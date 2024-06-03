#include <cs50.h> // https://github.com/cs50/libcs50?tab=readme-ov-file
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
// Make sure you install all the libraries
/*
Compile cmd: gcc runoff.c -lcs50 -o runoff.exe
Command Line Argument (how run): ./runoff.exe Candidate1 Candidate2 Candidate3 Candidate...
Example: ./runoff.exe Ana Juana Steve
*/
/*
How does the program work? In this program you must open it with the CLI (Command Line Argument)
with the following format: ./runoff.exe CandidateName1 CandidateName2 ...

In the "runoff" system, the winner is the one with +50% of votes. If there is no candidate with a
majority, the candidate with the fewest votes is eliminated  and his or her ballot is used in
search of second place preference. Then it's back to the second round.

If exist 3 ballots and 3 candidates, we can represent as
1| [Ana]   | [Steve] | [Steve] | [Ana]   | [Juana]
2| [Juana] | [Juana] | [Juana] | [Steve] | [Ana]
3| [Steve] | [Ana]   | [Ana]   | [Juana] | [Steve]

In this case, Ana is the winner because in the first round Juana is eliminated and in the second
round...
... Juanas vote became Ana vote because Anas was the second preference
*/
// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is j th preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);
bool Already_Voted(string CandidateName, int voter, int ActualRank);
int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{

    for (int j = 0; j < candidate_count; j++)
    {
        if (strcmp(candidates[j].name, name) == 0)
        {
            if (Already_Voted(name, voter, rank)){
                printf("Repeated vote.\n");
                return false; // Then invalid vote
            }
            preferences[voter][rank] = j;
            return true;
        }
    }
    printf("Invalid name.\n");
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // preferences[voter][rank]
    int AuxIndex = 0; // candidate index
    for (int j = 0; j < voter_count; j++)
    {
        for (int k = 0; k < candidate_count; k++)
        {
            AuxIndex = preferences[j][k];
            if (!candidates[AuxIndex].eliminated)
            {
                candidates[AuxIndex].votes++;
                break;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    int TotalVotes = 0; // Total votes of non-eliminated candidates
    int WINNERS = 0;
    int IndexWinner = 0;
    for (int j = 0; j < candidate_count; j++)
    {
        if (candidates[j].eliminated == false)
        {
            TotalVotes = TotalVotes + candidates[j].votes;
        }
    }

    // Find for mayorities votes (+50%)
    int HalfTotalVotes = round(TotalVotes / 2); // 50% votes
    for (int j = 0; j < candidate_count; j++)
    {
        if ((!candidates[j].eliminated) && (candidates[j].votes > HalfTotalVotes))
        {
            IndexWinner = j;
            TotalVotes = TotalVotes + candidates[j].votes;
            WINNERS++;
        }
    }
    if (WINNERS == 1)
    {
        printf("%s\n", candidates[IndexWinner].name);
        return true; // Print winner
    }
    else
    {
        return false; // NO EXISTS WINNER OR NEED A SECOND ROUND (TIES IS POSIBLE)
    }
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    int MinVote = INT_MAX;
    for (int j = 0; j < candidate_count; j++)
    {
        if ((candidates[j].votes < MinVote) && (!candidates[j].eliminated))
        {
            MinVote = candidates[j].votes;
        }
    }
    return MinVote;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // candidates tie represent as candidate[0] = candidate[1] = ... = candidate[n]
    bool TIE;
    int TiesCandidates = 0;
    int AvaibleCandidates = candidate_count;
    for (int j = 0; j < candidate_count; j++)
    {
        if (candidates[j].eliminated)
        {
            AvaibleCandidates--;
        }
        else if (candidates[j].votes == min)
        {
            TiesCandidates++;
        }
    }
    if (TiesCandidates == AvaibleCandidates)
    {
        return true; // Is tie
    }
    else
    {
        return false;
    }
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int j = 0; j < candidate_count; j++)
    {
        if (candidates[j].votes == min)
        { // This means that the candidate(s) with minimum number of votes will be eliminated
            candidates[j].eliminated = true;
        }
    }
    return;
}

bool Already_Voted(string CandidateName, int voter, int ActualRank)
{
    int index;
    if (ActualRank > 0)
    {
        for (int rank = 0; rank < ActualRank; rank++)
        {
            index = preferences[voter][rank];
            if (strcmp(CandidateName, candidates[index].name) == 0)
            {
                // already exist
                return true;
            }
        }
    }
    return false;
}
