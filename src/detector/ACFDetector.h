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
#include "../Util/IOUtil.h"

typedef unsigned int uint32;

namespace acf{

struct ClassifierModel{
	float* thrs;
	float* hs;
	uint32* fids;
	uint32* child;
	uint32 treeDepth;
	uint32 nTreeNodes;
	uint32 nTrees;
};

typedef struct ClassifierModel Clf;

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
	private:
		std::string _name;
		std::string _gtDir;
		std::string _posImgDir;
		std::string _negImgDir = "";
		std::string _posWinDir = "";
		std::string _negWinDir = "";
		cv::Size _modelDs = cv::Size(100,41);
		cv::Size _modelDsPad = cv::Size(128,64);
		int _stride = 4;
		Clf* _clf;
	public:
		Builder(const std::string name,const std::string posDir,const std::string gtDir);
		~Builder();
		ACFDetector build();
		Builder* negImgDir(std::string negDir);
		Builder* posWinDir(std::string posWinDir);
		Builder* negWinDir(std::string negWinDir);
		Builder* modelDs(cv::Size size);
		Builder* modelDsPad(cv::Size size);
		Builder* stride(int s);
		Builder* Classifier(Clf* c);
		friend ACFDetector;
//		friend std::ostream& operator<<(std::ostream& os,const Builder& b);
	};

	friend std::ostream& operator<<(std::ostream&os ,const ACFDetector& d);
	void train();
	void test();

	void detectImg(std::vector<BoundingBox>& bbs,cv::Mat image);

private:
	std::string _name;
	std::string _gtDir;
	std::string _posImgDir;
	std::string _negImgDir;
	std::string _posWinDir;
	std::string _negWinDir;
	cv::Size _modelDs;
	cv::Size _modelDsPad;
	int _stride;
	double _cascThr;
	Clf* _clf;
	ACFDetector(Builder* builder);
	ACFDetector& operator=(const ACFDetector&);//prevent the compiler to generate copying assignment
};

//std::ostream& operator<<(std::ostream& os,const ACFDetector::Builder& b);
std::ostream& operator<<(std::ostream&os ,const ACFDetector& d);
}

#endif
