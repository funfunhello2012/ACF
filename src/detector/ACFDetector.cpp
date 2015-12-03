/*
 * ACFDetector.cpp
 *
 *  Created on: 2015年11月9日
 *      Author: edison
 */


#include "ACFDetector.h"


using namespace acf;
ACFDetector::ACFDetector(ACFDetector::Builder* builder) {
	cout << "ACFDetector(Builder*)" << endl;
}

ACFDetector::	~ACFDetector(){
	cout << "~ACFDetector()" << endl;
}

ACFDetector::Builder::Builder(const string configFile){ cout << "Builder(config) from " << configFile << endl;}
ACFDetector::Builder::~Builder(){cout << "~Builder() " << endl;}

/**
 * Builder constructor to get a object
 */
ACFDetector ACFDetector:: Builder::build(){
	cout << "Build ACF Detector From Builder" << endl;
	return ACFDetector(this);
}

void ACFDetector::detectImg(std::vector<BoundingBox>& bbs,Mat image){
	cout << "detect image" << endl;
}

void ACFDetector::train(){
	cout << "train a detector here " << endl;
}

void ACFDetector::test(){
	cout << "test module here" << endl;
}





