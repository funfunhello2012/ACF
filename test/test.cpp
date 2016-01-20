/*
 * test.cpp
 *
 *  Created on: 2015年11月3日
 *      Author: edison
 */


#include "../src/detector/ACFDetector.h"
#include "../src/Util/common.h"
#include "../src//features/chnsCompute/Channel.h"
#include "../src/features/pyramid.h"
#include "../src/Util/IODetector.h"

using namespace std;
using namespace acf;

//use case 1 : load detector and detect image
void testLoadUseCase(){
	ACFDetector detector  =  loadDetectorFromMat("/home/edison/workspace/acfImplement/ACF/data/AcfInriaDetector.mat");
//	ACFDetector detector  =  loadDetectorFromJson("");
	vector<BoundingBox> bbs;
//	Mat image = imread("./data/I00000.png");
//	Mat image(5,3,CV_32FC3);
	Mat image(360,480,CV_32FC3);
	detector.detectImg(bbs,image);
}

//class ChnCustom: public Chn{
//public:
//	void compute(float * const image,const cv::Vec3i dims){
//		OUT("Custom compute");
//	}
//};

//use case 2 :
void testTrainTestUseCase(){
	ACFDetector::Builder* builder = new ACFDetector::Builder("detectorName","posDir","gtDir");
	ACFDetector detector = builder->build();
	Mat img;
	ChnsManager* chnsManager = detector.getChnsManager();
	Pyramid* pyramid = detector.getPyramid();
//	Chn* chn  = new ChnCustom();
//	chnsManager->addChn(chn);
	vector<vector<Mat> > datas;
//	pyramid->computeData(img,datas);
	detector.train();
	detector.test();
}




#if NOW_TESTING == TEST_ALL
int main( int argc, char** argv ){
	testLoadUseCase();
//	testTrainTestUseCase();
}
#endif
