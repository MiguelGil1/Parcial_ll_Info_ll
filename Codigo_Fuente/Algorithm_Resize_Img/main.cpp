#include <iostream>
#include <QImage>

#include <imageresize.h>


using namespace std;
#define PATH_TO_FILES "../Algorithm_Resize_Img/BD/"
int main()
{

    string fileName = "";
    string fileTxt = "ImgResize.txt";
    cout << "Ingrese nombre de la imagen a redimensioar (ej: brasil.png): ";
    cin >> fileName;
    ImageResize imgR(16, 16, PATH_TO_FILES + fileName, PATH_TO_FILES + fileTxt);
    imgR.categorizeAlgorithm();
    imgR.SaveImgTxt();

    return 0;
}
