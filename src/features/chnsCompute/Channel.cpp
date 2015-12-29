
#include "Channel.h"

#include <opencv2/objdetect/objdetect.hpp> // HOG Note: add opencv_objdetect to GCC linker setting

//using namespace cv;
using namespace std;
using namespace acf;

void ColorChn::compute(acf::MatrixD& img){
	OUT("CololChn::compute");
	this->chnImg = new MatrixD(img.cols,img.rows);
}

void GradHistChn::compute(acf::MatrixD& img){
	OUT("GradHistChn::compute");
	this->chnImg = new MatrixD(img.cols,img.rows);
}
//#if USE_MEX
//extern void cvtColor2(Mat &II, Mat &JJ, int code);
//#endif
//
//void ColorChn::compute(void){
//	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//	// % compute color channels
//	// p=pChns.pColor; nm='color channels';
//	// I=rgbConvert(I,p.colorSpace); I=convTri(I,p.smooth);
//	// if(p.enabled), chns=addChn(chns,I,nm,p,'replicate',h,w); end
//	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
//#if USE_MEX
//	cvtColor2(img, img,0);
//#else
//	cvtColor(img, img, colorSpace);
//#endif
//	//cvtColor2(img, img,0);
//	// smoothing is not available now.
//}
//
//void GradHistChn::compute(void){
//// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//// % compute custom channels
//// p=pChns.pCustom;
//// for i=find( [p.enabled] )
////   C=feval(p(i).hFunc,I,p(i).pFunc{:});
////   chns=addChn(chns,C,p(i).name,p(i),p(i).padWith,h,w);
//// end
//// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//
//#if USE_MEX
//	// to do...
//#else
//	cvtColor(img, img, CV_RGB2GRAY);
//
//	// test 6 bins hog
//	HOGDescriptor d(
//	Size(img.rows,img.cols), //winSize
//	Size(binSize,binSize), //blocksize
//	Size(binSize,binSize),  //blockStride,
//	 Size(binSize,binSize), //cellSize,
//	 nOrients//nbins,
//	// 0, //derivAper,
//	// -1, //winSigma,
//	// 0, //histogramNormType,
//	// 0.2, //L2HysThresh,
//	// 0 //gammal correction,
//	// //nlevels=64
//	);
//
//	// void HOGDescriptor::compute(const Mat& img, vector<float>& descriptors,
//	//                             Size winStride, Size padding,
//	//                             const vector<Point>& locations) const
//
//	vector<float> descriptorsValues;
//	//vector<Point> locations;
//	d.compute( img, descriptorsValues); // , Size(0,0), Size(0,0), locations
//
//	cout << "HOG descriptor size is " << d.getDescriptorSize() << endl;
//	cout << "img dimensions: " << img.cols << " width x " << img.rows << "height" << endl;
//	cout << "Found " << descriptorsValues.size() << " descriptor values" << endl;
//	//cout << "Nr of locations specified : " << locations.size() << endl;
//	  // HOG descriptor size is 3780
//	  //  img dimensions: 1060 width x 605height
//	  //  Found 28350000 descriptor values
//	  //  Nr of locations specified : 0
//
//	OUT_V(Mat(descriptorsValues).size());
//	img = Mat(descriptorsValues).reshape(nOrients, img.rows/binSize); //see http://docs.opencv.org/2.4/modules/core/doc/basic_structures.html
//   OUT_V(img.size());
//
//	// trouble of size: see http://stackoverflow.com/questions/14315488/opencv-getting-stdlength-error-what-vector-m-fill-insert-when-computing
//#endif
//	//  is not available now.
//}
//
void MagChn::compute(acf::MatrixD& img){
	OUT("Computing gradient magnitude");
	this->chnImg = new MatrixD(img.cols,img.rows);
}

void ChnsManager::compute(std::vector<acf::MatrixD*>& chnDatas,acf::MatrixD& image){
	OUT( "compute channels data");
	for(int i=0;i<chns.size();i++){
		chns[i]->compute(image);
		chnDatas.push_back(chns[i]->data());
	}
}
