#include "Converter.h"
using namespace std;

int Converter::Convert(Mat& sourceImage, Mat& destinationImage, int type) {
    if(type == 1) {
        return RGB2GrayScale(sourceImage, destinationImage);
    } 

    if(type == 2) {
        return GrayScale2RGB(sourceImage, destinationImage);
    }

    if(type == 3) {
        return RGB2HSV(sourceImage, destinationImage);
    }

    if(type == 4) {
        return HSV2RGB(sourceImage, destinationImage);
    }
    return -1;
}

int Converter::RGB2GrayScale(const Mat& sourceImage, Mat& destinationImage) {
    if (sourceImage.empty()) {
        cout << "Not a valid image file" << endl;
        return -1;
    }

    int rows = sourceImage.rows;
    int col = sourceImage.cols;
    int chanels = sourceImage.channels();

    destinationImage = Mat(rows, col, CV_8UC1);

    for (int i = 0; i < rows; i++) {
        const uchar *pRow = sourceImage.ptr<uchar>(i);
        uchar *destRow = destinationImage.ptr<uchar>(i);
        for (int j = 0; j < col; j++, pRow += chanels, destRow += 1) {
            uchar blue = pRow[0];
            uchar green = pRow[1];
            uchar red = pRow[2];
            uchar gray = floor(0.11 * blue + 0.59 * green + 0.30 * red);
            destRow[0] = gray;
        }
    }

    return 1;
}

int Converter::RGB2HSV(const Mat& sourceImage, Mat& destinationImage) {
    if (sourceImage.empty()) {
        cout << "Not a valid image file" << endl;
        return -1;
    }

    int rows = sourceImage.rows;
    int col = sourceImage.cols;
    int chanels = sourceImage.channels();

    destinationImage = Mat(rows, col, CV_8UC3);

    for (int i = 0; i < rows; i++) {
        const uchar *pRow = sourceImage.ptr<uchar>(i);
        uchar *destRow = destinationImage.ptr<uchar>(i);
        for (int j = 0; j < col; j++, pRow += chanels, destRow += 3) {
            float blue = pRow[0];
            float green = pRow[1];
            float red = pRow[2];

            float h = 0;
            float s = 0;
            float v = 0;

            float redNew = red/255;
            float greenNew = green/255;
            float blueNew = blue/255;

            float cMax = max(max(redNew, greenNew), blueNew);
            float cMin = min(min(redNew, greenNew), blueNew);

            float denta = cMax - cMin;

            if (denta != 0) {
                if(cMax == redNew) {
                    h = (greenNew - blueNew)/denta;
                    // h = int(h) % 6;
                    h = 60 * h;
                } else if (cMax == greenNew) {
                    h = (blueNew - redNew)/denta;
                    h = h + 120;
                    h = h * 60;
                } else {
                    h = (redNew - greenNew)/denta;
                    h = h + 240;
                    h = h * 60;
                }

                if(h < 0) {
                    h += 360;
                }


                s = denta / cMax;
            }

            v = cMax;

            s*=100;
		 	v*=100;

            destRow[0] = floor(h);
            destRow[1] = floor(s);
            destRow[2] = floor(v);
        }
    }

    return 1;
}

int Converter::HSV2RGB(const Mat& sourceImage, Mat& destinationImage) {
    if (sourceImage.empty()) {
        cout << "Not a valid image file" << endl;
        return -1;
    }

    int rows = sourceImage.rows;
    int col = sourceImage.cols;
    int chanels = sourceImage.channels();

    destinationImage = Mat(rows, col, CV_8UC3);

    for (int i = 0; i < rows; i++) {
        const uchar *pRow = sourceImage.ptr<uchar>(i);
        uchar *destRow = destinationImage.ptr<uchar>(i);
        for (int j = 0; j < col; j++, pRow += chanels, destRow += 3) {
            float h = pRow[0];
            float s = pRow[1];
            float v = pRow[2];

            s = s / 100;
            v = v /100;
            float C = v * s;
            float hh = h/60;
            float X = C * (1 - abs(fmod(hh, 2) - 1));

            float r = 0;
            float g = 0;
            float b = 0;

            if( hh>= 0 && hh<1 )
			{
				r = C;
				g = X;
			}
            else if( hh>=1 && hh<2 )
			{
				r = X;
				g = C;
			}
			else if( hh>=2 && hh<3 )
			{
				g = C;
				b = X;
			}
			else if( hh>=3 && hh<4 )
			{
				g = X;
				b = C;
			}
			else if( hh>=4 && hh<5 )
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

int Converter::GrayScale2RGB(const Mat& sourceImage, Mat& destinationImage) {
    if (sourceImage.empty()) {
        cout << "Not a valid image file" << endl;
        return -1;
    }

    int rows = sourceImage.rows;
    int col = sourceImage.cols;
    int chanels = sourceImage.channels();

    destinationImage = Mat(rows, col, CV_8UC3);

    for (int i = 0; i < rows; i++) {
        const uchar *pRow = sourceImage.ptr<uchar>(i);
        uchar *destRow = destinationImage.ptr<uchar>(i);
        for (int j = 0; j < col; j++, pRow += chanels, destRow += 3) {
            
            int gray = pRow[0];

            destRow[0] = gray * 1.5;
            destRow[1] = gray + 0.5;
            destRow[2] = gray * 3;
        }
    }

    return 0;
}