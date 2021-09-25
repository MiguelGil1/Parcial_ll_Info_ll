#include "imageresize.h"

ImageResize::ImageResize(){}

ImageResize::ImageResize(int _wLeds, int _hLeds, string _fileNameImg, string _fileNameTxt)
{
    // [ Inicializacion atributos básicos ]

    mWidthL = _wLeds;
    mHeightL = _hLeds;
    mFileNameImg = _fileNameImg;
    mFileNameTxt = _fileNameTxt;

    IMG = new QImage(mFileNameImg.c_str());

    // [ Inicializacion dinamica de matrices que contendrán los datos de la img redimensionada ]

    mImgRed = new int *[mHeightL];
    mImgGreen = new int *[mHeightL];
    mImgBlue = new int *[mHeightL];
    for (int i = 0; i < mHeightL; i++) {
        mImgRed[i] = new int [mWidthL];
        mImgGreen[i] = new int [mWidthL];
        mImgBlue[i] = new int [mWidthL];
    }
}

void ImageResize::categorizeAlgorithm()
{
    int width = IMG->width();
    int height = IMG->height();

//    float categW = width / mWidthL;
//    float categH = height / mHeightL;

    if ((width >= mWidthL) && (height >= mHeightL)) {
        // En este caso se realiza submuestreo

        if ((width % mWidthL == 0) && (height % mHeightL == 0)) {
            // En este caso no se consideran pixeles sobrantes
            subDivisionExact();
        }else {
            // Sí se consideran pixeles sobrantes
            subNoDivisionExact();
        }
    }else if ((width <= mWidthL) && (height <= mWidthL)) {
        // En este se hace sobremuestreo

        if ((mWidthL % width == 0) && (mHeightL % height == 0)) {
            // En este caso no se consideran pixeles faltantes
        }else {
            // Sí se consideran pixeles faltantes
        }
    }else if ((width >= mWidthL) && (height <= mHeightL)) {
        // En este caso se hace submuestreo sobre el ancho,
        // y sobremuestreo sobre el alto
    }else if((width <= mWidthL) && (height >= mHeightL)) {
        // En este caso de hace sobremuestreo sobre el ancho,
        // y submuestreo sobre el alto
    }


}

void ImageResize::subDivisionExact()
{
    int width = IMG->width();
    int height = IMG->height();


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
    // pixel dando su posicion, sumamos un a la coordenada x o y, dependiendo del caso.

    int pixelsColum = width/mWidthL;
    int pixelsRow = height/mHeightL;
    // Indicadores de desde dónde empezar a considerar los pixeles restantes
    int pixResColum = width % mWidthL;
    int pixResRow = height % mHeightL;

    int contPixR = 0; // Cantidad de pixeles a correr en la filas (row)
    int contPixC = 0; // Cantidad de pixeles a correr en las columanas (column)
    for (int i = 0; i < mHeightL; i++ ) {
        for (int j = 0; j < mWidthL; j++) {
            // Caso en que se corren los pixeles en la filas(row) y columnas(Colum) a la vez
            if ((mHeightL - pixResRow) <= i  && (mWidthL - pixResColum) <= j) { // 16 - 4
                mImgRed[i][j] = IMG->pixelColor(j*pixelsColum + ++contPixC, i*pixelsRow + ++contPixR).red();
                mImgGreen[i][j] = IMG->pixelColor(j*pixelsColum + ++contPixC, i*pixelsRow + ++contPixR).green();
                mImgBlue[i][j] = IMG->pixelColor(j*pixelsColum + ++contPixC, i*pixelsRow + ++contPixR).blue();
            }// Caso en que no se corren ni en la filas(row) y columnas(Colum)
            else if ((mHeightL - pixResRow) > i  && (mWidthL - pixResColum) > j){
                mImgRed[i][j] = IMG->pixelColor(j*pixelsColum, i*pixelsRow).red();
                mImgGreen[i][j] = IMG->pixelColor(j*pixelsColum, i*pixelsRow).green();
                mImgBlue[i][j] = IMG->pixelColor(j*pixelsColum, i*pixelsRow).blue();
            }// Caso en que solo se corren en las fillas(row)
            else if ((mHeightL - pixResRow) <= i) {
                mImgRed[i][j] = IMG->pixelColor(j*pixelsColum, i*pixelsRow + ++contPixR).red();
                mImgGreen[i][j] = IMG->pixelColor(j*pixelsColum, i*pixelsRow + ++contPixR).green();
                mImgBlue[i][j] = IMG->pixelColor(j*pixelsColum, i*pixelsRow + ++contPixR).blue();
            }// Caso en solo se corren en las columnas(column)
            else {
                mImgRed[i][j] = IMG->pixelColor(j*pixelsColum + ++contPixC, i*pixelsRow).red();
                mImgGreen[i][j] = IMG->pixelColor(j*pixelsColum + ++contPixC, i*pixelsRow).green();
                mImgBlue[i][j] = IMG->pixelColor(j*pixelsColum + ++contPixC, i*pixelsRow).blue();
            }
        }
    }

}


void ImageResize::SaveImgTxt()
{
    ofstream archImg(mFileNameTxt);

    if (!archImg.is_open()) {
        cout << "Error al abrir archivo" << endl;
        exit(1);
    }

    // [ Se almacena el color Red ]
    archImg << "uint8_t RedMatrix [256] = { \n";
    for (int i = 0; i < mHeightL; i++) {

        for (int j = 0; j < mWidthL; j++) {
            // Se considera el 255 por el error de tinkerkad
            if (mImgRed[i][j] == 255) {
                mImgRed[i][j] = 254;
            }
            // Considero el ultimo elemento, no debe llevar coma (,)
            if ((i == mHeightL - 1) && (j == mWidthL - 1)) {
                archImg << mImgRed[i][j];
            }else {
                archImg << mImgRed[i][j] << ", ";
            }
        }
        archImg << "\n";
    }
    archImg << "}; \n\n";

    // [ Se almacena el color Green ]
    archImg << "uint8_t GreenMatrix [256] = { \n";
    for (int i = 0; i < mHeightL; i++) {

        for (int j = 0; j < mWidthL; j++) {
            // Se considera el 255 por el error de tinkerkad
            if (mImgGreen[i][j] == 255) {
                mImgGreen[i][j] = 254;
            }
            // Considero el ultimo elemento, no debe llevar coma (,)
            if ((i == mHeightL - 1) && (j == mWidthL - 1)) {
                archImg << mImgGreen[i][j];
            }else {
                archImg << mImgGreen[i][j] << ", ";
            }
        }
        archImg << "\n";
    }
    archImg << "}; \n\n";

    // [ Se almacena el color Blue ]
    archImg << "uint8_t BlueMatrix [256] = { \n";
    for (int i = 0; i < mHeightL; i++) {

        for (int j = 0; j < mWidthL; j++) {
            // Se considera el 255 por el error de tinkerkad
            if (mImgBlue[i][j] == 255) {
                mImgBlue[i][j] = 254;
            }
            // Considero el ultimo elemento, no debe llevar coma (,)
            if ((i == mHeightL - 1) && (j == mWidthL - 1)) {
                archImg << mImgBlue[i][j];
            }else {
                archImg << mImgBlue[i][j] << ", ";
            }
        }
        archImg << "\n";
    }
    archImg << "}; \n\n";

    archImg.close();

}
