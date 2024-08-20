#include "BMP_Kit.h"

int main(int argc, char** argv)
{

    if (argc < 3){
        printf("Uso: ./FiltersExampleExec [Tipo de filtro] [nombre del archivo]\n");
        printf("Ejemplo: ./FiltersExampleExec grayscale FHD.bmp\n");
        return 1;
    }

    char* filterOption = argv[1];
    x24bmpFile filterFile;

    filterFile.filename = calloc(1000, sizeof(char));

    for (int i = 2; i < argc; i++) {
        strcat(filterFile.filename, argv[i]);
        if (i < argc - 1) {
            strcat(filterFile.filename, " "); // Añade un espacio entre los argumentos
        }
    }

    

  

    filterFile.ptrfile = fopen(filterFile.filename, "rb+");
    
    if (filterFile.ptrfile == NULL)
    {
        printf("No se ha podido abrir el archivo %s\n", filterFile.filename);
        return 2;
    }
    
    if(!(filterFile.truthfile = isBMPx24(filterFile.ptrfile, &filterFile.sizeBytes, &filterFile.bitspx))){
        printf("%s no es .bmp de 24 bits", filterFile.filename);
        fclose(filterFile.ptrfile);
        return 3;
    }
    
    filterFile.offsetOfImgData = getoffset(filterFile.ptrfile);
    get_Row_and_Column(filterFile.ptrfile, &filterFile.rowSize, &filterFile.columnSize);
    if (resolutionCreate(&filterFile.resolution, filterFile.rowSize, filterFile.columnSize) != 0)
    {
        fclose(filterFile.ptrfile);
        return 4;
    }
    //Aplicacion de filtros.

    copyBMPtoArray(filterFile.ptrfile, filterFile.offsetOfImgData, filterFile.resolution, filterFile.rowSize, filterFile.columnSize);

    if (strcmp(filterOption, "grayscale") == 0)
    {
        printf("Aplicando grayscale filter...\n");
        RGBtoGrayscale(filterFile.resolution, filterFile.rowSize, filterFile.columnSize);
        printf("Operacion completada\n");
    }
    else if (strcmp(filterOption, "reflect") == 0)
    {
        printf("Aplicado reflect filter...\n");
        RGB_Reflect(filterFile.resolution, filterFile.rowSize, filterFile.columnSize);
        printf("Operacion completada\n");
    }
    else if (strcmp(filterOption, "--") == 0)
    {
        printf("En proceso\n");
    }
    else{
        printf("Uso: ./FiltersExampleExec [Tipo de filtro] [nombre del archivo]\n");
        printf("Ejemplo: ./FiltersExampleExec grayscale FHD.bmp\n");

        printf("Tipos de filtros disponibles: grayscale, reflect.\n");
        fclose(filterFile.ptrfile);
        freeResolution(&filterFile.resolution, filterFile.rowSize);

        return 5;
    }
    
    copyArraytoBMP(filterFile.ptrfile, filterFile.resolution, filterFile.offsetOfImgData, filterFile.rowSize, filterFile.columnSize);


    fclose(filterFile.ptrfile);
    free(filterFile.filename);
    freeResolution(&filterFile.resolution, filterFile.rowSize);
    return 0;
}
