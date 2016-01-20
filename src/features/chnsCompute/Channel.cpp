


#include "mex/rgbConvertMex.hpp"
#include "mex/gradientMex.hpp"
#include "mex/wrappers.hpp"

#include "Channel.h"

using namespace cv;
using namespace std;



void ColorChn::compute(float * const image,const cv::Vec3i dims){
	OUT("ColorChn::compute");
//	float* data = rgbConvert(image, dims[0]*dims[1],dims[2],0,1.0f); ;
	float* data = new float[dims[0]/4*dims[1]/4*3];
	for(int i=0;i<dims[0]/4*dims[1]/4*3;i++){
		data[i] = i;
	}
	this->chnData = data;
}

void GradHistChn::compute(float * const image,const cv::Vec3i dims){
	OUT("GradHistChn::compute");
//	int nCh = dims[2];
//	int h2 = dims[0]/this->binSize;
//	int w2 = dims[1]/this->binSize;
//	float* M =  new float[dims[0]*dims[1]*nCh];
//	float* O =  new float[dims[0]*dims[1]*nCh];
//	float* H = new float[h2*w2*nCh*6];
//	gradHist(M,O,H,dims[0],dims[1],this->binSize,this->nOrients,0,1);

	float* H = new float[dims[0]/4*dims[1]/4*6];
	for(int i=0;i<dims[0]/4*dims[1]/4*6;i++){
		H[i] = i;
	}
	this->chnData = H;
//	delete[] O;
//	delete[] M;
}

void MagChn::compute(float * const image,const cv::Vec3i dims){
	OUT("MagChn::compute");
//	int h = dims[0];
//	int w = dims[1];
//	int nCh = dims[2];
//	float* M =  new float[w*h*nCh];
//	float* O =  new float[h*w*nCh];
//	gradMag(image, M, O, h, w, nCh,1 );
//	delete[] O;

	float* M = new float[dims[0]/4*dims[1]/4];
	for(int i=0;i<dims[0]/4*dims[1]/4;i++){
		M[i] = i;
	}
	this->chnData = M;
}

void ChnsManager::compute(std::vector<float*>& chnDatas,float* image, const Vec3i dims){
	OUT("ChnsManager::compute");
	int shrink = 4;//this should be set through constructor
	this->chnSize = vector<Vec3i>(chns.size());
	for(int i=0;i<chns.size();i++){
		OUT_V(chns.size());
		Vec3i curChnSz =Vec3i(dims[0]/shrink, dims[1]/shrink,chns[i]->getChnNum());
		this->chnSize[i] = curChnSz;
		chns[i]->compute(image,dims);
		chnDatas.push_back(chns[i]->data());
	}
}
