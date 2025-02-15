#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"

int get_integer(char* imprimir){
    
    int num = 0;
    int Verif = 0;
    //Si entrada es correcta funcion scanf retorna 1, caso incorrecto, retorna 0;
    do
    {
        printf("%s", imprimir); //Imprime segun la entrada get_integer("TEXTO QUE SE IMPRIME")
        Verif = scanf("%i", &num);
        //Si scanf falló, limpiar bufer
        if (Verif == 0 || getchar() != '\n')
        {
            while (getchar() != '\n'); //LIMPIEZA DE BUFER
            Verif = 0; //Declarar invalido por encontrar un caracter prohibido
        }
    } while (Verif == 0);
    return num;
}

void get_stringss(char *imprimir, char STRING[], int sizeSTR)
{   // args: STRING A IMPRIMIR | STRING A MANIPULAR | TAMAÑO DEL ARRAY
    /* Funcionamiento: Esta funcion permite en un solo paso imprimir mensaje para el usuario e
    introducir strings. El salto de linea es ignorado, no ocupa espacio en el array.*/
    char temp = 'F';
    int desb = 1, j, caution = 0;

    do
    {
        for (int k = 0; k < sizeSTR - 1; k++)
        { // reseteo de string
            STRING[k] = '\0';
        }
        
        caution = 0, desb = 0, j = 0, temp = 'F'; // reseteo de variables
        printf("%s", imprimir); // mensaje por pantalla

        while (((temp = getchar()) != '\n'))
        {
            if (j < sizeSTR - 1) // (Indices 0 - 9 y se resta 1 para el caracter nulo)
            {
                desb = 0;
                STRING[j] = temp;
            }
            else // MANEJO DE DESBORDAMIENTO
            {
                desb = 1;
                if (caution == 0)
                {
                    printf("CUIDADO! EL BUFER SE HA DESBORDADO, SE PROCEDERÁ A LA LIMPIEZA DE LOS "
                           "CARACTERES EXCEDENTES.\n MAX_CARACTERES: %i - 1 (NULL CHARACTER). \n", sizeSTR);
                    printf("\nCAUTION! THE BUFFER HAS OVERFLOWED, THEY WILL BE CLEANED"
                           "SURPLUS CHARACTERS.\n MAX_CHARACTERS: %i - 1 (NULL CHARACTER). \n", sizeSTR);
                    printf("\nCaracteres excedidos / Exceeded character: "
                           "%c (%i) | ", temp, temp);
                    caution = 1;
                }
                else
                { // Impresion de caracteres que se quedaron en el bufer
                    printf("%c (%i) | ", temp, temp);
                }
            }
            j++;
        }

        if (temp == '\n' && desb == 1) // Salto de linea
        { 
            printf("\n");
        }
    }while (desb == 1);
}

