/*
 * IOUtil.cpp
 *
 *  Created on: 2015年10月28日
 *      Author: edison
 *      read ,write and show  image like matlab format
 */


#include "IOUtil.h"
#include "common.h"

using namespace acf;


Mat acf::imread(const char* filename)  throw(invalid_argument){
	Mat image;
	image = cv::imread(filename,CV_LOAD_IMAGE_COLOR);
	if(!image.data){
		throw invalid_argument(string(filename)+" can not  be open or read in!\t");
	}
	return image;
}

void acf::imwrite(const string& filename,Mat image){
	cv::imwrite(filename,image);
}

void acf::imshow(const Mat image,const string  windowName){
	cv::namedWindow(windowName,CV_WINDOW_AUTOSIZE);
	cv::imshow(windowName,image);
	cv::waitKey(0);
}

ACFDetector acf::loadDetectorFromMat(const string matPath){
	OUT("load detector from .mat "+matPath);
	ACFDetector detector = ACFDetector::Builder("").build();
	return detector;
}

ACFDetector acf::loadDetectorFromJson(const string jsonPath){
	OUT("load detector from .json " + jsonPath);
	ACFDetector detector = ACFDetector::Builder("").build();
	return detector;
}

void acf::writeDetectorToJson(const string filePath){
	 OUT("write detector to " +filePath);
}
