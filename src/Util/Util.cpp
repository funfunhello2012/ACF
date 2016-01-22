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
	int m=image.rows*image.cols*image.channels();
	float* result = new float[m];
	int idx=0;
	for(int c = image.channels()-1;c>=0;c--){
		for(int i=0;i<image.cols;i++){
			for(int j=0;j<image.rows;j++){
				result[idx++] = (float)image.at<Vec3b>(j,i)[c];
			}
		}
	}
	return result;
}


Mat convertmat(float *image,Size sz,int nch)
{
	int m=sz.height*sz.width*nch;
	uchar* matData = new uchar[m];
	int off = sz.height*sz.width;
	int idx = 0;
	switch(nch){
	case 1:
		for(int h=0;h<sz.height;h++){
			for(int w=0;w<sz.width;w++){
				int hoff = w*sz.height+h;
				matData[idx++] = (uchar)image[hoff];
			}
		}
		break;
	case 3:
		for(int h=0;h<sz.height;h++){
			for(int w=0;w<sz.width;w++){
				int hoff = w*sz.height+h;
				matData[idx++] = (uchar)image[hoff+2*off];
				matData[idx++] = (uchar)image[hoff+off];
				matData[idx++] = (uchar)image[hoff];
			}
		}
		break;
	}
	return Mat(sz.height, sz.width, CV_8UC(nch),matData);
}

std::ostream& operator<<(std::ostream&os ,const BoundingBox& d){
	os << "[x,y,w,h:score]" << d.box << ":" << d.score;
}

