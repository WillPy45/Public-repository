El siguiente programa filter.c es un programa que aplica filtros a imágenes .bmp de 24 bits de profundidad.

Teniendo el programa compilado, ejecutalo con ./filter -[opcion de filtro] [ruta del archivo fuente] [nombre del archivo destino]

El mismo modifica un archivo partiendo del archivo fuente y crea un archivo nuevo, se cuenta con 5 filtros, estos serían.
- **Imágen original:**
  
![Example](https://github.com/WillPy45/Public-repository/blob/main/Filter/images/yard.bmp)

- **Escala de grises (-g):** Ejecutando con ./filter -g archivoFuente.bmp archivoSalida.bmp modifica la imágen a una escala de grises

![Example](https://github.com/WillPy45/Public-repository/blob/main/Filter/Imagenes_de_Salida/yard_grayscale.bmp)


- **Reflejar (-r):** Ejecutando con ./filter -r archivoFuente.bmp archivoSalida.bmp modifica la imágen reflejando el mismo.


![Example](https://github.com/WillPy45/Public-repository/blob/main/Filter/Imagenes_de_Salida/yard_reflect.bmp)

- **Desenfoque/blur (-b):**  Ejecutando con ./filter -r archivoFuente.bmp archivoSalida.bmp modifica la imágen con el desenfoque de caja.

![Example](https://github.com/WillPy45/Public-repository/blob/main/Filter/Imagenes_de_Salida/yard_blur.bmp)


- **Detección de bordes (-e):** Ejecutando con ./filter -r archivoFuente.bmp archivoSalida.bm retorna una imágen en donde los bordes se encuentren resaltados. EL mismo utiliza el Operador Sobel.
  
![Example](https://github.com/WillPy45/Public-repository/blob/main/Filter/Imagenes_de_Salida/yard_edges.bmp)

- **Deteccion de bordes y representacion en dos colores dependiendo del Umbral designado:** Ejecutando con ./filter -z archivoFuente.bmp archivoSalida.bmp retorna una imágen con los bordes resaltados en el color blanco y el resto en color negro. El Umbral es la mínima intensidad de la magnitud de un pixel para considerarlo borde, por lo cual el mismo adquiere el color blanco (0xffffff)

- **Umbral 10**

![Example](https://github.com/WillPy45/Public-repository/blob/main/Filter/Imagenes_de_Salida/yard_binaryEdge_Umbral10.bmp)

- **Umbral 20**

![Example](https://github.com/WillPy45/Public-repository/blob/main/Filter/Imagenes_de_Salida/yard_binaryEdge_Umbral20.bmp)

- **Umbral 30**

![Example](https://github.com/WillPy45/Public-repository/blob/main/Filter/Imagenes_de_Salida/yard_binaryEdge_Umbral30.bmp)

- **Umbral 50**

![Example](https://github.com/WillPy45/Public-repository/blob/main/Filter/Imagenes_de_Salida/yard_binaryEdge_Umbral50.bmp)

- **Umbral 100**

![Example](https://github.com/WillPy45/Public-repository/blob/main/Filter/Imagenes_de_Salida/yard_binaryEdge_Umbral100.bmp)

- **Umbral 150**

![Example](https://github.com/WillPy45/Public-repository/blob/main/Filter/Imagenes_de_Salida/yard_binaryEdge_Umbral150.bmp)

- **Umbral 200**

![Example](https://github.com/WillPy45/Public-repository/blob/main/Filter/Imagenes_de_Salida/yard_binaryEdge_Umbral200.bmp)

**Umbral 250**

![Example](https://github.com/WillPy45/Public-repository/blob/main/Filter/Imagenes_de_Salida/yard_binaryEdge_Umbral255.bmp)
