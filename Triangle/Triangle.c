#include <stdio.h>
#include "mylib.h"
//Usando gcc compila con este comando: gcc Triangle.c mylib.c -o Triangle.exe

//Prototipos


int pyramid(int height, char ascii_character); 


int main(void){
    int height = 0;
    char ascii_character;
    //Introducir altura - Solo enteros positivos. Se usará get_integer() para evitar problemas con los caracteres.
    do{
        height = get_integer("height: ");
    }while(height<=0); 
    printf("Ingrese un caracter a imprimir: \n");
    ascii_character= getchar();
    pyramid(height, ascii_character);


    return 0;
}


//Funciones

int pyramid(int height, char ascii_character){
    //arg1: altura. arg2: caracter a imprimir
    int ancho = height;
    int espacios = 0;
    int ascii = 0;
    int altura_actual = 0, i = 0, z = 0;
    int x = altura_actual;
    for (x=0; x < height; x++)
    {
        ascii = x+1; 
        espacios = ancho-ascii;
        for (i=0; i < espacios; i = i+1){
            printf(" ");

        }
        for (z=0; z < ascii; z++){
            printf("%c", ascii_character);
        }
        printf("\n");
        //Fin linea
    }
    return 0;
}
