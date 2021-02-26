#include "Blur.h"
#include <vector>

int meanFilter(const Mat &sourceImage, Mat &destinationImage, int kWidth, int kHeight)
{
    if (sourceImage.empty())
    {
        return -1;
    }

    int rows = sourceImage.rows;
    int cols = sourceImage.cols;
    int chanels = sourceImage.channels();
    int left = -kWidth / 2;
    int right = -left;
    int up = -kHeight / 2;
    int down = -up;
    int ksize = kWidth * kHeight;

    destinationImage = Mat(rows, cols, CV_MAKETYPE(CV_8U, chanels));

    for (int i = 0; i < rows; i++)
    {
        uchar *destRow = destinationImage.ptr<uchar>(i);
        for (int j = 0; j < cols; j++, destRow += chanels)
        {
            for (int ch = 0; ch < chanels; ch++)
            {
                uchar *kernels = new uchar[kWidth * kHeight];
                int idx = 0;
                for (int k = up; k <= down; k++)
                {
                    for (int h = left; h <= right; h++)
                    {
                        int iRow = i + k;
                        iRow = iRow > 0 ? iRow : 0;

                        int iCol = j + h;
                        iCol = iCol > 0 ? iCol : 0;
                        iCol = iCol * chanels;

                        const uchar *imgPixel = sourceImage.ptr<uchar>(iRow) + iCol;
                        kernels[idx] = imgPixel[ch];
                        idx++;
                    }
                }
                destRow[ch] = kernels[ksize / 2];
            }
        }
    }
    return 1;
}

int avgFilter(const Mat &sourceImage, Mat &destinationImage, int kWidth, int kHeight)
{
    if (sourceImage.empty())
    {
        return -1;
    }

    int rows = sourceImage.rows;
    int cols = sourceImage.cols;
    int chanels = sourceImage.channels();
    int left = -kWidth / 2;
    int right = -left;
    int up = -kHeight / 2;
    int down = -up;
    uchar **kernel = new uchar *[kHeight];
    for (int i = 0; i < kHeight; i++)
    {
        kernel[i] = new uchar[kWidth];
        for (int j = 0; j < kWidth; j++)
        {
            kernel[i][j] = 1;
        }
    }
    int ksize = kWidth * kHeight;

    destinationImage = Mat(rows, cols, CV_MAKETYPE(CV_8U, chanels));

    for (int i = 0; i < rows; i++)
    {
        uchar *destRow = destinationImage.ptr<uchar>(i);
        for (int j = 0; j < cols; j++, destRow += chanels)
        {
            for (int ch = 0; ch < chanels; ch++)
            {
                int sum = 0;
                for (int k = up; k <= down; k++)
                {
                    for (int h = left; h <= right; h++)
                    {
                        const uchar kVal = kernel[k + down][h + right];
                        int iRow = i + k;
                        iRow = iRow > 0 ? iRow : 0;

                        int iCol = j + h;
                        iCol = iCol > 0 ? iCol : 0;
                        iCol = iCol * chanels;

                        const uchar *imgPixel = sourceImage.ptr<uchar>(iRow) + iCol;
                        sum += imgPixel[ch] * kVal;
                    }
                }
                destRow[ch] = sum / ksize;
            }
        }
    }
    return 1;
}

double gauss(int x, int y, double sigma)
{
    double p = 1.0 / (2 * M_PI * sigma * sigma);
    double k = (x * x + y * y) / (2 * sigma * sigma);
    double e = exp(-k);
    return p * e;
}

int gaussianFilter(const Mat &sourceImage, Mat &destinationImage, int kWidth, int kHeight)
{
    float sigma = 1.0;
    if (sourceImage.empty())
    {
        return -1;
    }

    int rows = sourceImage.rows;
    int cols = sourceImage.cols;
    int chanels = sourceImage.channels();
    int left = -kWidth / 2;
    int right = -left;
    int up = -kHeight / 2;
    int down = -up;
    double **kernel = new double *[kHeight];
    int ksize = kWidth * kHeight;
    for (int k = up; k <= down; k++)
    {
        kernel[k + down] = new double[kWidth];
        for (int h = left; h <= right; h++)
        {
            kernel[k + down][h + right] = gauss(k, h, sigma);
            // cout << kernel[k + down][h + right] << " ";
        }
        // cout << endl;
    }

    destinationImage = Mat(rows, cols, CV_MAKETYPE(CV_8U, chanels));

    for (int i = 0; i < rows; i++)
    {
        uchar *destRow = destinationImage.ptr<uchar>(i);
        for (int j = 0; j < cols; j++, destRow += chanels)
        {
            for (int ch = 0; ch < chanels; ch++)
            {
                double sum = 0;
                for (int k = up; k <= down; k++)
                {
                    for (int h = left; h <= right; h++)
                    {
                        const double kVal = kernel[k + down][h + right];
                        int iRow = i + k;
                        iRow = iRow > 0 ? iRow : 0;

                        int iCol = j + h;
                        iCol = iCol > 0 ? iCol : 0;
                        iCol = iCol * chanels;

                        const uchar *imgPixel = sourceImage.ptr<uchar>(iRow) + iCol;
                        sum += (int)imgPixel[ch] * kVal;
                    }
                }
                destRow[ch] = (int)sum;
            }
        }
    }
    return 1;
}

int Blur::BlurImage(const Mat &sourceImage, Mat &destinationImage, int kWidth, int kHeight, int method)
{
    if (method == 0)
    {
        return avgFilter(sourceImage, destinationImage, kWidth, kHeight);
    }
    else if (method == 1)
    {
        return meanFilter(sourceImage, destinationImage, kWidth, kHeight);
    } else if (method == 2) {
        return gaussianFilter(sourceImage, destinationImage, kWidth, kHeight);
    }
}