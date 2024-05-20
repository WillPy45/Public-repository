#include <stdio.h>
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

void get_strings(char* output, char re_text[]) //get_string(Texto que desea como salida para el usuario | array donde guardarás el string)
{
    int j=0;
    printf("%s", output);
    while ((re_text[j] = getchar()) != '\n')
    {
        j++;
    }
}