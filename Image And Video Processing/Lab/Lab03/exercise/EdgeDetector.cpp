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

int imgGradientX(const Mat &sourceImage, Mat &destinationImage)
{

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

    for (int i = 0; i < rows; i++)
    {

        uchar *pRow = grayImage.ptr<uchar>(i);
        uchar *destRow = destinationImage.ptr<uchar>(i);
        for (int j = 0; j < cols - 1; j++, pRow += chanels, destRow += chanels)
        {
            int ix = (pRow + 1)[0] - pRow[0];
            destRow[0] = ix >= threshold ? 240 : 10;
        }
    }
    return 1;
}

int imgGradientY(const Mat &sourceImage, Mat &destinationImage)
{
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

    for (int i = 0; i < rows - 1; i++)
    {

        uchar *pRow = grayImage.ptr<uchar>(i);
        uchar *destRow = destinationImage.ptr<uchar>(i);
        for (int j = 0; j < cols; j++, pRow += chanels, destRow += chanels)
        {

            uchar *pRowNext = grayImage.ptr<uchar>(i + 1);
            int iy = (pRowNext + j * chanels)[0] - pRow[0];
            destRow[0] = iy >= threshold ? 240 : 10;
            ;
        }
    }
    return 1;
}

int imgGradientXY(const Mat &sourceImage, Mat &destinationImage)
{

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

    for (int i = 0; i < rows; i++)
    {

        uchar *pRow = grayImage.ptr<uchar>(i);
        uchar *destRow = destinationImage.ptr<uchar>(i);
        for (int j = 0; j < cols - 1; j++, pRow += chanels, destRow += chanels)
        {
            int ix = (pRow + 1)[0] - pRow[0];

            uchar *pRowNext = grayImage.ptr<uchar>(i + 1);
            int iy = (pRowNext + j * chanels)[0] - pRow[0];

            int ixy = sqrt(ix * ix + iy * iy);

            destRow[0] = ixy >= threshold ? 240 : 10;
        }
    }
    return 1;
}

int sobel(const Mat &sourceImage, Mat &destinationImage)
{

    if (sourceImage.empty())
    {
        return -1;
    }

    Mat grayImage;
    RGB2GrayScale(sourceImage, grayImage);

    float **hx = new float *[3];
    hx[0] = new float[3];
    hx[0][0] = -1;
    hx[0][1] = 0;
    hx[0][2] = 1;

    hx[1] = new float[3];
    hx[1][0] = -2;
    hx[1][1] = 0;
    hx[1][2] = 2;

    hx[2] = new float[3];
    hx[2][0] = -1;
    hx[2][1] = 0;
    hx[2][2] = 1;

    float **hy = new float *[3];
    hy[0] = new float[3];
    hy[0][0] = -1;
    hy[0][1] = -2;
    hy[0][2] = -1;

    hy[1] = new float[3];
    hy[1][0] = 0;
    hy[1][1] = 0;
    hy[1][2] = 0;

    hy[2] = new float[3];
    hy[2][0] = 1;
    hy[2][1] = 2;
    hy[2][2] = 1;

    int _kernelWidth = 3;
    int _kernelHeight = 3;

    int rows = grayImage.rows;
    int cols = grayImage.cols;
    int chanels = grayImage.channels();
    int left = -_kernelWidth / 2;
    int right = -left;
    int up = -_kernelHeight / 2;
    int down = -up;

    destinationImage = Mat(rows, cols, CV_MAKETYPE(CV_8U, chanels));
    for (int i = 1; i < rows - 1; i++)
    {
        uchar *destRow = destinationImage.ptr<uchar>(i);
        for (int j = 1; j < cols - 1; j++, destRow += chanels)
        {
            
            double sumX = 0;
            double sumY = 0;
            for (int k = up; k <= down; k++)
            {
                for (int h = left; h <= right; h++)
                {
                    const float kValX = hx[k + down][h + right];
                    const float kValY = hy[k + down][h + right];
                    int iRow = i - k;
                    iRow = iRow > 0 ? iRow : 0;
                    iRow = iRow < rows ? iRow : rows - 1;

                    int iCol = j - h;
                    iCol = iCol > 0 ? iCol : 0;
                    iCol = iCol < cols ? iCol : cols - 1;
                    iCol = iCol * chanels;

                    const uchar *imgPixel = grayImage.ptr<uchar>(iRow) + iCol;
                    sumX += imgPixel[0] * kValX;
                    sumY += imgPixel[0] * kValY;
                }
            }
            int v = sqrt(sumX * sumX + sumY * sumY);
            destRow[0] = v > 150 ? 255 : 0;
        }
    }
    return 1;
}


int EdgeDetector::DetectEdge(const Mat &sourceImage, Mat &destinationImage, int kWidth, int kHeight, int method)
{

    if (method == 1)
    {
        return imgGradientX(sourceImage, destinationImage);
    }
    else if (method == 2)
    {
        return imgGradientY(sourceImage, destinationImage);
    }
    else if (method == 3)
    {
        return imgGradientXY(sourceImage, destinationImage);
    }
    else if (method == 4)
    {
        return sobel(sourceImage, destinationImage);
    }

    return 1;
}