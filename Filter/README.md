El siguiente programa filter.c es un programa que aplica filtros a imágenes .bmp de 24 bits de profundidad.

Teniendo el programa compilado, ejecutalo con ./filter -[opcion de filtro] [ruta del archivo fuente] [nombre del archivo destino]

El mismo modifica un archivo partiendo del archivo fuente y crea un archivo nuevo, se cuenta con 5 filtros, estos serían.
- Imágen original:
  
![Example](https://github.com/WillPy45/Public-repository/blob/main/Filter/images/yard.bmp)

- Escala de grises (-g): Ejecutando con ./filter -g archivoFuente.bmp archivoSalida.bmp modifica la imágen a una escala de grises, esto iterando cada pixel y haciendo una sumatoria de sus diferentes canales de colores (Red, Green, y Blue) y dividiendo por 3
--> BYTE grayscaleValue = round((image[j][k].rgbtBlue + image[j][k].rgbtGreen + image[j][k].rgbtRed) / 3.0);

![Example](https://github.com/WillPy45/Public-repository/blob/main/Filter/Imagenes_de_Salida/yard_grayscale.bmp)


- Reflejar (-r):

![Example](https://github.com/WillPy45/Public-repository/blob/main/Filter/Imagenes_de_Salida/yard_reflect.bmp)

- Desenfoque/blur (-b):

![Example](https://github.com/WillPy45/Public-repository/blob/main/Filter/Imagenes_de_Salida/yard_blur.bmp)


- Detección de bordes (-e):
  
![Example](https://github.com/WillPy45/Public-repository/blob/main/Filter/Imagenes_de_Salida/yard_edges.bmp)

- Deteccion de bordes y representacion en dos colores dependiendo del Umbral designado:

![Example](https://github.com/WillPy45/Public-repository/blob/main/Filter/Imagenes_de_Salida/yard_binaryEdge_Umbral10.bmp)

![Example](https://github.com/WillPy45/Public-repository/blob/main/Filter/Imagenes_de_Salida/yard_binaryEdge_Umbral20.bmp)

![Example](https://github.com/WillPy45/Public-repository/blob/main/Filter/Imagenes_de_Salida/yard_binaryEdge_Umbral30.bmp)

![Example](https://github.com/WillPy45/Public-repository/blob/main/Filter/Imagenes_de_Salida/yard_binaryEdge_Umbral50.bmp)

![Example](https://github.com/WillPy45/Public-repository/blob/main/Filter/Imagenes_de_Salida/yard_binaryEdge_Umbral100.bmp)

![Example](https://github.com/WillPy45/Public-repository/blob/main/Filter/Imagenes_de_Salida/yard_binaryEdge_Umbral150.bmp)

![Example](https://github.com/WillPy45/Public-repository/blob/main/Filter/Imagenes_de_Salida/yard_binaryEdge_Umbral200.bmp)

![Example](https://github.com/WillPy45/Public-repository/blob/main/Filter/Imagenes_de_Salida/yard_binaryEdge_Umbral255.bmp)
