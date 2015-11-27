#include <iostream>
#include "../Util/common.h"
using namespace std;


class Pyramid{
public:
	Pyramid(ChnsManager manager){	}
	void computeData(Mat image,vector<Mat*>& data){
		OUT("compute pyramid Data");
	}

private:
	//	int nPerOct;      // [8] number of scales per octave
	//	int nOctUp;       // [0] number of upsampled octaves to compute
	//	int nApprox;      //[-1] number of approx. scales (if -1 nApprox=nPerOct-1)
	//	float* lambdas;      // [] coefficients for power law scaling (see BMVC10)
	//	int *pad;          // [0 0] amount to pad channels (along T/B and L/R)
	//	int *minDs;        // [16 16] minimum image size for channel computation
	//	int smooth;       //[1] radius for channel smoothing (using convTri)
	//	bool concat;       //[1] if true concatenate channels
	//	bool complete;     // [] if true does not check/set default vals in pPyramid
	//	int nTypes;       // number of channel types
	//	int nScales;      //number of scales computed
};

//class pChns{
//
//};
//class pPyramid{
//
//public:
//	pPyramid(pChns pchns,int nperoct,int npctup,int napprox,float *la,int pa[2],int minds[2],int sm,bool conc,bool complet){
//		pPyramid_pChns=pchns;
//		nPerOct=nperoct;
//		nOctUp=npctup;
//		nApprox=napprox;
//		lambdas=la;
//		pad=pa;
//		minDs=minds;
//		smooth=sm;
//		concat=conc;
//		complete=complet;
//	}
//	pPyramid(){}
//	~pPyramid(){}
//	int getnPerOct(){
//	return nPerOct;
//	}
//	int getnOctUp(){
//	return nOctUp;
//	}
//	int getnApprox(){
//		return nApprox;
//	}
//	float* getlambdas(){
//		return lambdas;
//	}
//	int* getpad(){
//		return pad;
//	}
//	int* getminDs(){
//		return minDs;
//	}
//	int getsmooth(){
//		return smooth;
//	}
//	bool getconcat(){
//		return concat;
//	}
//	bool getcomplete(){
//		return complete;
//	}
//	pChns getpPyramid_pChns(){
//		return pPyramid_pChns;
//	}
//private:
//	pChns pPyramid_pChns;
//	int nPerOct;      // [8] number of scales per octave
//	int nOctUp;       // [0] number of upsampled octaves to compute
//	int nApprox;      //[-1] number of approx. scales (if -1 nApprox=nPerOct-1)
//	float* lambdas;      // [] coefficients for power law scaling (see BMVC10)
//	int *pad;          // [0 0] amount to pad channels (along T/B and L/R)
//	int *minDs;        // [16 16] minimum image size for channel computation
//	int smooth;       //[1] radius for channel smoothing (using convTri)
//	bool concat;       //[1] if true concatenate channels
//	bool complete;     // [] if true does not check/set default vals in pPyramid
//};
//class data{
//};
//class info{
//};
//class pyramid{
//public:
//	pyramid(pPyramid pyramid_ppyramid,int ntypes,int nscales){
//
//	}
//	pyramid(){}
//	~pyramid(){}
//private:
//	pPyramid pyramid_pPyramid;

//	data* pyramid_data;         // [nScales x nTypes] cell array of computed channels
//	info* pyramid_info;      // [nTypes x 1] struct array (mirrored from chnsCompute)
//	float* lambdas;     //[nTypes x 1] scaling coefficients actually used
//	float* scales;       //[nScales x 1] relative scales (approximate)
//	//int()(2) scaleshw     - [nScales x 2] exact scales for resampling h and w
//};
//
//pyramid compute();
