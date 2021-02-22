#include "Converter.h"

int Converter::RGB2GrayScale(const Mat &sourceImage, Mat &destinationImage)
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

int Converter::GrayScale2RGB(const Mat &sourceImage, Mat &destinationImage)
{

    if (sourceImage.empty())
    {
        return -1;
    }

    int rows = sourceImage.rows;
    int cols = sourceImage.cols;

    destinationImage = Mat(rows, cols, CV_8UC3);

    for (int i = 0; i < rows; i++)
    {

        const uchar *pRow = sourceImage.ptr<uchar>(i);
        uchar *destRow = destinationImage.ptr<uchar>(i);
        for (int j = 0; j < cols; j++, pRow += 1, destRow += 3)
        {

            uchar grayValue = pRow[0];

            destRow[0] = grayValue * 0.1;
            destRow[1] = grayValue * 0.9;
            destRow[2] = grayValue * 0.9;
        }
    }
    return 1;
}

int Converter::RGB2HSV(const Mat &sourceImage, Mat &destinationImage)
{

    if (sourceImage.empty())
    {
        return -1;
    }

    int rows = sourceImage.rows;
    int cols = sourceImage.cols;
    int chanels = 3;

    destinationImage = Mat(rows, cols, CV_8UC3);

    for (int i = 0; i < rows; i++)
    {

        const uchar *pRow = sourceImage.ptr<uchar>(i);
        uchar *destRow = destinationImage.ptr<uchar>(i);
        for (int j = 0; j < cols; j++, pRow += chanels, destRow += chanels)
        {
            float blue = pRow[0] / 255.0;
            float green = pRow[1] / 255.0;
            float red = pRow[2] / 255.0;

            float h = 0;
            float s = 0;
            float v = 0;

            float cMax = max(blue, max(green, red));
            float cMin = min(blue, min(green, red));

            v = cMax;
            if (cMax != 0)
            {
                s = (cMax - cMin) / cMax;
            }

            if (cMax == red)
            {
                h = 60 * (green - blue) / s;
            }
            else if (cMax == green)
            {
                h = 60 * (blue - red) / s;
                h += 120;
            }
            else
            {
                h = 60 * (red - green) / s;
                h += 240;
            }

            if (h < 0)
            {
                h += 360;
            }

            destRow[0] = h;
            destRow[1] = s * 100;
            destRow[2] = v * 100;
        }
    }

    return 1;
}

int Converter::HSV2RGB(const Mat &sourceImage, Mat &destinationImage)
{
    if (sourceImage.empty())
    {
        return -1;
    }

    int rows = sourceImage.rows;
    int cols = sourceImage.cols;
    int chanels = 3;

    destinationImage = Mat(rows, cols, CV_8UC3);

    for (int i = 0; i < rows; i++)
    {

        const uchar *pRow = sourceImage.ptr<uchar>(i);
        uchar *destRow = destinationImage.ptr<uchar>(i);
        for (int j = 0; j < cols; j++, pRow += chanels, destRow += chanels)
        {
            float h = pRow[0];
            float s = pRow[1] / 100.0;
            float v = pRow[2] / 100.0;

            float C = v * s;
            float hh = h / 60;
            float X = C * (1 - abs(fmod(hh, 2) - 1));

            float r = 0;
            float g = 0;
            float b = 0;

            if (hh >= 0 && hh < 1)
            {
                r = C;
                g = X;
            }
            else if (hh >= 1 && hh < 2)
            {
                r = X;
                g = C;
            }
            else if (hh >= 2 && hh < 3)
            {
                g = C;
                b = X;
            }
            else if (hh >= 3 && hh < 4)
            {
                g = X;
                b = C;
            }
            else if (hh >= 4 && hh < 5)
            {
                r = X;
                b = C;
            }
            else
            {
                r = C;
                b = X;
            }

            float m = v - C;
            r += m;
            g += m;
            b += m;
            r *= 255.0;
            g *= 255.0;
            b *= 255.0;

            r = round(r);
            g = round(g);
            b = round(b);

            destRow[0] = b;
            destRow[1] = g;
            destRow[2] = r;
        }
    }

    return 1;
}

int Converter::Convert(Mat &sourceImage, Mat &destinationImage, int type)
{
    if (type == 1)
    {
        return this->RGB2GrayScale(sourceImage, destinationImage);
    }
    else if (type == 2)
    {
        return this->GrayScale2RGB(sourceImage, destinationImage);
    }
    else if (type == 3)
    {
        return this->RGB2HSV(sourceImage, destinationImage);
    }
    else if (type == 4)
    {
        return this->HSV2RGB(sourceImage, destinationImage);
    }
    return -1;
}