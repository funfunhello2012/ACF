


#include "mex/rgbConvertMex.hpp"
#include "mex/gradientMex.hpp"
#include "mex/wrappers.hpp"

#include "Channel.h"

using namespace cv;
using namespace std;



void ColorChn::compute(float * const image,const cv::Vec3i dims){
	OUT("ColorChn::compute");
	float* data = rgbConvert(image, dims[0]*dims[1],dims[2],0,1.0f); ;
	this->chnData = data;
}

void GradHistChn::compute(float * const image,const cv::Vec3i dims){
	OUT("GradHistChn::compute");
	int nCh = dims[2];
	int h2 = dims[0]/this->binSize;
	int w2 = dims[1]/this->binSize;
	float* M =  (float*) wrCalloc(dims[0]*dims[1]*nCh,sizeof(float));
	float* O =  (float*) wrCalloc(dims[0]*dims[1]*nCh,sizeof(float));
	float* H = (float*) wrCalloc(h2*w2*nCh*6,sizeof(float));
	gradHist(M,O,H,dims[0],dims[1],this->binSize,this->nOrients,0,1);
	this->chnData = H;
}

void MagChn::compute(float * const image,const cv::Vec3i dims){
	OUT("MagChn::compute");
	int h = dims[0];
	int w = dims[1];
	int nCh = dims[2];
	float* M =  (float*) wrCalloc(w*h*nCh,sizeof(float));
	float* O =  (float*) wrCalloc(h*w*nCh,sizeof(float));
	gradMag(image, M, O, h, w, nCh,1 );
	wrFree(O);
	this->chnData = M;
}

void ChnsManager::compute(std::vector<float*>& chnDatas,float* image, const Vec3i dims){
	OUT("ChnsManager::compute");
	for(int i=0;i<chns.size();i++){
		chns[i]->compute(image,dims);
		chnDatas.push_back(chns[i]->data());
	}
}
