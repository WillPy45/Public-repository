#include <math.h>
#include <stdio.h>
#include "mylib.h"

/*--- First compile using the command: gcc readability.c mylib.c -o readability.exe --- */

// Colleman-Liau Index
float CLI(char text[])
{
    /*Colleman-Liau Index ---> https://en.wikipedia.org/wiki/Coleman%E2%80%93Liau_index
    index = 0.0588 * L - 0.296 * S - 15.8
    L = (Letters ÷ Words) × 100
    S = (Sentences ÷ Words) × 100
    */
    float f_CLI, letters = 0, words = 1, sentences = 0;
    int i_CLI, j = 0;
    do
    {
        // letters counting
        if ((text[j] > 64 && text[j] < 91) || (text[j] > 96 && text[j] < 123) ||
            (text[j] > 47 && text[j] < 58)) // ASCII
        {
            letters++;
        }

        // words counting
        if (text[j] == ' ' && text[j + 1] != ' ')
        {
            words++;
        }

        // sentences counting
        /*  For this counting, any period, exclamation points, or question mark indicates a sentence. 
        Except dots that have letters on their right side, for example: U.S. RR.HH.*/

        if (text[j+1] == ' '){
            switch (text[j])
            {
                case '?':
                    sentences++;
                    break;
                case '.':
                    sentences++;
                    break;
                case '!':
                    sentences++;
                    break;
                default:
                    break;
            }
        }
        j++;
    }
    while (text[j] != '\0' && text[j] != '\n');

    // Application of the formula CLI
    float L = (letters / words) * 100;
    float S = (sentences / words) * 100;
    f_CLI = 0.0588 * L - 0.296 * S - 15.8;

    return f_CLI;
}

int main()
{
    // Input of text
    char text[1000000];
    get_strings("Text: ", text);

    // Ouput
    printf("CLI: %f\n", CLI(text));
    int rounded_CLI = round(CLI(text));
    if (rounded_CLI < 1){
        printf("Before Grade 1\n");
    }
    else if (rounded_CLI > 16){
        printf("Grade 16+\n");
    }
    else{
        printf("Grade %i\n", rounded_CLI);
    }
}
