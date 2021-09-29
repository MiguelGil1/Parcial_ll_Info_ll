#include "imageresize.h"

// Se habla varias veces de "divisionExact".
// Se refiere a que: en submuestreo, la division entre
// el tamano de la imagen y el de matriz es o no exacta;
// y el sobremuestreo se refiere a que la division entre
// el tamano de la matriz y el de la imagen es o no exacta.

/// [ METODOS DE SUBMUESTREO ]

void ImageResize::subDivisionExact()
{
    int width = IMG->width();
    int height = IMG->height();

    // Indican el tamaño del salto
    int pixelsColum = width/mWidthL;
    int pixelsRow = height/mHeightL;

    for (int i = 0; i < mHeightL ; i++) {
        for (int j = 0; j < mWidthL; j++) {
            mImgRed[i][j] = IMG->pixelColor(j*pixelsColum, i*pixelsRow).red();
            mImgGreen[i][j] = IMG->pixelColor(j*pixelsColum, i*pixelsRow).green();
            mImgBlue[i][j] = IMG->pixelColor(j*pixelsColum, i*pixelsRow).blue();
        }
    }
}

void ImageResize::subNoDivisionExact()
{
    int width = IMG->width();
    int height = IMG->height();
    // La idea de este caso es el siguiente:
    // Como la division no es exacta, si no se consideran los pixeles restantes se pierde informacion
    // posiblemente importante. Esta cantidad de pixeles que restan se obtienen con las variables:
    // pixResColum, pixResRow.
    // Entonces la forma de considerar estos pixeles restantes con que, cada vez que se coje un
    // pixel danda su posicion, sumamos uno a la coordenada x o y, dependiendo del caso.

    int pixelsColum = width/mWidthL;
    int pixelsRow = height/mHeightL;

    // Indicadores de desde dónde empezar a considerar los pixeles restantes
    int pixResColum = width % mWidthL;
    int pixResRow = height % mHeightL;

    int contPixR = 0; // Cantidad de pixeles a correr en la filas (row)
    int contPixC = 0; // Cantidad de pixeles a correr en las columanas (column)
    for (int i = 0; i < mHeightL; i++ ) {
        if ((mHeightL - pixResRow) <= i) {
            ++contPixR;
        }
        for (int j = 0; j < mWidthL; j++) {
            // Caso en que se corren los pixeles en la filas(row) y columnas(Colum) a la vez
            if ((mHeightL - pixResRow) <= i  && (mWidthL - pixResColum) <= j) { // 16 - 4
                ++contPixC;
                mImgRed[i][j] = IMG->pixelColor(j*pixelsColum + contPixC, i*pixelsRow + contPixR).red();
                mImgGreen[i][j] = IMG->pixelColor(j*pixelsColum + contPixC, i*pixelsRow + contPixR).green();
                mImgBlue[i][j] = IMG->pixelColor(j*pixelsColum + contPixC, i*pixelsRow + contPixR).blue();
            }// Caso en que no se corren ni en la filas(row) y columnas(Colum)
            else if ((mHeightL - pixResRow) > i  && (mWidthL - pixResColum) > j){
                mImgRed[i][j] = IMG->pixelColor(j*pixelsColum, i*pixelsRow).red();
                mImgGreen[i][j] = IMG->pixelColor(j*pixelsColum, i*pixelsRow).green();
                mImgBlue[i][j] = IMG->pixelColor(j*pixelsColum, i*pixelsRow).blue();
            }// Caso en que solo se corren en las fillas(row)
            else if ((mHeightL - pixResRow) <= i) {
                mImgRed[i][j] = IMG->pixelColor(j*pixelsColum, i*pixelsRow + contPixR).red();
                mImgGreen[i][j] = IMG->pixelColor(j*pixelsColum, i*pixelsRow + contPixR).green();
                mImgBlue[i][j] = IMG->pixelColor(j*pixelsColum, i*pixelsRow + contPixR).blue();
            }// Caso en solo se corren en las columnas(column)
            else {
                ++contPixC;
                mImgRed[i][j] = IMG->pixelColor(j*pixelsColum + contPixC, i*pixelsRow).red();
                mImgGreen[i][j] = IMG->pixelColor(j*pixelsColum + contPixC, i*pixelsRow).green();
                mImgBlue[i][j] = IMG->pixelColor(j*pixelsColum + contPixC, i*pixelsRow).blue();
            }
        }
        contPixC = 0;
    }
}

/// [ METODOS DE SOBREMUESTREO ]

