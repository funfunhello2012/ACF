/*
 * IODetector.cpp
 *
 *  Created on: 2015年12月3日
 *      Author: edison
 */
#include "IODetector.h"
using namespace acf;
using cv::Size;

ACFDetector acf::loadDetectorFromMat(const string matPath){
	OUT("load detector from .mat "+matPath);
	ACFDetector::Builder* builder = new ACFDetector::Builder("testDe","/posDir","/gtDir");
	Size s(100,41);
	Size padS(128,64);
	string negImgDir = "";
	string posWinDir="";
	string negWinDir="";
	int stride = 4;

	builder->modelDs(s);
	builder->modelDsPad(padS);
	builder->negImgDir(negImgDir);
	builder->posWinDir(posWinDir);
	builder->negWinDir(negWinDir);
	builder->stride(stride);

	ACFDetector detector = builder->build();
	OUT(detector);
	return detector;
}

ACFDetector acf::loadDetectorFromJson(const string jsonPath){
	OUT("load detector from .json " + jsonPath);
	ACFDetector::Builder* builder = new ACFDetector::Builder("testDe","/posDir","/gtDir");
	ACFDetector detector = builder->build();
	return detector;
}

void acf::writeDetectorToJson(const string filePath){
	 OUT("write detector to " +filePath);
}
