#ifndef BMP_KIT_H
#define BMP_KIT_H
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct{ 
    uint8_t redIntensity;
    uint8_t greenIntensity;
    uint8_t blueIntensity;
}RGB;

typedef struct{
    RGB** iresulution; //Resolución, para casos de no necesitar otros atributos
}ArrayRGB;

typedef struct
{
    FILE* ptrfile; // Puntero otorgado por fopen
    RGB** resolution; // Array 2D
    uint32_t rowSize; // Cantidad de filas
    uint32_t columnSize; // Cantidad de columnas
    bool truthfile; // T si archivo es .bmp de 24 bits de profundidad, F caso contrario
    uint32_t sizeBytes; // Tamaño en bytes del archivo
    uint32_t offsetOfImgData; // Desplazamiento necesario para el inicio de datos de la imágen
    uint16_t bitspx; // Profunidad de colores
    char* filename; // Nombre del archivo
}x24bmpFile;

//Funciones Prototipos
/*A partir de un puntero de tipo RGB** Nombre, se crea una matriz 2D de Fila x Columna (resolución).
Por ejemplo 800x600*/
int resolutionCreate(RGB*** ptrpixelArray, uint32_t row, uint32_t column); 

//Liberación de memoria creada por la función resolutionCreate
void freeResolution(RGB*** ptrpixelArray, uint32_t row); 

/*Función para verificar si el archivo es .bmp de 24 bits, esta función también deposita el tamaño del archivo y 
la cantidad de bits por pixel*/
bool isBMPx24(FILE *ptrFile, uint32_t *auxVar_BMPSize, uint16_t *auxVar_BitsPerPixel); 

/*Esta función retorna 0 si el tamaño del archivo se obtuvo correctamente y -1 si existen errores. 
Dentro de la variable auxvar_BMPSize se guardará el tamaño del archivo.*/
uint32_t BMPSize(FILE *ptrFile, uint32_t *auxVar_BMPSize);

//Se obtiene el inicio de datos de la imágen, en otras palabras a partir de qué byte empieza los patrones de colores.
uint32_t getoffset(FILE* ptrFile);

//Obtiene la cantidad de bits que ocupa un pixel
void getbitspx(FILE *ptrFile, uint16_t *BitsPerPixel);

//Obtiene filas y columnas de una imágen. Sirve para extraer las dimensiones de una imágen existente
void get_Row_and_Column(FILE *ptrFile, uint32_t *row, uint32_t *column);

//Copia los colores de un archivo .bmp y lo aloja en un array bidimensional de struct RGB
void copyBMPtoArray(FILE *ptrFile, uint32_t offsetOfImgData, RGB** RGB_Array, uint32_t row, uint32_t column);

//Copia los colores de un array bidimensional de struct RGB  y lo aloja en el archivo .bmp
void copyArraytoBMP(FILE *ptrFile, RGB** RGB_Array, uint32_t offsetOfImgData, uint32_t row, uint32_t column);

//Modificar un pixel de un array RGB 2D
void ColorModifier(RGB** Array, uint32_t row, uint32_t column, uint8_t blue, uint8_t green, uint8_t red);

#endif // BMP_KIT_H
