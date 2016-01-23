#include "Channel.h"

using namespace cv;
using namespace std;



void ColorChn::compute(float * const image,const cv::Vec3i dims){
	OUT("ColorChn::compute");
//	float* data = rgbConvert(image, dims[0]*dims[1], dims[2],2, 1.0f/255) ;
	float* data = new float[dims[0]*dims[1]*dims[2]];
	memcpy(data,image,sizeof(float)*dims[0]*dims[1]*dims[2]);
	this->chnData = data;
	this->dims = Vec3i(dims[0],dims[1],dims[2]);
}

ColorChn::~ColorChn(){
	delete []chnData;
}

void GradHistChn::compute(float * const image,const cv::Vec3i dims){
	OUT("GradHistChn::compute");
	Size sz = Size(dims[1],dims[0]);
	float*M = new float[sz.height*sz.width];
	float* O = new float[sz.height*sz.width];
	int normRad = 5;
	float normConst=.005;
	bool full = 0;
//	float* luvImg = rgbConvert(originImg, sz.height*sz.width, nCh,2, 1.0f/255) ;
	gradMag(image,M, O,sz.height,sz.width,3,false);
	float* convRes = new float[sz.height*sz.width*1];
	convTri( M, convRes, sz.height, sz.width,1,normRad, 1 );
	gradMagNorm(M,convRes,sz.height,sz.width,normConst);
	int hb,wb,nChns;
	hb = sz.height/binSize;
	wb = sz.width/binSize;
	nChns = useHog== 0 ? nOrients : (useHog==1 ? nOrients*4 : nOrients*3+5);
	float* H = new float[hb*wb*nChns];
	if( useHog==0 ) {
		gradHist( M, O, H, sz.height, sz.width, binSize, nOrients, softBin, full );
	} else if(useHog==1) {
		hog( M, O, H,  sz.height, sz.width, binSize, nOrients, softBin, full, clipHog );
	} else {
		fhog( M, O, H,  sz.height, sz.width, binSize, nOrients, softBin, clipHog );
	}

	this->chnData = H;
	this->dims = Vec3i(hb,wb,nChns);
	delete[] O;
	delete[] M;
}

GradHistChn::~GradHistChn(){
	delete[]chnData;
}

void MagChn::compute(float * const image,const cv::Vec3i dims){
	OUT("MagChn::compute");

//	float* luvImg = rgbConvert(originImg, sz.height*sz.width, nCh,2, 1.0f/255) ;
//	gradMag(luvImg,M, O,sz.height,sz.width,3,false);
//	float* convRes = new float[sz.height*sz.width*1];
//	convTri( M, convRes, sz.height, sz.width,1,normRad, 1 );
//	gradMagNorm(M,convRes,sz.height,sz.width,normConst);

	float* M = new float[dims[0]*dims[1]];
	float* O=0;
	Size sz = Size(dims[1],dims[0]);
//	float* luvImg = rgbConvert(image, sz.height*sz.width, dims[2],2, 1.0f/255) ;	//mind
	gradMag(image,M, O,sz.height,sz.width,3,false);
	float* convRes = new float[sz.height*sz.width*1];
	convTri( M, convRes, sz.height, sz.width,1,normRad, 1 );
	gradMagNorm(M,convRes,sz.height,sz.width,normConst);
	this->chnData = M;
	this->dims = Vec3i(dims[0],dims[1],1);
	delete convRes;
}

MagChn::~MagChn(){
	delete []chnData;
}

void ChnsManager::compute(std::vector<float*>& chnDatas,float* image, const Vec3i dims){
	OUT("ChnsManager::compute");
	int shrink = this->shrink;//this should be set through constructor
	this->chnSize = vector<Vec3i>(chns.size());
	int h = dims[0]/shrink;
	int w = dims[1]/shrink;
	for(int i=0;i<chns.size();i++){
		if(chns[i]->isEnabled()){//compute if the channel is enabled
			int nChns = chns[i]->getChnNum();
			Vec3i outChnSz =Vec3i(h, w,nChns);
			this->chnSize[i] = outChnSz;
			chns[i]->compute(image,dims);
			Vec3i chnDims = chns[i]->getChnDims();
			//if(chnDims[0]!=outChnSz[0] || chnDims[1]!=outChnSz[1]) //resample the data here
				//imResampleMex(chns[i]->data())
			float* chnDataOut = new float[h*w*nChns];
			resample((float*)chns[i]->data(), (float*)chnDataOut, chnDims[0], h, chnDims[1], w, nChns,1.0f);
			chnDatas.push_back(chnDataOut);
		}
	}
}
