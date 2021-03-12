#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/core.hpp>
using namespace std;
using namespace cv;

int main() {
    Mat img = imread("./../test1.jpg");
    imshow("Image Test", img);
    waitKey(0);
}
