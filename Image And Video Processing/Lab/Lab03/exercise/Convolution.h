#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <math.h>
#include <list>
#include <algorithm>

using namespace cv;
using namespace std; 

class Convolution
{
	float** _kernel;// lưu giá trị của ma trận kernel dùng để tích chập
	int _kernelWidth;//chiều rộng kernel
	int _kernelHeight;//chiều dài kernel
public:
	//set kernel, chiều rộng, chiều dài kernel phải là số lẻ
	void SetKernel(float** kernel, int kWidth, int kHeight);
	void GenGaussKener(int kWidth, int kHeight, float sigma);

	/*
	Hàm tính convolution của 1 ảnh xám với kernel được xác định trước
	sourceImage: ảnh input
	destinationImage: ảnh output
	Hàm trả về
	0: nếu tính thành công
	1: nếu tính thất bại (không đọc được ảnh input,...)
	*/
	int DoConvolution(const Mat& sourceImage, Mat& destinationImage);	
	// Convolution();
	// ~Convolution();
};

