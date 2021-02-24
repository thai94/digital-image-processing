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
            line(histImage, Point(marginLeft + bin * (i), chartHeight * (k + 1)), Point(marginLeft + bin * (i), (k + 1) * chartHeight - cvRound(pRow[i] * 5000)), scalar, 2, 8, 0);
        }
    }
    return 1;
}

float ColorTransformer::CompareImage(const Mat &image1, Mat &image2)
{
    Mat histMatrix1;
    Mat histMatrix2;

    this->CalcHistogram(image1, histMatrix1);
    this->CalcHistogram(image2, histMatrix2);

    int chanels = histMatrix1.rows;
    int colorNum = histMatrix2.cols;

    float sum = 0;
    for (int i = 0; i < chanels; i++) {
        float *pChanelImage1 = histMatrix1.ptr<float>(i);
        float *pChanelImage2 = histMatrix2.ptr<float>(i);

        for (int bin = 0; bin < colorNum; bin++) {
            sum += min(pChanelImage1[bin], pChanelImage2[bin]);
        }
    }

    return sum * 100 / (float)chanels;
}

int ColorTransformer::ReduceImageColor(const Mat& sourceImage, Mat& destinationImage, RgbColor *paletteColor, int nPalette) {
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
            uchar blue = pRow[0];
            uchar green = pRow[1];
            uchar red = pRow[2];

            RgbColor rgbColor = RgbColor();
            rgbColor.blue = blue;
            rgbColor.green = green;
            rgbColor.red = red;

            float min = 99999999.0;
            RgbColor nearestColor;
            for (int k = 0; k < nPalette; k++) {
                
                RgbColor color = paletteColor[k];
                float diffBlue = rgbColor.blue - color.blue;
                float diffGreen = rgbColor.green - color.green;
                float diffRed = rgbColor.red - color.red;
                float sum = diffBlue * diffBlue + diffGreen * diffGreen + diffRed * diffRed;
                float norm2 = sqrt(sum);
                if(norm2 < min) {
                    min = norm2;
                    nearestColor = color;
                }
            }

            destRow[0] = nearestColor.blue;
            destRow[1] = nearestColor.green;
            destRow[2] = nearestColor.red;
        }
    }

    return 1;
}