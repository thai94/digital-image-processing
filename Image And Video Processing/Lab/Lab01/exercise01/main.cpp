#include "Converter.h"
#include "ColorTransformer.h"

using namespace std;

void hsv2rbg(float h, float s, float v)
{
    s = s;
    v = v;
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

    cout << r << "-" << g << "-" << b << endl;
}

void rgb2hsv(float red, float green, float blue)
{

    float h = 0;
    float s = 0;
    float v = 0;

    red = red / 255;
    green = green / 255;
    blue = blue / 255;

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

    cout << h << "-" << s << "-" << v << endl;
}

int main(int, char **)
{

    Mat sourceImage = imread("./../test1.jpg");
    Mat sourceImage2 = imread("./../test6.jpg");
    
    Mat grayImage;
    // Mat rgbImage;
    // Mat hsvImage;

    Converter cv = Converter();
    cv.Convert(sourceImage, grayImage, 1);
    // imshow("Gray Image", grayImage);
    // cv.Convert(grayImage, rgbImage, 2);
    // cv.Convert(sourceImage, hsvImage, 3);
    // cv.Convert(hsvImage, rgbImage, 4);

    // imshow("Color Image", rgbImage);

    Mat brighterImage;
    Mat contrasterImage;
    Mat histMatrix;
    Mat histImage;
    Mat fourColorImage;

    ColorTransformer colorTransformer = ColorTransformer();
    // colorTransformer.ChangeBrighness(grayImage, brighterImage, 50);
    // colorTransformer.ChangeContrast(sourceImage, contrasterImage, 300);
    // imshow("Color Image", contrasterImage);
    // colorTransformer.CalcHistogram(sourceImage, histMatrix);
    // colorTransformer.DrawHistogram(histMatrix, histImage);
    // imshow("Hist Image", histImage);
    // cout << "Similar: " << colorTransformer.CompareImage(sourceImage, sourceImage2) << " %";

    RgbColor *paletteColor = new RgbColor[4];
    RgbColor color1 = RgbColor();
    color1.red = 255;
    color1.green = 0;
    color1.blue = 0;
    paletteColor[0] = color1;

    RgbColor color2 = RgbColor();
    color2.red = 255;
    color2.green = 255;
    color2.blue = 0;
    paletteColor[1] = color2;

    RgbColor color3 = RgbColor();
    color3.red = 0;
    color3.green = 255;
    color3.blue = 0;
    paletteColor[2] = color3;

    RgbColor color4 = RgbColor();
    color4.red = 255;
    color4.green = 0;
    color4.blue = 255;
    paletteColor[3] = color4;

    colorTransformer.ReduceImageColor(sourceImage, fourColorImage, paletteColor, 4);
    imshow("fourColorImage", fourColorImage);




    waitKey(0);
}