void ImageResize::sobreDivisionExact()
{
    int width = IMG->width();
    int height = IMG->height();

    // Indican la cantidad de veces a replicar un pixel, ya sea de columna o fila
    int pixelsColum = mWidthL/width;
    int pixelsRow = mHeightL/height;

    int red;
    int green;
    int blue;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // Se coge el color a replicar
            red = IMG->pixelColor(j, i).red();
            green = IMG->pixelColor(j, i).green();
            blue = IMG->pixelColor(j, i).blue();
            // En la matriz de leds, se pone repetitivamene tal color
            for (int iCopy = 0; iCopy < pixelsRow; iCopy++) {
                for (int jCopy = 0; jCopy < pixelsColum; jCopy++) {
                    mImgRed[i*pixelsRow + iCopy][j*pixelsColum + jCopy] = red;
                    mImgGreen[i*pixelsRow + iCopy][j*pixelsColum + jCopy] = green;
                    mImgBlue[i*pixelsRow + iCopy][j*pixelsColum + jCopy] = blue;
                }
            }
        }
    }
}

void ImageResize::sobreNoDivisionExact()
{
    int width = IMG->width();
    int height = IMG->height();

    // Indican la cantidad de veces a replicar un pixel, ya sea de columna o fila
    int pixelsColum = mWidthL/width;
    int pixelsRow = mHeightL/height;

    // Indican la cantidad de pixels faltantes para completar la matriz de leds
    int pixResColum = mWidthL % width;
    int pixResRow = mHeightL % height;

    // Contadores auxuliares para el relleno de pixeles en filas y columnas
    // Se inicializan en -1 porque en caso contrario indexan la matriz en posiciones inválidas
    int contPixR = -1;
    int contPixC = -1;

    int red;
    int green;
    int blue;

    for (int i = 0; i < height; i++) {
        if ((height - pixResRow) <= i) {
            contPixR++;
        }

        for (int j = 0; j < width; j++) {
            red = IMG->pixelColor(j, i).red();
            green = IMG->pixelColor(j, i).green();
            blue = IMG->pixelColor(j, i).blue();

            // Caso en que rellenan con pixeles en la filas(row) y las columnas(colum)
            if ((height - pixResRow) <= i  && (width - pixResColum) <= j) {
                contPixC++;
                for (int iCopy = 0; iCopy < pixelsRow + 1; iCopy++) {
                    for (int jCopy = 0; jCopy < pixelsColum + 1; jCopy++) {
                        mImgRed[i*pixelsRow + iCopy + contPixR][j*pixelsColum + jCopy + contPixC] = red;
                        mImgGreen[i*pixelsRow + iCopy + contPixR][j*pixelsColum + jCopy + contPixC] = green;
                        mImgBlue[i*pixelsRow + iCopy + contPixR][j*pixelsColum + jCopy + contPixC] = blue;
                    }
                }
            }// Caso en que no se rellenan con pixeles ni en las filas(row) ni en las columnas(colum)
            else if ((height - pixResRow) > i && (width - pixResColum) > j) {
                for (int iCopy = 0; iCopy < pixelsRow; iCopy++) {
                    for (int jCopy = 0; jCopy < pixelsColum; jCopy++) {
                        mImgRed[i*pixelsRow + iCopy][j*pixelsColum + jCopy] = red;
                        mImgGreen[i*pixelsRow + iCopy][j*pixelsColum + jCopy] = green;
                        mImgBlue[i*pixelsRow + iCopy][j*pixelsColum + jCopy] = blue;
                    }
                }
            }// Caso en que se rellenan con pixeles solo en las filas(row)
            else if ((height - pixResRow) <= i) {
                for (int iCopy = 0; iCopy < pixelsRow + 1; iCopy++) {
                    for (int jCopy = 0; jCopy < pixelsColum; jCopy++) {
                        mImgRed[i*pixelsRow + iCopy + contPixR][j*pixelsColum + jCopy] = red;
                        mImgGreen[i*pixelsRow + iCopy + contPixR][j*pixelsColum + jCopy] = green;
                        mImgBlue[i*pixelsRow + iCopy + contPixR][j*pixelsColum + jCopy] = blue;
                    }
                }
            }// Caso en que se rellenan con pixeles solo en las columnas(colum)
            else {
                contPixC++;
                for (int iCopy = 0; iCopy < pixelsRow; iCopy++) {
                    for (int jCopy = 0; jCopy < pixelsColum + 1; jCopy++) {
                        mImgRed[i*pixelsRow + iCopy][j*pixelsColum + jCopy + contPixC] = red;
                        mImgGreen[i*pixelsRow + iCopy][j*pixelsColum + jCopy + contPixC] = green;
                        mImgBlue[i*pixelsRow + iCopy][j*pixelsColum + jCopy + contPixC] = blue;
                    }
                }
            }
        }contPixC = -1;
    }
}
