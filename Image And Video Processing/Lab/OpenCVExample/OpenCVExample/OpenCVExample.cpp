// OpenCVExample.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int RGB2Gray_1(const cv::Mat &srcImg, cv::Mat &dstImg)
{
	if (srcImg.data == NULL || srcImg.rows <= 0 || srcImg.cols <= 0)
		return 0;

	int width = srcImg.cols, height = srcImg.rows;

	dstImg = cv::Mat(height, width, CV_8UC1, Scalar(0));

	int srcnChannels = srcImg.channels();
	int dstnChannels = dstImg.channels();

	for (int y = 0; y < height; y++)
	{
		const uchar* pSrcRow = srcImg.ptr<uchar>(y);
		uchar* pDstRow = dstImg.ptr<uchar>(y);

		for (int x = 0; x < width; x++, pSrcRow += srcnChannels, pDstRow += dstnChannels)
		{
			uchar B = pSrcRow[0];
			uchar G = pSrcRow[1];
			uchar R = pSrcRow[2];
			float gray = (float)(R + G + B) / 3;
			pDstRow[0] = (uchar)gray;
		}
	}

	return 1;
}

int RGB2Gray_2(const cv::Mat &srcImg, cv::Mat &dstImg)
{
	if (srcImg.data == NULL || srcImg.rows <= 0 || srcImg.cols <= 0)
		return 0;

	int width = srcImg.cols, height = srcImg.rows;

	dstImg = cv::Mat(height, width, CV_8UC1, Scalar(0));

	int srcWidthStep = srcImg.step[0];
	int dstWidthStep = dstImg.step[0];

	int srcnChannels = srcImg.step[1];
	int dstnChannels = dstImg.step[1];

	const uchar* pSrcData = (uchar*)srcImg.data;
	uchar* pDstData = (uchar*)dstImg.data;

	for (int y = 0; y < height; y++, pSrcData += srcWidthStep, pDstData += dstWidthStep)
	{
		const uchar* pSrcRow = pSrcData;
		uchar* pDstRow = pDstData;

		for (int x = 0; x < width; x++, pSrcRow += srcnChannels, pDstRow += dstnChannels)
		{
			uchar B = pSrcRow[0];
			uchar G = pSrcRow[1];
			uchar R = pSrcRow[2];
			float gray = (float)(R + G + B) / 3;
			pDstRow[0] = (uchar)gray;
		}
	}

	return 1;
}


int do_average_filter(const cv::Mat &srcImg, cv::Mat &dstImg, int kernelWidth, int kernelHeight)
{
	if (srcImg.data == NULL || srcImg.rows <= 0 || srcImg.cols <= 0)
		return 0;

	int width = srcImg.cols, height = srcImg.rows;

	dstImg = cv::Mat(height, width, srcImg.type(), Scalar(0));

	int widthStep = srcImg.step[0];
	int nChannels = srcImg.step[1];
	

	int kHalfWidth = kernelWidth >> 1;
	int kHalfHeight = kernelHeight >> 1;
	
	vector<int> offsets;
	for (int y = -kHalfHeight; y <= kHalfHeight; y++)
		for (int x = -kHalfWidth; x <= kHalfWidth; x++)
			offsets.push_back(y*widthStep + x*nChannels);

	int xStart = kHalfHeight, yStart = kHalfHeight;
	int xEnd = width - kHalfWidth - 1, yEnd = height - kHalfHeight - 1;

	const uchar* pSrcData = (uchar*)srcImg.data + yStart*widthStep + xStart*nChannels;
	uchar* pDstData = (uchar*)dstImg.data + yStart*widthStep + xStart*nChannels;
	
	int n = offsets.size();

	for (int y = yStart; y <= yEnd; y++, pSrcData += widthStep, pDstData += widthStep)
	{
		const uchar* pSrcRow = pSrcData;
		uchar* pDstRow = pDstData;

		for (int x = xStart; x <= xEnd; x++, pSrcRow += nChannels, pDstRow += nChannels)
		{						
			for (int i = 0; i < nChannels; i++)			
			{				
				int avg = 0;
				for (int k = 0; k < n; k++)
					avg += pSrcRow[i + offsets[k]];
				pDstRow[i] = (uchar)(avg / n);
			}			
		}
	}

	return 1;
}


int main()
{	
	Mat srcImg = imread("D:\\ltt.jpg", CV_LOAD_IMAGE_COLOR);

	Mat grayImg;
	RGB2Gray_2(srcImg, grayImg);

	Mat avgImg;
	do_average_filter(srcImg, avgImg, 7, 7);

	cv::imshow("Src Image", srcImg);	
	cv::imshow("Gray Image", grayImg);
	cv::imshow("Avg Image", avgImg);
	waitKey(0);
	
}




