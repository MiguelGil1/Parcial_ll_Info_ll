#include "imageresize.h"

ImageResize::ImageResize(){}

ImageResize::ImageResize(int _wLeds, int _hLeds, string _fileName)
{
    // [ Inicializacion atributos básicos ]

    mWidthL = _wLeds;
    mHeightL = _hLeds;
    mFileName = _fileName;

    IMG = new QImage("../Algorithm_Resize_Img/Images/img.jpg");

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
        }else {
            // Sí se consideran pixeles sobrantes
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

void ImageResize::SaveImgTxt()
{
    ofstream archImg(mFileName);

    // [ Se almacena el color Red ]
    archImg << "uint8_t RedMatrix [256] = { \n";
    for (int i = 0; i < mHeightL; i++) {

        for (int j = 0; j < mWidthL; j++) {
            archImg << mImgRed[i][j] << ", ";
        }
        archImg << "\n";
    }
    archImg << "}; \n\n";

    // [ Se almacena el color Green ]
    archImg << "uint8_t GreenMatrix [256] = { \n";
    for (int i = 0; i < mHeightL; i++) {

        for (int j = 0; j < mWidthL; j++) {
            archImg << mImgGreen[i][j] << ", ";
        }
        archImg << "\n";
    }
    archImg << "}; \n\n";

    // [ Se almacena el color Blue ]
    archImg << "uint8_t BlueMatrix [256] = { \n";
    for (int i = 0; i < mHeightL; i++) {

        for (int j = 0; j < mWidthL; j++) {
            archImg << mImgBlue[i][j] << ", ";
        }
        archImg << "\n";
    }
    archImg << "}; \n\n";

    archImg.close();

}
