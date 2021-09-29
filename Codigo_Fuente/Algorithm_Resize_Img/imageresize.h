#ifndef IMAGERESIZE_H
#define IMAGERESIZE_H

#include <iostream>
#include <QImage>
#include <fstream>

using namespace std;

class ImageResize
{
public:

    ~ImageResize();

    ImageResize(int _wLeds, int _hLeds, string _fileNameImg, string _fileNameTxt);

    // [ SUBMUESTREO ]
    // Submuestreo en donde la division es exacta
    void subDivisionExact();
    // Submuestreo en donde la division no es exacta
    void subNoDivisionExact();

    // [ SOBREMUESTREO ]
    // Analogo a submuestreo
    void sobreDivisionExact();
    void sobreNoDivisionExact();

    // [ SUB Y SOBRE A LA VEZ ]


    // A partir de las dimensiones de la matriz de leds
    // y la imagen, determina que metodo, entre los de
    // submuestreo y sobremuestreo, se debe ejecutar para
    // la correcta redimension de la imagen
    void categorizeAlgorithm();

    // Una vez realizado el proceso de redimension, se
    // ejecuta para guardar la informacion en un .txt
    void SaveImgTxt();

private:

    int mWidthL; // Ancho de matriz de leds
    int mHeightL; // Alto/largo de matriz de leds

    // Ruta y nombre de la imagen
    string mFileNameImg;

    // Nombre y ruta del archivo .txt
    string mFileNameTxt;

    // Objeto que contiene la informacion de la imagen
    QImage *IMG;

    // [ MATRICES DE CADA COLOR]
    int **mImgRed;
    int **mImgGreen;
    int **mImgBlue;
};

#endif // IMAGERESIZE_H
