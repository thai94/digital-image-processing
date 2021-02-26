#include <iostream>
#include "Blur.h"
using namespace std;


int main(int, char**) {

    Mat sourceImage = imread("./../test1.png");
    Mat blurImage;
    Blur blur = Blur();
    blur.BlurImage(sourceImage, blurImage, 5, 5, 2);

    imshow("blur image", blurImage);
    waitKey(0);
}
