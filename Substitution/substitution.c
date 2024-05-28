#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "mylib.h"
/* Este programa utiliza los argumentos proveidos por las lineas de coma 
 La entrada esperada por el CLI es un string de 26 caracteres no duplicados del alfabeto inglés
 https://imgur.com/a/tXz3rDt <-- Compilacion y ejemplo de uso*/
 
void Sub_ciphertextF(char plaintext[], char ciphertext[], char key[]);
int IsDuplicate(char array[]);

int main(int argc, char* argv[])
{
    int TAM = 1000000;
    char plaintext[TAM], ciphertext[TAM];


    //Validacion
    if (argc == 2)
    {
        int strlenght = strlen(argv[1]);
        if (strlenght == 26)
        {
            for (int j = 0; j < 26; j++)
            {
                if (!((argv[1][j]>64 && argv[1][j] < 91) || (argv[1][j]>96 && argv[1][j] < 123)))
                {
                    printf("key only must containt letters\n");
                    return 1;
                }
                else if(IsDuplicate(argv[1])){
                    printf("The key must not have duplicate elements\n");
                    return 1;
                }
            }
        }else
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }

    }else{
        printf("Usage: ./substitution key\n");
        return 1;
    }

    //E/S
    get_stringss("Plaintext: ", plaintext, TAM);
    Sub_ciphertextF(plaintext, ciphertext, argv[1]);
    printf("\nCiphertext: %s\n", ciphertext);
    return 0;
}

void Sub_ciphertextF(char plaintext[], char ciphertext[], char key[]){
    int j = 0;
    char upperABCs[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    char lowerABCs[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};


    do
    {
        //Caso mayuscula
        if (plaintext[j]>64 && plaintext[j] < 91)
        {
            for (int k = 0; k < 26; k++)
            {
                if (plaintext[j] == upperABCs[k])
                {
                    ciphertext[j] = toupper(key[k]);
                    break;
                }
            }
        }//Caso minuscula
        else if (plaintext[j]>96 && plaintext[j] < 123)
        {
            for (int k = 0; k < 26; k++)
            {
                if (plaintext[j] == lowerABCs[k])
                {
                    ciphertext[j] = (toupper(key[k]) + 32); //Distancia de upper character a lower character en ASCII
                    break;
                }
            }
        }//No es una letra
        else
        {
            ciphertext[j] = plaintext[j];
        }

        j++;
    } while (plaintext[j]);

}

int IsDuplicate(char array[]){
    int size = strlen(array);
    int cant = 0;
    for (int j = 0; j < size; j++){
        cant = 0;
        for (int k = 0; k< size; k++){
            if (array[j] == array[k]){
                cant++;
            }
        if (cant > 1){
            return 1;
        }
        }
    }
    return 0;
}

