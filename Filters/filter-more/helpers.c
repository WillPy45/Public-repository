#include "helpers.h"
#include "math.h"
#include <stdlib.h>
#include <stdio.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
  

    // grayscaleValue is an average of RED, GREEN, and BLUE values
    for (int j = 0; j < height; j++){
        for (int k = 0; k < width; k++){
            // Calculate the grayscale value
            BYTE grayscaleValue = round((image[j][k].rgbtBlue + image[j][k].rgbtGreen + image[j][k].rgbtRed) / 3.0);

            // Assign the grayscale value of all color components
            image[j][k].rgbtBlue = grayscaleValue;
            image[j][k].rgbtGreen = grayscaleValue;
            image[j][k].rgbtRed = grayscaleValue;
        }
    }
    return;
}


// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int j = 0; j < height; j++){
        for (int k = 0; k < (width/2); k++){
            //swap
            RGBTRIPLE tmp = image[j][k];
            image[j][k] = image[j][width - k - 1];
            image[j][width - k - 1] = tmp;
        }
    }

    return;
}



void copyRGBTRIPLE(int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE copyImage[height][width]){
     for (int height_It = 0; height_It < height; height_It++){
        for (int width_It = 0; width_It < width; width_It++){
            copyImage[height_It][width_It].rgbtRed = image[height_It][width_It].rgbtRed;
            copyImage[height_It][width_It].rgbtGreen = image[height_It][width_It].rgbtGreen;
            copyImage[height_It][width_It].rgbtBlue = image[height_It][width_It].rgbtBlue;


        }
    }
}


void blurPixel(int x, int y, int height, int width, RGBTRIPLE copyImage[height][width], RGBTRIPLE *imagePixel){
    int sumRed = 0;
    int sumGreen = 0;
    int sumBlue = 0;
    int validPixels = 0; //Incluye el mismo pixel seleccionado + sus vecinos

    for (int image_y = y - 1; image_y <= y + 1; image_y++){
        for (int image_x = x - 1; image_x <= x + 1; image_x++){
            if (image_x >= 0 && image_x < width && image_y >= 0 && image_y < height){
                sumRed += copyImage[image_y][image_x].rgbtRed;
                sumGreen += copyImage[image_y][image_x].rgbtGreen;
                sumBlue += copyImage[image_y][image_x].rgbtBlue;
                validPixels++;
            }
        }

    }

    //Aplicacion del valor de blur sumatoriaValores/cantidadDePixeles
    if (validPixels > 0){
        imagePixel->rgbtRed = round((float) sumRed/validPixels);
        imagePixel->rgbtGreen = round((float) sumGreen/validPixels);
        imagePixel->rgbtBlue = round((float)sumBlue/validPixels);
    }
}

