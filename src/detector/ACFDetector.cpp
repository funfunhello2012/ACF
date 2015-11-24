/*
 * ACFDetector.cpp
 *
 *  Created on: 2015年11月9日
 *      Author: edison
 */


#include "../Util/IOUtil.h"
#include "ACFDetector.h"

using namespace std;
using namespace acf;
ACFDetector::ACFDetector() {
	cout << "ACFDetector()" << endl;
}

ACFDetector::	~ACFDetector(){
	cout << "~ACFDetector()" << endl;
}

ACFDetector::Builder::Builder(){ cout << "Builder()" << endl;}
ACFDetector::Builder::~Builder(){cout << "~Builder() " << endl;}

/**
 * Builder constructor to get a object
 */
ACFDetector ACFDetector:: Builder::build(){
	cout << "Build ACF Detector From Builder" << endl;
	return ACFDetector();
}





