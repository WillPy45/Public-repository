import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python3 dna.py [dna databases] [dna sequence]")

    # Read database file into a variable
    database_path = sys.argv[1]
    database_buffer = list()

    try:
        with open(database_path, "r") as database_file:
            database_buffer = list(csv.DictReader(database_file))

    except FileNotFoundError:
            sys.exit(f"{database_path} file does not exist")


    # Read DNA sequence file into a variable
    sequence_path = sys.argv[2]
    sequence_buffer = str()

    try:
        with open(sequence_path, "r") as sequence_file:
            sequence_buffer = sequence_file.readline()

    except FileNotFoundError:
        sys.exit(f"{sequence_path} file does not exist")


    # Find longest match of each STR in DNA sequence
    longest_matches_STR = dict()


    for dnapiece_key in list(database_buffer[0].keys()):
        if dnapiece_key != "name":
            longest_matches_STR[dnapiece_key] = longest_match(sequence_buffer, dnapiece_key)

    # Check database for matching profiles
    suspect_name = "No match"
    
    for suspect in database_buffer:
        match = True
        
        for dna_str in longest_matches_STR.keys():
            if int(suspect[dna_str]) != longest_matches_STR[dna_str]:
                match = False
                break

        if match:
            suspect_name = suspect["name"]
            break


    print(f"Suspect is {suspect_name}")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
