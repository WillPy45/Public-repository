#include "BMP_Kit.h"

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Funciones
int resolutionCreate(RGB*** ptrpixelArray, uint32_t row, uint32_t column){ 
    
    *ptrpixelArray = calloc(row, sizeof(RGB *));
    if (*ptrpixelArray == NULL) {
        printf("Error al asignar memoria.\n");
        
        return 1;
    }
    
    // Reserva memoria para cada fila (Eje Y)
    for (uint32_t i = 0; i < row; ++i) {
        (*ptrpixelArray)[i] = calloc(column, sizeof(RGB));
        if ((*ptrpixelArray)[i] == NULL) {
             
            printf("Error al asignar memoria para la fila %d. ", i);

            //Liberación de memorias creadas correctamente antes del error
            for (uint32_t memoryleakIndex = 0; memoryleakIndex < i+1; memoryleakIndex++)
            {
                free((*ptrpixelArray)[memoryleakIndex]);
            }
            free(*ptrpixelArray);
            return 1; 
        } 
    }

    return 0;
}

void freeResolution(RGB*** ptrpixelArray, uint32_t row){ //Liberación de memoria creada por la función resolutionCreate
    for (uint32_t i = 0; i < row; ++i) {
        free((*ptrpixelArray)[i]);
    }

    free(*ptrpixelArray);
}

//-------------------------------------------------------------------------------------------------------------------

/*Esta función retorna 0 si el tamaño del archivo se obtuvo correctamente y -1 si existe errores. Dentro de la variable auxvar_BMPSize
 se guardará el tamaño del archivo.*/
bool isBMPx24(FILE *ptrFile, uint32_t *auxVar_BMPSize, uint16_t *auxVar_BitsPerPixel){
    fseek(ptrFile, 0, SEEK_SET);
    uint8_t signature[] = {0x42, 0x4d};
    
    //Comprobacion de firma BM
    for (uint32_t j = 0; j < 2; j++){
        if (fgetc(ptrFile) != signature[j]){
            return false;
        }
    }

    //Comprobacion de integridad de tamaño

    if (BMPSize(ptrFile, auxVar_BMPSize) == -1){
        return false;
        //lo que dice ftell sobre el tamaño del archivo no coincide con los datos otorgados en la estructura hexadecimal
    }
    getbitspx(ptrFile, auxVar_BitsPerPixel);
    if (*auxVar_BitsPerPixel != 24)
    {
        return false;
    }
    
    
    return true;
}

/* Dentro de la variable BitsPerPixel se almacena la cantidad de bits que ocupa cada
pixel de la imágen*/
void getbitspx(FILE *ptrFile, uint16_t *BitsPerPixel){ 
    fseek (ptrFile, 28, SEEK_SET);
    uint8_t pixelSizeSignature[2];
    fread(pixelSizeSignature, 1, 2, ptrFile);
    *BitsPerPixel = 0x0;
    for (uint32_t i = 0; i < 2; i++)
    {
        *BitsPerPixel = pixelSizeSignature[i] << (8 * i) | *BitsPerPixel;
    }
}

/*Esta función retorna 0 si el tamaño del archivo se obtuvo correctamente y -1 si existe errores. Dentro de la variable auxvar_BMPSize
 se guardará el tamaño del archivo.*/
uint32_t BMPSize(FILE *ptrFile, uint32_t *auxVar_BMPSize){ 

    //Comprobación
    fseek(ptrFile, 0, SEEK_END);
    uint64_t file_size_ftell = ftell(ptrFile);

    uint8_t FileSizeSignature[4];
    fseek(ptrFile, 2, SEEK_SET);
    fread(FileSizeSignature, 1, 4, ptrFile);
    
    //Se usan operadores de desplazamiento de bits para acomodar el conjunto de hexadecimales en una sola variable
    uint32_t SizeInHex = 0x0; 
    for (uint32_t j = 0; j < 4; j++){
        SizeInHex = (FileSizeSignature[j]<<(8*j)) | SizeInHex;
    }

    //Comprobación de veracidad ftell y datos hexadecimales para el tamaño del archivo
    if (file_size_ftell == SizeInHex){
        *auxVar_BMPSize = SizeInHex;
        return 0; //Sin error
    }else{
        return -1; //Caso incoherencia
    }
}

/*El inicio de datos de la imágen se encuentra en los datos del fichero (offset). Sacar el dato requiere la conversión en little endian y combinación de los hexadecimales */
uint32_t getoffset(FILE* ptrFile){
    fseek(ptrFile, 10, SEEK_SET);
    uint8_t offsetBigendian[4];
    fread(offsetBigendian, 1, 4, ptrFile);
    uint32_t offsetLittleendian = 0x0;

    for (int i = 0; i < 4; i++)
    {
        offsetLittleendian = (offsetBigendian[i] << (8 * i)) | offsetLittleendian;
    }
    return offsetLittleendian;
}

void get_Row_and_Column(FILE *ptrFile, uint32_t *row, uint32_t *column){
    *row = 0; 
    *column = 0;
    uint8_t tmpBuffer[4];

    //Obtener columna
    fseek(ptrFile, 18, SEEK_SET);
    fread(tmpBuffer, 1, 4, ptrFile);
    for (int j = 0; j < 4; j++)
    {
        *column = (tmpBuffer[j] << (8 * j)) | *column;
    }
    

    //Obtener fila
    fseek(ptrFile, 22, SEEK_SET);
    fread(tmpBuffer, 1, 4, ptrFile);
    for (int j = 0; j < 4; j++)
    {
        *row = (tmpBuffer[j] << (8 * j)) | *row;
    }
}


