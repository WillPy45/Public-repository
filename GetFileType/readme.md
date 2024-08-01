# GetFileType README
## Descripción
GetFileType es un programa de tipo terminal (Command Line Argument) en donde con una dirección del archivo se puede determinar el tipo de archivo. El mismo se vale de los datos hexadecimales que se encuentran dentro de cada archivo.
## Uso
- Teniendo el programa compilado, debes abrir una terminal como por ejemplo la terminal integrada de Visual Code Studio.
- Debes escribir el comando ./GetFileType.exe y una dirección al archivo que se desea obtener su tipo.
```bash
./GetFileType [ruta/nombre_del_archivo]
```
## Notas
- **Claridad en la Identificación:** Se especifican los tipos de archivos que el programa puede identificar.
- **Independencia:** Las funciones están hechas de tal modo de que puedas extraer del código fuente solo las necesarias. Algunas funciones dependen de otras funciones para su correcto funcionamiento.
  ```c
  //PNG.
  bool isPNG(FILE *ptrFile);
  ```
  ```c
  //Libre Office.
  //Función principal (De uso en código)
  bool isOfficeFile(FILE *ptrFile);
  //Funciones necesarias (Se requiere declarar estas funciones para que la función principal funcione correctamente)
  char* GetOfficeType(FILE *ptrFile);
  void Get_mimetype(char mimetypeArray[], int mimetypeSize, FILE* ptrFile);
  ```
  ```c
  //BMP de 24 bits de profundidad
  //Función principal (De uso en código)
  bool isBMPx24(FILE *ptrFile);
  //Funciones necesarias (Se requiere declarar esta funcion para que la función principal funcione correctamente)
  int BMPSize(FILE *ptrFile);
- **Reconocimiento de Limitaciones:** Se aclara que el programa no es exhaustivo y puede tener problemas de precisión en algunos casos.
- **Advertencia sobre Uso:** Se enfatiza que el software no está destinado para usos profesionales, destacando su carácter básico.
- **Mejora continua:** El software puede sufrir modificaciones si es necesario, por lo tanto no se declara como una versión final.
