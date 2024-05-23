#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
{// args: STRING A IMPRIMIR | STRING A MANIPULAR | TAMAÑO DEL ARRAY
    char temp = 'F';
    int desb = 1;
    do
    {
        temp = 'F';
        desb = 1;
        printf("%s", imprimir);
        fgets(STRING, sizeSTR, stdin);
        for (int j = 0; j <= sizeSTR - 2; j++)
        {
            if (STRING[j] == '\n')
            {
                desb = 0;
            }
        }
        if (desb == 1)
        { // En caso de deborde, limpiar bufer
            printf("CUIDADO! EL BUFER SE HA DESBORDADO, SE PROCEDERÁ A LA LIMPIEZA DE LOS "
                   "CARACTERES EXCEDENTES.\n MAX_CARACTERES: %i - 1 (NULL CHARACTER). \n --- RECUERDA QUE ENTER TAMBIEN ES UN CARACTER---\n",
                   sizeSTR);
            do
            {
                temp = getchar();
                printf("\nBasura: %c (%i)\n", temp, temp);
            }while (temp != '\0' && temp != '\n');
        }
    }while (desb == 1);
}


