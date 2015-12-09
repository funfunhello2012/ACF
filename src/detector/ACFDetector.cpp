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
	this->_clf = builder->_clf;
}

ACFDetector::	~ACFDetector(){
	OUT("~ACFDetector()");
	delete[] this->_clf->child;
	delete[] this->_clf->fids;
	delete[] this->_clf->hs;
	delete[] this->_clf->thrs;
	delete this->_clf;
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
	cout << "negDir:"<<d._negImgDir<<',';
	cout << "posWinDir:"<<d._posWinDir<<',';
	cout << "negWinDir:"<<d._negWinDir<<',';
	cout << "stride:"<<d._stride<<',';
	cout << "modelDsPad:"<<d._modelDsPad<<',';
	cout << "modelDs:"<<d._modelDs<<"...}";
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

ACFDetector::Builder* ACFDetector::Builder::Classifier(Clf* c){
	this->_clf = c;
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





