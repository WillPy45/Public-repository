#include "BMP_Kit.h"
#include <time.h>
//Programa para probar las funciones creadas en BMP_Kit.h
int main(int argc, char** argv){
    clock_t start_t, end_t;
    double total_t;
    start_t = clock();
    x24bmpFile archivo1;

    archivo1.filename = calloc(1000, sizeof(char));

    for (int i = 1; i < argc; i++) {
        strcat(archivo1.filename, argv[i]);
        if (i < argc - 1) {
            strcat(archivo1.filename, " "); // Añade un espacio entre los argumentos
        }
    }

    archivo1.ptrfile = fopen(archivo1.filename, "rb+");
    
    
    if (archivo1.ptrfile == NULL)
    {
        printf("Error al crear archivo, puntero nulo\n");
        return 1;
    }

    //Carga de datos en los atributos del archivo y comprobación de validez
    if(!(archivo1.truthfile = isBMPx24(archivo1.ptrfile, &archivo1.sizeBytes, &archivo1.bitspx))){
        printf("%s no es .bmp de 24 bits", archivo1.filename);
        fclose(archivo1.ptrfile);
        return 2;
    }


    archivo1.offsetOfImgData = getoffset(archivo1.ptrfile);
    get_Row_and_Column(archivo1.ptrfile, &archivo1.rowSize, &archivo1.columnSize);

    if (resolutionCreate(&archivo1.resolution, archivo1.rowSize, archivo1.columnSize) != 0)
    {
        fclose(archivo1.ptrfile);
        return 3;
    }

    //Prueba de posiciones modificables
    archivo1.resolution[0][0].redIntensity = 0xAF;
    archivo1.resolution[0][0].greenIntensity = 0xFF;
    archivo1.resolution[0][0].blueIntensity = 0xAC;

    archivo1.resolution[0][1].redIntensity = 0xAF;
    archivo1.resolution[0][1].greenIntensity = 0xFF;
    archivo1.resolution[0][1].blueIntensity = 0xAC;

    //Prueba de impresión
    printf("r[0][0]: %x | g[0][0]: %x | b[0][0]: %x\n", archivo1.resolution[0][0].redIntensity, archivo1.resolution[0][0].greenIntensity, archivo1.resolution[0][0].blueIntensity);
    printf("r[0][0]: %x | g[0][1]: %x | b[0][1]: %x\n", archivo1.resolution[0][1].redIntensity, archivo1.resolution[0][1].greenIntensity, archivo1.resolution[0][1].blueIntensity);

    //Prueba de impresión posterior a copia 
    copyBMPtoArray(archivo1.ptrfile, archivo1.offsetOfImgData, archivo1.resolution, archivo1.rowSize, archivo1.columnSize);
    printf("Posterior a copia\n");
    printf("r[0][0]: %x | g[0][0]: %x | b[0][0]: %x\n", archivo1.resolution[0][0].redIntensity, archivo1.resolution[0][0].greenIntensity, archivo1.resolution[0][0].blueIntensity);
    printf("r[0][0]: %x | g[0][1]: %x | b[0][1]: %x\n", archivo1.resolution[0][1].redIntensity, archivo1.resolution[0][1].greenIntensity, archivo1.resolution[0][1].blueIntensity);

    //Se dibuja una bandera
    uint32_t j;
    for (j = 0; j < archivo1.rowSize/3; j++)
    {
        for (uint32_t k = 0; k < archivo1.columnSize; k++)
        {
            
            ColorModifier(archivo1.resolution, j, k, 0x0, 0x0, 0xff);
        }
        
    }

    for (j; j < archivo1.rowSize/3*2; j++)
    {
        for (uint32_t k = 0; k < archivo1.columnSize; k++)
        {
            ColorModifier(archivo1.resolution, j, k, 0xff, 0xff, 0xff);
            
        }
        
    }

    for (j; j < archivo1.rowSize/3*3; j++)
    {
        for (uint32_t k = 0; k < archivo1.columnSize; k++)
        {
            ColorModifier(archivo1.resolution, j, k, 0xff, 0x0, 0x0);
               
        }
        
    }

   
    
    //Se hace efecto de lo dibujado haciendo cambios en el archivo .bmp
    printf("Revise su archivo de imágen %s, posiblemente haya sufrido cambios\n", archivo1.filename);
    copyArraytoBMP(archivo1.ptrfile, archivo1.resolution, archivo1.offsetOfImgData, archivo1.rowSize, archivo1.columnSize);
    
    //Liberación de memoria
    
    free(archivo1.filename);
    freeResolution(&archivo1.resolution, archivo1.rowSize);
    fclose(archivo1.ptrfile);
    printf("\nOPERACIÓN EXITOSA\n \n");

    end_t = clock();
    total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;

    printf("Datos.\n");
    printf("Resolucion de imagen: %i x %i\n", archivo1.columnSize, archivo1.rowSize);
    printf("Bits por pixel: %i\n", archivo1.bitspx);
    printf("Peso de la imagen: %i bytes\n", archivo1.sizeBytes);
    printf("Tiempo de ejecucion: %f\n", total_t);
    return 0;
}

