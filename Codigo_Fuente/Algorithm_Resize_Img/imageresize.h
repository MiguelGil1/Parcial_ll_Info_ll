#ifndef IMAGERESIZE_H
#define IMAGERESIZE_H

#include <iostream>
#include <QImage>
#include <fstream>

using namespace std;

class ImageResize
{
public:
    // ImageResize();
    ~ImageResize();
    ImageResize(int _wLeds, int _hLeds, string _fileNameImg, string _fileNameTxt);
    void SaveImgTxt();

    // [ SUBMUESTREO ]
    void subDivisionExact();
    void subNoDivisionExact();

    // [ SOBREMUESTREO ]
    void sobreDivisionExact();
    void sobreNoDivisionExact();

    void categorizeAlgorithm();
    void Sobremuestreo();

private:

    int mWidthL;
    int mHeightL;
    string mFileNameImg;
    string mFileNameTxt;
    QImage *IMG; // Maverick del futuro, no se le olvide eliminar lo del heap -> delete[];

    int **mImgRed;
    int **mImgGreen;
    int **mImgBlue;
};

#endif // IMAGERESIZE_H