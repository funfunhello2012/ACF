/*
 * IOUtil.cpp
 *
 *  Created on: 2015年10月28日
 *      Author: edison
 *      read ,write and show  image like matlab format
 */


#include "IOUtil.h"
#include <highgui.h>

using cv::Mat;
using namespace acf;
using namespace std;

Mat imread(const char* filename)  throw(invalid_argument){
	Mat image;
	image = cv::imread(filename,CV_LOAD_IMAGE_COLOR);
	if(!image.data){
		throw invalid_argument(string(filename)+" can not  be open or read in!\t");
	}
	return image;
}

void imwrite(const string& filename,Mat image){
	cv::imwrite(filename,image);
}

void imshow(const Mat image,const string  windowName){
	cv::namedWindow(windowName,CV_WINDOW_AUTOSIZE);
	cv::imshow(windowName,image);
	cv::waitKey(0);
}

ACFDetector acf::loadDetectorFromMat(const string matPath){
	cout << "load detector from .mat " << matPath << endl;
	ACFDetector detector = ACFDetector::Builder("").build();
	return detector;
}

ACFDetector acf::loadDetectorFromJson(const string jsonPath){
	cout << "load detector from .json " << jsonPath << endl;
	ACFDetector detector = ACFDetector::Builder("").build();
	return detector;
}

void acf::writeDetectorToJson(const string filePath){
	cout << "write detector to " << filePath << endl;
}
