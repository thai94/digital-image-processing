#include "ColorTransformer.h"
using namespace std;

int ColorTransformer::ChangeBrighness(const Mat& sourceImage, Mat& destinationImage, short b) {
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
            uchar blue = pRow[0];
            uchar green = pRow[1];
            uchar red = pRow[2];

            destRow[0] = max(0, min(255, blue + b));
            destRow[1] = max(0, min(255, green + b));
            destRow[2] = max(0, min(255, red + b));
        }
    }

    return 1;
}

int ColorTransformer::ChangeContrast(const Mat& sourceImage, Mat& destinationImage, float c) {
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

            float factor = (259 * (c + 255)) / (255 * (259 - c));
            float newBlue = factor*(blue - 128) + 128;
            float newGreen = factor*(green - 128) + 128;
            float newRed = factor*(red - 128) + 128;

            destRow[0] = round(newBlue);
            destRow[1] = round(newGreen);
            destRow[2] = round(newRed);
        }
    }

    return 1;
}

int ColorTransformer::CalcHistogram(const Mat& sourceImage, Mat& histMatrix) {
    if (sourceImage.empty()) {
        cout << "Not a valid image file" << endl;
        return -1;
    }

    int rows = sourceImage.rows;
    int col = sourceImage.cols;
    int chanels = sourceImage.channels();

    histMatrix = Mat(chanels, 256, CV_32F, Scalar(0, 0, 0));

    float sumChanel1 = 0;
    float sumChanel2 = 0;
    float sumChanel3 = 0;
    for (int i = 0; i < rows; i++) {
        const uchar *pRow = sourceImage.ptr<uchar>(i);
        for (int j = 0; j < col; j++, pRow += chanels) {
            for (int k = 0; k < chanels; k++) {
                float *histRow = histMatrix.ptr<float>(k);
                int color = pRow[k]; // chanel k
                histRow[color]++;

                if(k == 0) {
                    sumChanel1++;
                } else if(k == 1) {
                    sumChanel2++;
                } else {
                    sumChanel3++;
                }
            }
        }
    }

    for (int i = 0; i < chanels ; i++) {
        float *histRow = histMatrix.ptr<float>(i);
        float sum = 0;
        if(i == 0) {
            sum = sumChanel1;
        } else if (i == 1) {
            sum = sumChanel2;
        } else {
            sum = sumChanel3;
        }
        for (int j = 0; j < 256; j++) {
            histRow[j] = histRow[j] / sum;
        }
    }
    cout << "Finsh";
    return 1;
}

int ColorTransformer::DrawHistogram(const Mat& histMatrix, Mat& histImage) {
    int chanels = histMatrix.rows;
    int colorNum = histMatrix.cols;

    int width = 250;
    int height = 250;
    histImage = Mat(height, width, CV_8UC3, Scalar(255, 255, 255));
    int bin = cvRound((double)width / height);

    // for (int i = 0; i < 1; i++) {
    //     const int *pRow = histMatrix.ptr<int>(i);
    //     for (int j = 0; j < colorNum; j++) {
    //         line(histImage, Point(bin*(j), height), Point(bin*(i), height - cvRound(pRow[j])), Scalar(0), 2, 8, 0);
    //     }
    // }

    // normalize(histMatrix, histMatrix, 0, height, NORM_MINMAX, -1, Mat());

    const float *pRow = histMatrix.ptr<float>(0);
    for (int i = 0; i < colorNum; i++) {
        line(histImage, Point(bin*(i), height), Point(bin*(i), height - cvRound(pRow[i]*8000)), Scalar(0, 0, 255), 2, 8, 0);
    }

    return 1;
}

int ColorTransformer::HistogramEqualization(const Mat& sourceImage, Mat& destinationImage) {
    equalizeHist(sourceImage, destinationImage);
    return 1;
}

float ColorTransformer::CompareImage(const Mat& image1, Mat& image2) {
    Mat histImage1;
    Mat histImage2;

    this->CalcHistogram(image1, histImage1);
    this->CalcHistogram(image2, histImage2);


    int chanels = histImage1.rows;
    int colorNum = histImage1.cols;

    float sum = 0;
    for (int i = 0; i < chanels; i++) {
        float *pChanelImage1 = histImage1.ptr<float>(i);
        float *pChanelImage2 = histImage2.ptr<float>(i);

        for (int bin = 0; bin < colorNum; bin++) {
            sum += min(pChanelImage1[bin], pChanelImage2[bin]);
        }
    }

    return sum;
}