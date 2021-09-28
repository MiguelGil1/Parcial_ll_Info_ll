#include <iostream>
#include <QImage>

#include <imageresize.h>


using namespace std;

int main()
{

    string fileName = "../Algorithm_Resize_Img/BD/brasil10x7.jpg";
    string fileTxt = "../Algorithm_Resize_Img/BD/ImgResize.txt";

    ImageResize imgR(16, 16, fileName, fileTxt);
    imgR.categorizeAlgorithm();
    imgR.SaveImgTxt();

    return 0;
}
