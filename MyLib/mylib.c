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
            printf("\nCAUTION! THE BUFFER HAS OVERFLOWED, THEY WILL BE CLEANED"
            "SURPLUS CHARACTERS.\n MAX_CHARACTERS: %i - 1 (NULL CHARACTER). \n --- REMEMBER THAT ENTER IS ALSO A CHARACTER---\n", sizeSTR);
            printf("\nCaracteres excedidos / Exceeded character: ");
            do
            {
                temp = getchar();
                printf("%c (%i) | ", temp, temp);
            }while (temp != '\0' && temp != '\n');
            printf("\n");
        }
    }while (desb == 1);
}


