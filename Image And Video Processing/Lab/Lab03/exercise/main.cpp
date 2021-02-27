#include <iostream>
#include "Blur.h"
#include "Convolution.h"
#include "EdgeDetector.h"
using namespace std;


int main(int, char**) {

    Mat sourceImage = imread("./../test1.png");
    Mat blurImage;
    // Blur blur = Blur();
    // blur.BlurImage(sourceImage, blurImage, 5, 5, 2);

    

    // Convolution convolution = Convolution();
    // convolution.GenGaussKener(5, 5, 1.0);
    // convolution.DoConvolution(sourceImage, blurImage);

    // namedWindow("image", WINDOW_NORMAL);
    // resizeWindow("image", 800, 600);

    EdgeDetector edgeDetector = EdgeDetector();
    Mat destImage;
    edgeDetector.DetectEdge(sourceImage, destImage, 5, 5, 4);

    imshow("image", destImage);
    waitKey(0);
}
