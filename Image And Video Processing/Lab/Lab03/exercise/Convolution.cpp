#include "Convolution.h"

void Convolution::SetKernel(float** kernel, int kWidth, int kHeight) {
    this->_kernelHeight = kHeight;
    this->_kernelWidth = kWidth;
    this->_kernel = kernel;
}

double gauss1(int x, int y, double sigma)
{
    double p = 1.0 / (2 * M_PI * sigma * sigma);
    double k = (x * x + y * y) / (2 * sigma * sigma);
    double e = exp(-k);
    return p * e;
}

void Convolution::GenGaussKener(int kWidth, int kHeight, float sigma) {

    int left = -kWidth / 2;
    int right = -left;
    int up = -kHeight / 2;
    int down = -up;
    float **kernel = new float *[kHeight];
    for (int k = up; k <= down; k++)
    {
        kernel[k + down] = new float[kWidth];
        for (int h = left; h <= right; h++)
        {
            kernel[k + down][h + right] = gauss1(k, h, sigma);
        }
    }

    this->_kernel = kernel;
    this->_kernelHeight = kHeight;
    this->_kernelWidth = kWidth;
}

int Convolution::DoConvolution(const Mat& sourceImage, Mat& destinationImage) {
    if (sourceImage.empty())
    {
        return -1;
    }

    int rows = sourceImage.rows;
    int cols = sourceImage.cols;
    int chanels = sourceImage.channels();
    int left = -this->_kernelWidth / 2;
    int right = -left;
    int up = -this->_kernelHeight / 2;
    int down = -up;

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
                        const float kVal = this->_kernel[k + down][h + right];
                        int iRow = i - k;
                        iRow = iRow > 0 ? iRow : 0;
                        iRow = iRow < rows ? iRow : rows - 1;

                        int iCol = j - h;
                        iCol = iCol > 0 ? iCol : 0;
                        iCol = iCol < cols ? iCol : cols - 1;
                        iCol = iCol * chanels;

                        const uchar *imgPixel = sourceImage.ptr<uchar>(iRow) + iCol;
                        sum += imgPixel[ch] * kVal;
                    }
                }
                destRow[ch] = sum;
            }
        }
    }
    return 1;
}