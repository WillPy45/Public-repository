#include <cs50.h> //Libreria Open Source otorgado por la Universidad de Harvard
#include <stdint.h> //Tipos de datos enteros de diferentes tamaños, uint8_t = 1 byte
#include <stdio.h> 
#include <string.h> //Manejo de cadenas
//Versión básica.
//Entrada por línea de comando esperado: ./GetFileType [direccion/nombre del archivo]
//Ejemplo de uso: ./GetFileType /workspaces/Public-repository/README.md

/*Modulos de getFileType, pueden usarse de manera independiente teniendo salida booleana.
 Útil cuando solo quieres saber si X archivo es el tipo especificado (pdf, png, ods, etc)*/
bool isPDF(FILE *ptrFile); 
bool isPNG(FILE *ptrFile); 

//GetOffice Type. 
bool isOfficeFile(FILE *ptrFile);
char* GetOfficeType(FILE *ptrFile);
void Get_mimetype(char mimetypeArray[], int mimetypeSize, FILE* ptrFile);

//Funcion principal de obtener tipo de fichero en una cadena de texto, útil para informarse
char* getFileType(FILE *ptrFile);


int main(int argc, char *argv[])
{ // argv[1]: filename
    if (argc != 2){
        printf("Formato: ./GetFileType [direccion/nombre del archivo]\n");
        return 1;
    }

    FILE *ptrFile = fopen(argv[1], "r");

    if (ptrFile == NULL){
        printf("-- No se ha podido encontrar el archivo %s\n", argv[1]);
        return 2;
    }

    char* FileType = getFileType(ptrFile);
    if (strcmp(FileType, "unclassified file") != 0){
        printf("Este archivo es %s\n", FileType);
    }
    else{
        printf(".::Error::. %s\n", FileType);
    }
    fclose(ptrFile);
    return 0;
}

bool isPDF(FILE *ptrFile){
    fseek(ptrFile, 0, SEEK_SET);
    uint8_t PDF_Signature[] = {0x25, 0x50, 0x44, 0x46, 0x2D};
    uint8_t SignatureSize = sizeof(PDF_Signature);
    uint8_t tmpBuffer[SignatureSize];
    fread(tmpBuffer, 1, SignatureSize, ptrFile);
    for (int i = 0; i < SignatureSize; i++){
        if (tmpBuffer[i] != PDF_Signature[i]){
            return false;
        }
    }
    return true;
}

//OFFICE
/*Los archivos OpenOffice tienen un patrones similares hexadecimales que lo utilizamos como indicador de tipo de archivo, por ende es posible
confundir los archivos si solo comparamos los primeros digitos ya que cada archivo varía en su contenido de cabecera.
Es por ello que para este caso  debemos buscar un patrón interesante, este sería mimetype, en donde mimetypeapplication/vnd.oasis.opendocument.txt
refiere a .odt y mimetypeapplication/vnd.oasis.opendocument.spreadsheet refiere a .ods*/

bool isOfficeFile(FILE *ptrFile){
    fseek(ptrFile, 0, SEEK_SET);

    //50 4B 03 04
    uint8_t CommonOfficeSignature[] = {0x50, 0x4b, 0x03, 0x04};
    uint8_t SignatureSize = sizeof(CommonOfficeSignature);
    uint8_t tmpBuffer[SignatureSize];

    fread(tmpBuffer, 1, SignatureSize, ptrFile);

    for (int i = 0; i < SignatureSize; i++){
        if (tmpBuffer[i] != CommonOfficeSignature[i]){
            return false;
        }
    }
    return true;
}

char* GetOfficeType(FILE *ptrFile){
    char mimetype[250];
    Get_mimetype(mimetype, 250, ptrFile);

    if (strcmp(mimetype, "mimetypeapplication/vnd.oasis.opendocument.text") == 0){
        return "odt";
    }else if(strcmp(mimetype, "mimetypeapplication/vnd.oasis.opendocument.spreadsheet") == 0){
        return "ods";
    }else{
        return "error";
    }
}

void Get_mimetype(char mimetypeArray[], int mimetypeSize, FILE* ptrFile){
    if (ptrFile == NULL){
        printf("No se pudo abrir archivo\n");
        return;
    }

    fseek(ptrFile, 30, SEEK_SET);
    char tmpChar;
    int j = 0;
    while((tmpChar = fgetc(ptrFile)) != 'P'){
        mimetypeArray[j] = tmpChar;
        j++;
    }
    return;
}

//

bool isPNG(FILE *ptrFile){
    fseek(ptrFile, 0, SEEK_SET);
    uint8_t PNG_Signature[] = {137, 80, 78, 71};
    uint8_t SignatureSize = sizeof(PNG_Signature);

    uint8_t tmpBuffer[SignatureSize];
    fread(tmpBuffer, 1, SignatureSize, ptrFile);
    for (int i = 0; i < SignatureSize; i++){
        if (tmpBuffer[i] != PNG_Signature[i]){
            return false;
        }
    }
    return true;
}



char* getFileType(FILE *ptrFile){
    if(ptrFile == NULL){
        return "null_pointer";
    }
    if (isPDF(ptrFile)){
        return "pdf";
    }else if(isOfficeFile(ptrFile)){
        return GetOfficeType(ptrFile);

    }else if(isPNG(ptrFile)){
        return "png";
    }else{
        return "unclassified file";
    }
}




