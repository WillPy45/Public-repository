El siguiente programa filter.c es un programa que aplica filtros a imágenes .bmp de 24 bits de profundidad.

Teniendo el programa compilado, ejecutalo con ./filter -[opcion de filtro] [ruta del archivo fuente] [nombre del archivo destino]

El mismo modifica un archivo partiendo del archivo fuente y crea un archivo nuevo, se cuenta con 5 filtros, estos serían.
- g: Ejecutando con ./filter -g archivoFuente.bmp archivoSalida.bmp modifica la imágen a una escala de grises, esto iterando cada pixel y sumando con sus pixeles vecinos, luego dividiendo la cantidad de pixeles vecinos incluyendo el pixel seleccionado.

[Imágen de referencia]



