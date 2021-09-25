#ifndef IMAGERESIZE_H
#define IMAGERESIZE_H

#include <iostream>
#include <QImage>
#include <fstream>

using namespace std;

class ImageResize
{
public:
    ImageResize();
    ImageResize(int _wLeds, int _hLeds, string _fileName);
    void SaveImgTxt();

    void categorizeAlgorithm();
    void Sobremuestreo();

private:

    int mWidthL;
    int mHeightL;
    string mFileName;
    QImage *IMG; // Maverick del futuro, no se le olvide eliminar lo del heap -> delete[];

    int **mImgRed;
    int **mImgGreen;
    int **mImgBlue;
};

#endif // IMAGERESIZE_H
