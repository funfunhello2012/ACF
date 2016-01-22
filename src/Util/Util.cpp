/*
 * Util.cpp
 *
 *  Created on: 2016年1月20日
 *      Author: edison
 */

#include "Util.h"

using namespace cv;

/**
 * convert the OpenCV mat to float pointer to matlab
 */
float * matconvert(Mat image)
{

	int k=0;
	int m=image.rows*image.cols*image.channels();
	uchar* A=(uchar*)malloc(m*sizeof(uchar));
	for(int i=0;i<image.rows;i++)
	{
		uchar *p=image.ptr<uchar>(i);
		for(int j=0;j<image.cols*image.channels();j++)
			A[k++]=(uchar)p[j];

	}
	float *A1 = (float*)malloc(m*sizeof(float));
	int idx = 0;

	//here OpenCV store data as BGR and matlab store as RGB
	for(int ch=image.channels()-1; ch>=0; ch--){
		for(int r=0;r<m;){
				A1[idx++]=(float)A[r+ch];
				r = r+3;
		}
	}
	return A1;
}

/**
 * convert the pointer to matlab data  OpenCV mat
 */
Mat convertmat(float *ima,Size sz,int nch)
{
	int m=sz.height*sz.width*nch;
	uchar *B=(uchar*)malloc(m*sizeof(uchar));
	int off =sz.height*sz.width;
	int idx = 0;
	switch(nch){
	case 1:
		for(int i=0;i<off;i++)
				B[idx++] = (uchar)(ima[i]+0.5);
		break;
	case 3:
		for(int i=0;i<off;i++){
				B[idx++]=(uchar)(ima[i+2*off]+0.5);
				B[idx++] = (uchar)(ima[i+off]+0.5);
				B[idx++] = (uchar)(ima[i]+0.5);
		}
		break;
	}

	return Mat(sz.height, sz.width, CV_8UC(nch),B);
}
