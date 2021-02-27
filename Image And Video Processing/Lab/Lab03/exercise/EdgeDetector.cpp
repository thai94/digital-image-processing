#include "EdgeDetector.h"

int RGB2GrayScale(const Mat &sourceImage, Mat &destinationImage)
{
    if (sourceImage.empty())
    {
        return -1;
    }

    int rows = sourceImage.rows;
    int cols = sourceImage.cols;
    int chanels = sourceImage.channels();

    destinationImage = Mat(rows, cols, CV_8UC1);

    for (int i = 0; i < rows; i++)
    {

        const uchar *pRow = sourceImage.ptr<uchar>(i);
        uchar *destRow = destinationImage.ptr<uchar>(i);
        for (int j = 0; j < cols; j++, pRow += chanels, destRow += 1)
        {
            uchar blue = pRow[0];
            uchar green = pRow[1];
            uchar red = pRow[2];

            uchar grayValue = floor(0.11 * blue + 0.59 * green + 0.30 * red);
            destRow[0] = grayValue;
        }
    }

    return 1;
}

int imgGradientX(const Mat& sourceImage, Mat& destinationImage) {

    if (sourceImage.empty())
    {
        return -1;
    }

    int threshold = 10;

    Mat grayImage;
    RGB2GrayScale(sourceImage, grayImage);

    int rows = grayImage.rows;
    int cols = grayImage.cols;
    int chanels = grayImage.channels();

    destinationImage = Mat(rows, cols, CV_MAKETYPE(CV_8U, chanels));

    for (int i = 0; i < rows; i++) {

        uchar *pRow = grayImage.ptr<uchar>(i);
        uchar *destRow = destinationImage.ptr<uchar>(i);
        for (int j = 0; j < cols - 1; j++, pRow += chanels, destRow += chanels) {
            int ix = (pRow + 1)[0] - pRow[0];
            destRow[0] = ix >= threshold ? 240 : 10;
        }
    }
    return 1;
}

int imgGradientY(const Mat& sourceImage, Mat& destinationImage) {
    if (sourceImage.empty())
    {
        return -1;
    }

    int threshold = 10;

    Mat grayImage;
    RGB2GrayScale(sourceImage, grayImage);

    int rows = grayImage.rows;
    int cols = grayImage.cols;
    int chanels = grayImage.channels();

    destinationImage = Mat(rows, cols, CV_MAKETYPE(CV_8U, chanels));

    for (int i = 0; i < rows - 1; i++) {

        uchar *pRow = grayImage.ptr<uchar>(i);
        uchar *destRow = destinationImage.ptr<uchar>(i);
        for (int j = 0; j < cols; j++, pRow += chanels, destRow += chanels) {
            
            uchar *pRowNext = grayImage.ptr<uchar>(i + 1);
            int iy = (pRowNext + j * chanels)[0] - pRow[0];
            destRow[0] = iy >= threshold ? 240 : 10;;
        }
    }
    return 1;
}

int imgGradientXY(const Mat& sourceImage, Mat& destinationImage) {
    
    if (sourceImage.empty())
    {
        return -1;
    }

    int threshold = 10;

    Mat grayImage;
    RGB2GrayScale(sourceImage, grayImage);
    int rows = grayImage.rows;
    int cols = grayImage.cols;
    int chanels = grayImage.channels();

    destinationImage = Mat(rows, cols, CV_MAKETYPE(CV_8U, chanels));

    for (int i = 0; i < rows; i++) {

        uchar *pRow = grayImage.ptr<uchar>(i);
        uchar *destRow = destinationImage.ptr<uchar>(i);
        for (int j = 0; j < cols - 1; j++, pRow += chanels, destRow += chanels) {
            int ix = (pRow + 1)[0] - pRow[0];

            uchar *pRowNext = grayImage.ptr<uchar>(i + 1);
            int iy = (pRowNext + j * chanels)[0] - pRow[0];

            int ixy = sqrt(ix * ix + iy * iy);

            destRow[0] = ixy >= threshold ? 240 : 10;
        }
    }
    return 1;
}

int EdgeDetector::DetectEdge(const Mat& sourceImage, Mat& destinationImage, int kWidth, int kHeight, int method) {

    if(method == 1) {
        return imgGradientX(sourceImage, destinationImage);
    } else if (method == 2) {
        return imgGradientY(sourceImage, destinationImage);
    } else if (method == 3) {
        return imgGradientXY(sourceImage, destinationImage);
    }

    return 1;
}