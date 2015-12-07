/*
 * ACFDetector.cpp
 *
 *  Created on: 2015年11月9日
 *      Author: edison
 */


#include "ACFDetector.h"


using namespace acf;
using namespace std;
using cv::Size;
using cv::Mat;



ACFDetector::ACFDetector(ACFDetector::Builder* builder) {
	OUT("ACFDetector(Builder*)");
	this->_cascThr = -1;
	this->_gtDir = builder->_gtDir;
	this->_modelDs = builder->_modelDs;
	this->_modelDsPad = builder->_modelDsPad;
	this->_name = builder->_name;
	this->_negImgDir = builder->_negImgDir;
	this->_negWinDir = builder->_negWinDir;
	this->_posImgDir = builder->_posImgDir;
	this->_posWinDir = builder->_posWinDir;
	this->_stride = builder->_stride;
}

ACFDetector::	~ACFDetector(){
	OUT("~ACFDetector()");
}

//ACFDetector::Builder::Builder(const string configFile){ cout << "Builder(config) from " << configFile << endl;}
ACFDetector::Builder::Builder(const string name,const string posDir,const string gtDir){
	OUT("Builder(string,string,string)");
	this->_name = name;
	this->_posImgDir = posDir;
	this->_gtDir = gtDir;
}

ACFDetector::Builder::~Builder(){
	delete this;
	OUT("~Builder() ");
}

//ostream& acf::operator<< (ostream& os,const acf::ACFDetector::Builder& b){
//	cout<< "Builder<<";
//	return os;
//}

std::ostream& acf::operator<<(std::ostream&os ,const ACFDetector& d){
	cout<< "ACFDetector{";
	cout << "name:"<<d._name<<',';
	cout << "posDir:"<<d._posImgDir<<',';
	cout << "gtDir:"<<d._gtDir<<',';
	cout << "modelDsPad:"<<d._modelDsPad<<"...}";
	return os;
}

ACFDetector::Builder* ACFDetector::Builder::negImgDir(std::string negDir){
	this->_negImgDir = negDir;
	return this;
}

ACFDetector::Builder* ACFDetector::Builder::posWinDir(std::string posWinDir){
	this->_posWinDir = posWinDir;
	return this;
}

ACFDetector::Builder* ACFDetector::Builder::negWinDir(std::string negWinDir){
	this->_negWinDir = negWinDir;
	return this;
}

ACFDetector::Builder* ACFDetector::Builder::modelDs(Size size){
	this->_modelDs = size;
	return this;
}

ACFDetector::Builder* ACFDetector::Builder::modelDsPad(cv::Size size){
	this->_modelDsPad = size;
	return this;
}

ACFDetector::Builder* ACFDetector::Builder::stride(int s){
	this->_stride = s;
	return this;
}

/**
 * Builder constructor to get a object
 */
ACFDetector ACFDetector:: Builder::build(){
	OUT("Build ACF Detector From Builder");
	return ACFDetector(this);
}

void ACFDetector::detectImg(std::vector<BoundingBox>& bbs,Mat image){
	OUT("detect image");
}

void ACFDetector::train(){
	OUT("train a detector here ");
}

void ACFDetector::test(){
	OUT("test module here");
}





