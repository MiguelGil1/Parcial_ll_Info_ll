#include "imageresize.h"

ImageResize::ImageResize(){}

ImageResize::ImageResize(int _wLeds, int _hLeds, string _fileName)
{
    mWidthL = float(_wLeds);
    mHeightL = float(_hLeds);
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
    float width = IMG->width();
    float height = IMG->height();

    float categW = width / mWidthL;
    float categH = height / mHeightL;


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
