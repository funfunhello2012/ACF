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

/**
 * This Classifier Model hold the data for the classifier
 */
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

/**************************************************
 * ACFDetector is the detector object to used
 * we can use it in two case:
 * 1.load an detector from a file then detect a image
 * 	ACFDetector detector  =  loadDetectorFromMat("/home/edison/workspace/acfImplement/ACF/data/AcfInriaDetector.mat");
 * 	vector<BoundingBox> bbs;
 * 	Mat image = imread("./data/I00000.png");
 * 	detector.detectImg(bbs,image);
 * 2.train a detector and test it on a dataset
 */
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
		Builder* modelDs(cv::Size size);
		Builder* modelDsPad(cv::Size size);
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
	/*********************************************************
	 * detect image and get the BoundBox in this image
	 * @param bbs : it is a set of bounding box that hold the (x,y,width,height,score) values
	 * @param image : a cv::Mat image data
	 */
	void detectImg(std::vector<BoundingBox>& bbs,cv::Mat image);
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
	cv::Size _modelDs;
	cv::Size _modelDsPad;
	int _stride;
	int _shrink;
	double _cascThr;
	Clf* _clf;
	Pyramid* _pyramid;
	ChnsManager* _chnsManager;
	Builder* _builder;
	ACFDetector(Builder* builder);
	ACFDetector& operator=(const ACFDetector&);//prevent the compiler to generate copying assignment
	/**
	 * detect one scale image
	 */
	void detectOneScale(std::vector<BoundingBox>& bbs,float* chns,int rows,int cols,int nC);
};

//std::ostream& operator<<(std::ostream& os,const ACFDetector::Builder& b);
std::ostream& operator<<(std::ostream&os ,const ACFDetector& d);
}

#endif