void blurAplication(int height, int width, RGBTRIPLE image[height][width], RGBTRIPLE copyImage[height][width]){
    // Aplicar el desenfoque a todos los píxeles
    for (int j = 0; j < height; j++) {
        for (int k = 0; k < width; k++) {
            blurPixel(k, j, height, width, copyImage, &image[j][k]);
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Crear matriz auxiliar para no trabajar sobre arrays modificados en tiempo real
    RGBTRIPLE(*copyImage)[width] = calloc(height, sizeof(RGBTRIPLE[width]));
    if (copyImage == NULL)
    {
        printf("Not enough memory to store image.\n");
        return;
    }

    // Hacer una copia de la matriz original
    copyRGBTRIPLE(height, width, image, copyImage);

    //Aplicar el flitro
    blurAplication(height, width, image, copyImage);

    free(copyImage);
    return;
}


// Detect edges

//Convulsion 3*3

void ConvulsionKernelsGxGy(int height, int width, RGBTRIPLE imagen_Origen[height][width], RGBTRIPLE imagen_Convulsionado[height][width], int kernelGx[3][3], int kernelGy[3][3]){

    int tempValorConvulsionGx_Red = 0;
    int tempValorConvulsionGx_Green = 0;
    int tempValorConvulsionGx_Blue = 0;

    int tempValorConvulsionGy_Red = 0;
    int tempValorConvulsionGy_Green = 0;
    int tempValorConvulsionGy_Blue = 0;

    int magnitudRed = 0;
    int magnitudGreen = 0;
    int magnitudBlue = 0;

    // Recorrer todos los píxeles de la imagen (exceptuando los bordes)
    for (int height_it = 0; height_it < height ; height_it++)
    {
        for (int width_it = 0; width_it < width ; width_it++)
        {
            tempValorConvulsionGx_Red = 0;
            tempValorConvulsionGy_Red = 0;

            tempValorConvulsionGx_Green = 0;
            tempValorConvulsionGy_Green = 0;

            tempValorConvulsionGx_Blue = 0;
            tempValorConvulsionGy_Blue = 0;

            for (int j = height_it - 1, iteradorKernel_h = 0; j <= height_it + 1; j++, iteradorKernel_h++)
            {
                for (int k = width_it - 1, iteradorKernel_w = 0; k <= width_it + 1; k++, iteradorKernel_w++)
                {


                  // Verificar si el píxel vecino está dentro de los límites de la imagen
                    if (j >= 0 && j < height && k >= 0 && k < width) {
                        // Si está dentro de los límites, usamos el valor del píxel original
                        tempValorConvulsionGx_Red += imagen_Origen[j][k].rgbtRed * kernelGx[iteradorKernel_h][iteradorKernel_w];
                        tempValorConvulsionGy_Red += imagen_Origen[j][k].rgbtRed * kernelGy[iteradorKernel_h][iteradorKernel_w];

                        tempValorConvulsionGx_Green += imagen_Origen[j][k].rgbtGreen * kernelGx[iteradorKernel_h][iteradorKernel_w];
                        tempValorConvulsionGy_Green += imagen_Origen[j][k].rgbtGreen * kernelGy[iteradorKernel_h][iteradorKernel_w];

                        tempValorConvulsionGx_Blue += imagen_Origen[j][k].rgbtBlue * kernelGx[iteradorKernel_h][iteradorKernel_w];
                        tempValorConvulsionGy_Blue += imagen_Origen[j][k].rgbtBlue * kernelGy[iteradorKernel_h][iteradorKernel_w];
                    } else {
                        // Si el píxel vecino está fuera de los límites, se utiliza el valor 0 (padding cero)
                        // Esto es como si el píxel fuera negro (0) para los bordes
                        tempValorConvulsionGx_Red += 0 * kernelGx[iteradorKernel_h][iteradorKernel_w];
                        tempValorConvulsionGy_Red += 0 * kernelGy[iteradorKernel_h][iteradorKernel_w];

                        tempValorConvulsionGx_Green += 0 * kernelGx[iteradorKernel_h][iteradorKernel_w];
                        tempValorConvulsionGy_Green += 0 * kernelGy[iteradorKernel_h][iteradorKernel_w];

                        tempValorConvulsionGx_Blue += 0 * kernelGx[iteradorKernel_h][iteradorKernel_w];
                        tempValorConvulsionGy_Blue += 0 * kernelGy[iteradorKernel_h][iteradorKernel_w];
                    }

                }
            }

            // Asignar el valor convolucionado al píxel en la imagen de salida
            magnitudRed = round( sqrt(tempValorConvulsionGx_Red  * tempValorConvulsionGx_Red + tempValorConvulsionGy_Red * tempValorConvulsionGy_Red));
            magnitudGreen = round( sqrt(tempValorConvulsionGx_Green  * tempValorConvulsionGx_Green + tempValorConvulsionGy_Green * tempValorConvulsionGy_Green));
            magnitudBlue = round( sqrt(tempValorConvulsionGx_Blue  * tempValorConvulsionGx_Blue + tempValorConvulsionGy_Blue * tempValorConvulsionGy_Blue));

            // Normalizar la magnitud para que no exceda 255

            magnitudRed = fmin(255, magnitudRed);
            magnitudGreen = fmin(255, magnitudGreen);
            magnitudBlue = fmin(255, magnitudBlue);

            //Aplicacion de las magnitudes a los pixeles de la imagen original
            imagen_Convulsionado[height_it][width_it].rgbtRed = magnitudRed;
            imagen_Convulsionado[height_it][width_it].rgbtGreen = magnitudGreen;
            imagen_Convulsionado[height_it][width_it].rgbtBlue = magnitudBlue;
        }
    }

}





void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Aplicar el filtro de escala de grises (grayscale) para trabajar con una intensidad
    //grayscale(height, width, image);

    // Crear matriz auxiliar para no trabajar sobre arrays modificados en tiempo real
    RGBTRIPLE(*copyImage)[width] = calloc(height, sizeof(RGBTRIPLE[width]));
    if (copyImage == NULL)
    {
        printf("Not enough memory to store image.\n");
        return;
    }

    // Hacer una copia de la matriz original
    copyRGBTRIPLE(height, width, image, copyImage);

    //Deteccion de bordes mediante Sobel Operator
    //Declaracion de Kernels Gx y Gy

    int Gx[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int Gy[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };


    ConvulsionKernelsGxGy(height, width, copyImage, image, Gx, Gy);

    free(copyImage);

    return;
}





// Deteccion de bordes con umbral y escala de grises
void ConvulsionKernelsGxGy_Grayscale(int height, int width, int Umbral, RGBTRIPLE imagen_Origen[height][width], RGBTRIPLE imagen_Convulsionado[height][width], int kernelGx[3][3], int kernelGy[3][3]){

    int tempValorConvulsionGx = 0;
    int tempValorConvulsionGy = 0;
    int magnitud = 0;

    // Recorrer todos los píxeles de la imagen (exceptuando los bordes)
    for (int height_it = 0; height_it < height ; height_it++)
    {
        for (int width_it = 0; width_it < width ; width_it++)
        {
            tempValorConvulsionGx = 0;
            tempValorConvulsionGy = 0;

            for (int j = height_it - 1, iteradorKernel_h = 0; j <= height_it + 1; j++, iteradorKernel_h++)
            {
                for (int k = width_it - 1, iteradorKernel_w = 0; k <= width_it + 1; k++, iteradorKernel_w++)
                {


                  // Verificar si el píxel vecino está dentro de los límites de la imagen
                    if (j >= 0 && j < height && k >= 0 && k < width) {
                        // Si está dentro de los límites, usamos el valor del píxel original
                        tempValorConvulsionGx += imagen_Origen[j][k].rgbtRed * kernelGx[iteradorKernel_h][iteradorKernel_w];
                        tempValorConvulsionGy += imagen_Origen[j][k].rgbtRed * kernelGy[iteradorKernel_h][iteradorKernel_w];

                    } else {
                        // Si el píxel vecino está fuera de los límites, se utiliza el valor 0 (padding cero)
                        // Esto es como si el píxel fuera negro (0) para los bordes
                        tempValorConvulsionGx += 0 * kernelGx[iteradorKernel_h][iteradorKernel_w];
                        tempValorConvulsionGy += 0 * kernelGy[iteradorKernel_h][iteradorKernel_w];


                    }

                }
            }

            // Asignar el valor convolucionado al píxel en la imagen de salida
            magnitud = round( sqrt(tempValorConvulsionGx * tempValorConvulsionGx + tempValorConvulsionGy * tempValorConvulsionGy));

            // Normalizar la magnitud para que no exceda 255

            magnitud = fmin(255, magnitud);


            //Aplicacion de los valores binarios, blanco para borde y negro para no borde
            if (magnitud >= Umbral){
                imagen_Convulsionado[height_it][width_it].rgbtRed = 0xff;
                imagen_Convulsionado[height_it][width_it].rgbtGreen = 0xff;
                imagen_Convulsionado[height_it][width_it].rgbtBlue = 0xff;

            }else{
                imagen_Convulsionado[height_it][width_it].rgbtRed = 0x0;
                imagen_Convulsionado[height_it][width_it].rgbtGreen = 0x0;
                imagen_Convulsionado[height_it][width_it].rgbtBlue = 0x0;
            }

        }
    }

}





void BinaryEdges(int height, int width, RGBTRIPLE image[height][width], int Umbral) //Blanco y negro (255 y 0)
{
    // Aplicar el filtro de escala de grises (grayscale) para trabajar con una intensidad
    grayscale(height, width, image);

    // Crear matriz auxiliar para no trabajar sobre arrays modificados en tiempo real
    RGBTRIPLE(*copyImage)[width] = calloc(height, sizeof(RGBTRIPLE[width]));
    if (copyImage == NULL)
    {
        printf("Not enough memory to store image.\n");
        return;
    }

    // Hacer una copia de la matriz original
    copyRGBTRIPLE(height, width, image, copyImage);

    //Deteccion de bordes mediante Sobel Operator
    //Declaracion de Kernels Gx y Gy

    int Gx[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };

    int Gy[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };


    ConvulsionKernelsGxGy_Grayscale(height, width, Umbral, copyImage, image, Gx, Gy);

    //Se espera una imágen binaria, o sea de dos valores, 255 y 0

    free(copyImage);
    return;
}