//--------------------------------------------------------------------------------------------------------------------
/*Retorna un array en donde el primer pixel (0, 0) corresponde a la esquina superior izquierda
[(0, 0)  (0, 1) (0, 2) (0, 3) (0, 4)]
[(1, 0)  (1, 1) (1, 2) (1, 3) (1, 4)]
[(2, 0)  (2, 1) (2, 2) (2, 3) (2, 4)]
*/
void copyBMPtoArray(FILE *ptrFile, uint32_t offsetOfImgData, RGB** RGB_Array, uint32_t row, uint32_t column){
    fseek(ptrFile, offsetOfImgData, SEEK_SET);
    uint32_t padding = (4 - (column * 3) % 4) % 4; // Calcular tamaño del padding
    if (padding == 0){

        uint32_t jt = 0;
        uint32_t necessaryBytes = column*3;
        uint8_t tmpBufferArray[necessaryBytes];
        for (uint32_t j = 0; j < row; j++)
        {
        
            jt = row - j - 1;
            fread(tmpBufferArray, 1, necessaryBytes, ptrFile); 
    
            for (size_t k = 0, r = 0; k < column; k++, r = r+3) //En .bmp la imágen comienza desde la última fila
            {
                RGB_Array[jt][k].blueIntensity = tmpBufferArray[r];
                RGB_Array[jt][k].greenIntensity = tmpBufferArray[r+1];
                RGB_Array[jt][k].redIntensity = tmpBufferArray[r+2];
            }
        
         
        
        }
        }else{
        
        uint32_t jt = 0;
        uint32_t necessaryBytes = column*3;
        uint8_t tmpBufferArray[necessaryBytes];
        for (uint32_t j = 0; j < row; j++)
        {
        
            jt = row - j - 1;
            fread(tmpBufferArray, 1, necessaryBytes, ptrFile); 
    
            for (size_t k = 0, r = 0; k < column; k++, r = r+3) //En .bmp la imágen comienza desde la última fila
            {
                RGB_Array[jt][k].blueIntensity = tmpBufferArray[r];
                RGB_Array[jt][k].greenIntensity = tmpBufferArray[r+1];
                RGB_Array[jt][k].redIntensity = tmpBufferArray[r+2];
            }
        
            fseek(ptrFile, padding, SEEK_CUR);
        
        }

        }
} 

//---------------------------------------------------------------------------------------------
void copyArraytoBMP(FILE *ptrFile, RGB** RGB_Array, uint32_t offsetOfImgData, uint32_t row, uint32_t column){
    
    fseek(ptrFile, offsetOfImgData, SEEK_SET);
    uint32_t padding = (4 - (column * 3) % 4) % 4;
    
    if (padding == 0){

        uint32_t necessaryBytes = column*3;
        uint8_t tmpBytesBuffer[necessaryBytes];

    
        for (long int j = row-1; j >= 0 ; j--) 
        { 
            // Conversión al orden que BMP interpreta los colores
  
            for (uint32_t k = 0,  r = 0; k < necessaryBytes; k = k+3, r++)
            {
                tmpBytesBuffer[k] = RGB_Array[j][r].blueIntensity;
                tmpBytesBuffer[k+1] = RGB_Array[j][r].greenIntensity;
                tmpBytesBuffer[k+2] = RGB_Array[j][r].redIntensity;
            
            }
            fwrite(tmpBytesBuffer, 1, necessaryBytes, ptrFile);
       
       
        }

  
    }else
    {
        uint32_t necessaryBytes = column*3;
        uint8_t tmpBytesBuffer[necessaryBytes];

    
        for (long int j = row-1; j >= 0 ; j--) 
        { 
            // Conversión al orden que BMP interpreta los colores
  
            for (uint32_t k = 0,  r = 0; k < necessaryBytes; k = k+3, r++)
            {
                tmpBytesBuffer[k] = RGB_Array[j][r].blueIntensity;
                tmpBytesBuffer[k+1] = RGB_Array[j][r].greenIntensity;
                tmpBytesBuffer[k+2] = RGB_Array[j][r].redIntensity;
            
            }
            fwrite(tmpBytesBuffer, 1, necessaryBytes, ptrFile);
            fseek(ptrFile, padding, SEEK_CUR);
       
        }
        
       
    }
}
      



void ColorModifier(RGB** Array, uint32_t row, uint32_t column, uint8_t blue, uint8_t green, uint8_t red){
    Array[row][column].blueIntensity = blue;
    Array[row][column].greenIntensity = green;
    Array[row][column].redIntensity = red;
}


//Filtros
void RGBtoGrayscale(RGB** Array, uint32_t rows, uint32_t columns){
    //Formula Y = 0.299 R + 0.587 G + 0.114 B
    uint8_t Y_GrayscaleValue;
   

    for (uint32_t j = 0; j < rows; j++)
    {
        for (uint32_t k = 0; k < columns; k++)
        {
            
            Y_GrayscaleValue = (uint8_t) (Array[j][k].redIntensity*0.299 + Array[j][k].greenIntensity * 0.587 + Array[j][k].blueIntensity * 0.114);
          
            Array[j][k].blueIntensity = Y_GrayscaleValue;
            Array[j][k].greenIntensity = Y_GrayscaleValue;
            Array[j][k].redIntensity = Y_GrayscaleValue;
        }
        
    } 
}