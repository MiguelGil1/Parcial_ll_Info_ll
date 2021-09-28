#include "imageresize.h"

/// [ FUNCIONES QUE NO INCLUYEN REDIMENSIONAMIENTO ]


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
            sobreDivisionExact();
        }else {
            // Sí se consideran pixeles faltantes
            sobreNoDivisionExact();
        }
    }else if ((width >= mWidthL) && (height <= mHeightL)) {
        // En este caso se hace submuestreo sobre el ancho,
        // y sobremuestreo sobre el alto
    }else if((width <= mWidthL) && (height >= mHeightL)) {
        // En este caso de hace sobremuestreo sobre el ancho,
        // y submuestreo sobre el alto
    }
}


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



void ImageResize::SaveImgTxt()
{
    // El método realiza el proceso de guardado de la imagen redimensionda en un archivo txt

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



ImageResize::~ImageResize()
{
    // Destructor que elimina los arreglos dinámicos de la imagen

    for (int i = 0; i < mHeightL; i++) {
        delete [] mImgRed[i];
        delete [] mImgGreen[i];
        delete [] mImgBlue[i];
    }
    delete [] mImgRed;
    delete [] mImgGreen;
    delete [] mImgBlue;


}
