/*
 * IODetector.cpp
 *
 *  Created on: 2015年12月3日
 *      Author: edison
 */
#include "IODetector.h"

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

