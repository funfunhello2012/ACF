/*
 * ACFDetector.cpp
 *
 *  Created on: 2015年11月9日
 *      Author: edison
 */

#include "../Util/Builder.h"
#include "../Util/Util.h"
#include <vector>
#include <opencv2/opencv.hpp>

using cv::Size;
namespace acf{

class ACFDetector {
private:
	class Opts{
		const Size modelDimension;
		const Size modelDimensionPad;
		int stride;
		int cascThr;
		int cascCal;
		const float seed;
		const string name;
		const string posImgDir;
		const string negImgDir;
		const int nPos;
		const int nNeg;
		const int nPerNeg;
		const int nAccNeg;
	};

	ACFDetector();
	ACFDetector& operator=(const ACFDetector&);//prevent the compiler to generate copying assignment

public:
	~ACFDetector();
	ACFDetector(const ACFDetector& origin);
	/****************************************
	 *  There are two way to get detector,first one is this
	 *  initialize ACFDetector from builder
	 *  second one is load detector from .mat or .xml file using "Util/IOUtil"
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


};

}




