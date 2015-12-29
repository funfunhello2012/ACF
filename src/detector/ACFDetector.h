/*
 * ACFDetector.cpp
 *
 *  Created on: 2015年11月9日
 *      Author: edison
 */

#ifndef SRC_DETECTOR_ACFDETECTOR_H_
#define SRC_DETECTOR_ACFDETECTOR_H_

#include <cmath>
#include "../Util/Builder.h"
#include "../Util/Util.h"
#include "../Util/common.h"
#include "../Util/IOUtil.h"
#include "../features/pyramid.h"

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
		Size _modelDs = Size(100,41);
		Size _modelDsPad = Size(128,64);
		int _stride = 4;
		int _shrink =  4;
		double _cascThr = -1;
		Clf* _clf = NULL;
		Pyramid* _pyramid = NULL;
		ChnsManager* _chnsManager = NULL;
	public:
		Builder(const std::string name,const std::string posDir,const std::string gtDir);
		~Builder();
		ACFDetector build();
		Builder* negImgDir(std::string negDir);
		Builder* posWinDir(std::string posWinDir);
		Builder* negWinDir(std::string negWinDir);
		Builder* modelDs(Size size);
		Builder* modelDsPad(Size size);
		Builder* stride(int s);
		Builder* shrink(int s);
		Builder* cascThr(double t);
		Builder* classifier(Clf* c);
		Pyramid* getPyramid();
		ChnsManager* getChnsManager();
		friend ACFDetector;
//		friend std::ostream& operator<<(std::ostream& os,const Builder& b);
	};

	friend std::ostream& operator<<(std::ostream&os ,const ACFDetector& d);
	void train();
	void test();
	void detectImg(std::vector<BoundingBox>& bbs,MatrixD& image);
	Pyramid* getPyramid(){
		return this->_pyramid;
	}

	ChnsManager* getChnsManager(){
		return this->_chnsManager;
	}

private:
	std::string _name;
	std::string _gtDir;
	std::string _posImgDir;
	std::string _negImgDir;
	std::string _posWinDir;
	std::string _negWinDir;
	Size _modelDs;
	Size _modelDsPad;
	int _stride;
	int _shrink;
	double _cascThr;
	Clf* _clf;
	Pyramid* _pyramid;
	ChnsManager* _chnsManager;
	Builder* _builder;
	ACFDetector(Builder* builder);
	ACFDetector& operator=(const ACFDetector&);//prevent the compiler to generate copying assignment
	void detectOneScale(std::vector<BoundingBox>& bbs,float* chns,int rows,int cols,int nC);
};

//std::ostream& operator<<(std::ostream& os,const ACFDetector::Builder& b);
std::ostream& operator<<(std::ostream&os ,const ACFDetector& d);
}

#endif
