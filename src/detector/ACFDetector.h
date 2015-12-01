/*
 * ACFDetector.cpp
 *
 *  Created on: 2015年11月9日
 *      Author: edison
 */

#ifndef SRC_DETECTOR_ACFDETECTOR_H_
#define SRC_DETECTOR_ACFDETECTOR_H_

#include "../Util/Builder.h"
#include "../Util/Util.h"
#include "../Util/common.h"
#include <vector>


using cv::Size;
using cv::Mat;
using std::string;
namespace acf{

class ACFDetector {
public:
	~ACFDetector();
	ACFDetector(const ACFDetector& origin);
	/****************************************
	 *  There are two way to get detector,
	 *  first one is this,  initialize ACFDetector from builder
	 *  second one is   load detector from .mat or .xml file using "Util/IOUtil"
	 */
	class Builder : public IBuilder<ACFDetector>{
	public:
		Builder(const string configFile);
		~Builder();
		ACFDetector build();
	};

	void train();
	void test();

	void detectImg(std::vector<BoundingBox>& bbs,Mat image);

private:
	Size modelDs;
	Size modelDsPad;
	int stride;
	double cascThr;

	ACFDetector(Builder* builder);
	ACFDetector& operator=(const ACFDetector&);//prevent the compiler to generate copying assignment
};

}

#endif
