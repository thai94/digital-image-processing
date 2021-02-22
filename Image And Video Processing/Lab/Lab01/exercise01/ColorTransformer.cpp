#include "ColorTransformer.h"

int ColorTransformer::ChangeBrighness(const Mat &sourceImage, Mat &destinationImage, short b)
{
    if (sourceImage.empty())
    {
        return -1;
    }

    int rows = sourceImage.rows;
    int cols = sourceImage.cols;
    int chanels = sourceImage.channels();

    destinationImage = Mat(rows, cols, CV_MAKETYPE(CV_8U, chanels));

    for (int i = 0; i < rows; i++)
    {
        const uchar *pRow = sourceImage.ptr<uchar>(i);
        uchar *destRow = destinationImage.ptr<uchar>(i);
        for (int j = 0; j < cols; j++, pRow += chanels, destRow += chanels)
        {
            for (int k = 0; k < chanels; k++)
            {
                int brighterValue = pRow[k] + b;
                destRow[k] = brighterValue > 255 ? 255 : brighterValue;
            }
        }
    }

    return 1;
}

int ColorTransformer::ChangeContrast(const Mat &sourceImage, Mat &destinationImage, float c)
{
    if (sourceImage.empty())
    {
        return -1;
    }

    int rows = sourceImage.rows;
    int cols = sourceImage.cols;
    int chanels = sourceImage.channels();

    destinationImage = Mat(rows, cols, CV_MAKETYPE(CV_8U, chanels));
    float f = (259 * (c + 255)) / (float)(255 * (259 - c));

    for (int i = 0; i < rows; i++)
    {
        const uchar *pRow = sourceImage.ptr<uchar>(i);
        uchar *destRow = destinationImage.ptr<uchar>(i);
        for (int j = 0; j < cols; j++, pRow += chanels, destRow += chanels)
        {
            for (int k = 0; k < chanels; k++)
            {
                float v = f * (pRow[k] - 128) + 128;
                if (v < 0)
                {
                    v = 0;
                }
                if (v > 255)
                {
                    v = 255;
                }
                destRow[k] = v;
            }
        }
    }
    return 1;
}

int ColorTransformer::CalcHistogram(const Mat &sourceImage, Mat &histMatrix)
{
    if (sourceImage.empty())
    {
        return -1;
    }

    int rows = sourceImage.rows;
    int cols = sourceImage.cols;
    int chanels = sourceImage.channels();

    histMatrix = Mat(chanels, 256, CV_32F, Scalar(0, 0, 0));

    uint sum[chanels];
    for (int i = 0; i < chanels; i++)
    {
        sum[i] = 0;
    }
    for (int i = 0; i < rows; i++)
    {
        const uchar *pRow = sourceImage.ptr<uchar>(i);
        for (int j = 0; j < cols; j++, pRow += chanels)
        {
            for (int k = 0; k < chanels; k++)
            {
                float *histRow = histMatrix.ptr<float>(k);
                int color = pRow[k]; // chanel k
                histRow[color]++;
                sum[k]++;
            }
        }
    }

    for (int i = 0; i < chanels; i++)
    {
        float *histRow = histMatrix.ptr<float>(i);
        for (int j = 0; j < 256; j++)
        {
            histRow[j] = histRow[j] / sum[i];
        }
    }
    return 1;
}

int ColorTransformer::HistogramEqualization(const Mat &sourceImage, Mat &destinationImage)
{
    return -1;
}

int ColorTransformer::DrawHistogram(const Mat &histMatrix, Mat &histImage)
{
    int chanels = histMatrix.rows;
    int colorNum = histMatrix.cols;

    int width = 300;
    int height = 250 * chanels;
    int chartHeight = 200;
    int marginLeft = 10;

    histImage = Mat(height, width, CV_8UC3, Scalar(255, 255, 255));
    int bin = cvRound((double)width / colorNum);

    for(int k = 0; k < chanels; k++) {
        const float *pRow = histMatrix.ptr<float>(k);
        Scalar scalar;
        if(chanels == 3) {
            if(k == 0) {
                scalar = Scalar(255, 0, 0);
            } else if (k == 1) {
                scalar = Scalar(0, 128, 0);
            } else {
                scalar = Scalar(0, 0, 255);
            }
        } else {
            scalar = Scalar(128, 128, 128);
        }

        for (int i = 0; i < colorNum; i++)
        {
            line(histImage, Point(marginLeft + bin * (i), chartHeight * (k + 1)), Point(marginLeft + bin * (i), (k + 1) * chartHeight - cvRound(pRow[i] * 15000)), scalar, 2, 8, 0);
        }
    }
    return 1;
}

float ColorTransformer::CompareImage(const Mat &image1, Mat &image2)
{
    return -1;
}