/*
 * test.cpp
 *
 *  Created on: 2015年11月3日
 *      Author: edison
 */
#include "IOUtil.h"
extern "C"{
#include "matio.h"
}
#include "../detector/ACFDetector.h"
#include "../features/Params.h"
#include "common.h"
#include "../features/chnsCompute/Channel.h"
#include "../features/pyramid.h"

using namespace std;
using namespace acf;

//use case 1 : load detector and detect image
void testLoadUseCase(){
	ACFDetector detector  =  loadDetectorFromMat("test.mat");
	vector<BoundingBox> bbs;
	Mat image;
	detector.detectImg(bbs,image);
}

class ChnCustom: public Chn{
public:
	void compute(){
		OUT("Custom compute");
	}
};
//use case 2 :
void testTrainTestUseCase(){
	ACFDetector detector = ACFDetector::Builder("conf/detector.conf").build();
	Mat img;
	ChnsManager chnsManager;
	Pyramid pyramid(chnsManager);
	Chn* chn  = new ChnCustom();
	chnsManager.addChn(chn);
	vector<Mat*> datas;
	pyramid.computeData(img,datas);
	detector.train();
	detector.test();
}

//ParamChns test
//void testParamChannel(){
//	vector<IParamChns*> pChannels;
//	ParamChnsColor colorChns;
//	ParamChnsGrad GradChns;
//	ParamChnsMag MagChns;
//	pChannels.push_back(&colorChns);
//	pChannels.push_back(&GradChns);
//	pChannels.push_back(&MagChns);
//
//	for(int i=0;i<pChannels.size();i++){
//		switch(pChannels[i]->getChnsType()){
//		case Color:cout <<  i <<" is Color channel" << endl;break;
//		case GradHist:cout <<  i <<" is Grad Histogram channel" << endl;break;
//		case GradMag:cout <<  i <<" is Grad Mag channel" << endl;break;
//		case Custom:cout << i << " is Custom channel" << endl;
//		}
//	}
//}

void testReadShowImage(){
		try{
			cv::Mat image;
			image = acf::imread( "test.jpg");
			acf::imshow(image);
			acf::imwrite("testOut.jpg",image);
		}
		catch(const std::invalid_argument& ia){
			cout << "Exception:"<< ia.what()  << "test.jpg" << " is not a valid for read!" << endl;
		}
}

int main( int argc, char** argv ){
//	testLoadUseCase();
	testTrainTestUseCase();
//	testParamChannel();
//	testReadShowImage();

//	mat_t *matfp;
//	matfp = Mat_Open(argv[1],MAT_ACC_RDONLY);
//	if ( NULL == matfp ) {
//		fprintf(stderr,"Error opening MAT file %s\n",argv[1]);
//		return EXIT_FAILURE;
//	}
//
//	matvar_t * matvar;
//	matvar = Mat_VarRead(matfp,"dtmp");
//	//    matvar = Mat_VarReadInfo(matfp,"detector");
//	if(NULL!=matvar){
//		printf("read in\n");
//		matvar_t* opts = Mat_VarGetStructFieldByName(matvar,"opts",0);
//		if(opts!=NULL){
//			Mat_VarPrint(opts,1);
//		}

//		matvar_t* cls = Mat_VarGetStructFieldByName(matvar,"cls",0);
//		if(cls!=NULL){
//			Mat_VarPrint(cls,1);
//		}
//		matvar_t* info = Mat_VarGetStructFieldByName(matvar,"info",0);
//		if(info!=NULL){
//			Mat_VarPrint(info,1);
//		}

//		Mat_VarFree(matvar);
//	}
//	else{
//		printf("detector content is null\n");
//	}
//	Mat_Close(matfp);
//	return EXIT_SUCCESS;

}
