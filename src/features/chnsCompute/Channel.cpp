
#include "Channel.h"

#include <opencv2/objdetect/objdetect.hpp> // HOG Note: add opencv_objdetect to GCC linker setting

using namespace cv;
using namespace std;



void ColorChn::compute(float * const image,const cv::Vec3i dims){
	OUT("ColorChn::compute");
	float* data =  new float[dims.val[0]*dims.val[1]*dims.val[2]];
	this->chnData = data;
}

void GradHistChn::compute(float * const image,const cv::Vec3i dims){
	OUT("GradHistChn::compute");
	float* data =  new float[dims.val[0]*dims.val[1]*dims.val[2]];
	this->chnData = data;
}

void MagChn::compute(float * const image,const cv::Vec3i dims){
	OUT("MagChn::compute");
	float* data = new float[dims.val[0]*dims.val[1]*dims.val[2]];
	this->chnData = data;
}

void ChnsManager::compute(std::vector<float*>& chnDatas,float* image, const Vec3i dims){
	OUT("ChnsManager::compute");
	for(int i=0;i<chns.size();i++){
		chns[i]->compute(image,dims);
		chnDatas.push_back(chns[i]->data());
	}
}
