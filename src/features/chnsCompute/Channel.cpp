#include "Channel.h"

using namespace cv;
using namespace std;



void ColorChn::compute(float * const image,const cv::Vec3i dims){
	OUT("ColorChn::compute");
//	float* data = rgbConvert(image, dims[0]*dims[1],dims[2],0,1.0f); ;
	float* data = new float[dims[0]*dims[1]*dims[2]];
	for(int i=0;i<dims[0]*dims[1]*dims[2];i++){
		data[i] = i;
	}
	this->chnData = data;
	this->dims = Vec3i(dims[0],dims[1],dims[2]);
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

	float* H = new float[dims[0]/binSize*dims[1]/binSize*nOrients];
	for(int i=0;i<dims[0]/binSize*dims[1]/binSize*nOrients;i++){
		H[i] = i;
	}
	this->chnData = H;
	this->dims = Vec3i(dims[0]/binSize,dims[1]/binSize,nOrients);
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

	float* M = new float[dims[0]*dims[1]];
	for(int i=0;i<dims[0]*dims[1];i++){
		M[i] = i;
	}
	this->chnData = M;
	this->dims = Vec3i(dims[0],dims[1],1);
}

void ChnsManager::compute(std::vector<float*>& chnDatas,float* image, const Vec3i dims){
	OUT("ChnsManager::compute");
	int shrink = this->shrink;//this should be set through constructor
	this->chnSize = vector<Vec3i>(chns.size());
	int h = dims[0]/shrink;
	int w = dims[1]/shrink;
	for(int i=0;i<chns.size();i++){
		OUT_V(chns.size());
		if(chns[i]->isEnabled()){//compute if the channel is enabled
			Vec3i outChnSz =Vec3i(h, w,chns[i]->getChnNum());
			this->chnSize[i] = outChnSz;
			chns[i]->compute(image,dims);
			Vec3i chnDims = chns[i]->getChnDims();
			//if(chnDims[0]!=outChnSz[0] || chnDims[1]!=outChnSz[1]) //resample the data here
				//imResampleMex(chns[i]->data())
			chnDatas.push_back(chns[i]->data());
		}
	}
}
