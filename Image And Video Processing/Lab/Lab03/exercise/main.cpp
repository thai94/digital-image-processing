#include <iostream>
#include "Blur.h"
#include "Convolution.h"
using namespace std;


int main(int, char**) {

    Mat sourceImage = imread("./../test2.jpeg");
    Mat blurImage;
    // Blur blur = Blur();
    // blur.BlurImage(sourceImage, blurImage, 5, 5, 2);

    

    Convolution convolution = Convolution();
    convolution.GenGaussKener(5, 5, 1.0);
    convolution.DoConvolution(sourceImage, blurImage);

    namedWindow("image", WINDOW_NORMAL);
    resizeWindow("image", 800, 600);

    imshow("image", blurImage);
    waitKey(0);
}
