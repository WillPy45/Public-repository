#include <stdio.h>
#include <string.h>
#include <math.h>
#include "mylib.h"
/* Este programa utiliza los argumentos proveidos por las lineas de comandos, escribe ./caesar.exe key, por 
ejemplo ./caesar 13 */
// https://imgur.com/a/AKBQnZw <-- Compilacion y ejemplo de uso

int isNumber(char* argv[], int ind);
void ciphertextF(char plaintext[], char ciphertext[], int key);

int main(int argc, char* argv[]){
    int key, TAM = 1000000;
    char plaintext[TAM], ciphertext[TAM];

    if ((argc == 2) && (isNumber(argv, 1) == 1))
    {
        key = atoi(argv[1]);
        if (key < 0){
            printf("Usage: ./caesar key | only positive numbers\n");
            return 1;
        }
        
    }else{
        printf("Usage: ./caesar key\n"); 
        return 1;
    }
    get_stringss("Plaintext: ", plaintext, TAM);
    ciphertextF(plaintext, ciphertext, key); 
    printf("\nCiphertext: %s\n", ciphertext);
      
    return 0;
}

int isNumber(char* argv[], int ind) // Ints
{
    int j = 0, noINT = 0;
    do
    {
        if ((argv[1][j] == '-' || argv[1][j] == '+' ) || (argv[ind][j] > 47 && argv[ind][j] < 58))
        {
            noINT = 0;
        }
        else{
            noINT = 1;
            break;
        }
        j++;
    } while (argv[ind][j] != '\0' && noINT == 0);

    //Is number?
    if (noINT == 0){
        return 1; 
    }else{
        return 0;
    }
}

void ciphertextF(char plaintext[], char ciphertext[], int key){
    int j = 0, index = 0;
    char upperABCs[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    char lowerABCs[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    do
    {
        if ((plaintext[j]>64 && plaintext[j] < 91) || (plaintext[j] > 96 && plaintext[j] < 123))
        {
            if (plaintext[j]>64 && plaintext[j] < 91)
            {        
                index = plaintext[j]-65; //Upper ASCII 65 - 90
                ciphertext[j] = upperABCs[(index + key) % 26]; 

            }else{
                
                index = plaintext[j]-97; //Lower ASCII 97 - 122 
                ciphertext[j] = lowerABCs[(index + key) % 26]; 
                
            }

        }else{
            ciphertext[j] = plaintext[j];
        }      
        j++;
    } while (plaintext[j] != '\0');  
}