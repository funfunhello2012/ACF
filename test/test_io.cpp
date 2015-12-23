/*
 * test_io.cpp
 *
 *  Created on: 2015年12月3日
 *      Author: edison
 */
extern "C"{
#include "matio.h"
}

#include "../src/Util/common.h"
#include "../src/Util/IODetector.h"
#include "../src/detector/ACFDetector.h"

using namespace std;
using namespace acf;

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

void testMatRead(char* matPath){

	mat_t *matfp;
	matfp = Mat_Open(matPath,MAT_ACC_RDONLY);
	if ( NULL == matfp ) {
		fprintf(stderr,"Error opening MAT file %s\n",matPath);
		return;
	}

	matvar_t * matvar;
	matvar = Mat_VarRead(matfp,"detector");
//	matvar_t* matInfo;
//	matInfo = Mat_VarReadInfo(matfp,"detector");
//	Mat_VarPrint(matInfo,0);
	if(NULL!=matvar){
		matvar_t* opts = Mat_VarGetStructFieldByName(matvar,"opts",0);
		if(opts!=NULL){
			OUT("Read Detector opts Field");
			//opts.pPyramid
			matvar_t* opts_pPyramid = Mat_VarGetStructFieldByName(opts,"pPyramid",0);
			if(opts_pPyramid!=NULL){
				//detector.opts.pPyramid.pChns.shrink
				matvar_t* opts_pPyramid_pChns = Mat_VarGetStructFieldByName(opts_pPyramid,"pChns",0);
				matvar_t* opts_pPyramid_pChns_shrink = Mat_VarGetStructFieldByName(opts_pPyramid_pChns,"shrink",0);
				double * shrink = (double*) opts_pPyramid_pChns_shrink->data;
				OUT("opts.pPyramid.pChns.shrink");
				OUT(*shrink);

				//opts.pPyramid.nPerOct
				matvar_t* opts_pPyramid_nPerOct =  Mat_VarGetStructFieldByName(opts_pPyramid,"nPerOct",0);
				double * nPerOct = (double*) opts_pPyramid_nPerOct->data;
				OUT("opts.pPyramid.nPerOct");
				OUT(*nPerOct);

				//opts.pPyramid.nOctUp
				matvar_t* opts_pPyramid_nOctUp =  Mat_VarGetStructFieldByName(opts_pPyramid,"nOctUp",0);
				double * nOctUp = (double*) opts_pPyramid_nOctUp->data;
				OUT("opts.pPyramid.nOctUp");
				OUT(*nOctUp);

				//opts.pPyramid.nApprox
				matvar_t* opts_pPyramid_nApprox=  Mat_VarGetStructFieldByName(opts_pPyramid,"nApprox",0);
				double * nApprox = (double*) opts_pPyramid_nApprox->data;
				OUT("opts.pPyramid.nApprox");
				OUT(*nApprox);

				//opts.pPyramid.lambdas
				matvar_t* opts_pPyramid_lambdas=  Mat_VarGetStructFieldByName(opts_pPyramid,"lambdas",0);
				double * lambdas = (double*) opts_pPyramid_lambdas->data;
				OUT("opts.pPyramid.lambdas");
				int len = opts_pPyramid_lambdas->dims[1];
				for(int i=0;i<len;i++) OUT(lambdas[i]);

				//opts.pPyramid.pad
				matvar_t* opts_pPyramid_pad =  Mat_VarGetStructFieldByName(opts_pPyramid,"pad",0);
				double * pad = (double*) opts_pPyramid_pad->data;
				OUT("opts.pPyramid.pad");
				OUT(*pad);
				OUT(*(pad+1));

				//opts.pPyramid.minDs
				matvar_t* opts_pPyramid_minDs =  Mat_VarGetStructFieldByName(opts_pPyramid,"minDs",0);
				double * minDs = (double*) opts_pPyramid_minDs->data;
				OUT("opts.pPyramid.minDs");
				OUT(*minDs);
				OUT(*(minDs+1));

				//opts.pPyramid.smooth
				matvar_t* opts_pPyramid_smooth =  Mat_VarGetStructFieldByName(opts_pPyramid,"smooth",0);
				double * smooth = (double*) opts_pPyramid_smooth->data;
				OUT("opts.pPyramid.smooth");
				OUT(*smooth);

				//opts.pPyramid.concat
				matvar_t* opts_pPyramid_concat =  Mat_VarGetStructFieldByName(opts_pPyramid,"concat",0);
				double * concat = (double*) opts_pPyramid_concat->data;
				OUT("opts.pPyramid.concat");
				OUT(*concat);
			}
			//opts.filters
//			matvar_t * opts_filters = Mat_VarGetStructFieldByName(opts,"filters",0);

			//opts.modelDs
			matvar_t* opts_modelDs = Mat_VarGetStructFieldByName(opts,"modelDs",0);
			double *modelDs = (double *) opts_modelDs->data;
			OUT("opts.modelDs");
			OUT(modelDs[0]);
			OUT(modelDs[1]);

			//opts.modelDsPad
			matvar_t* opts_modelDsPad = Mat_VarGetStructFieldByName(opts,"modelDsPad",0);
			double *modelDsPad = (double *) opts_modelDsPad->data;
			OUT("opts.modelDsPad");
			OUT(modelDsPad[0]);
			OUT(modelDsPad[1]);

			//opts.pNms
			matvar_t* opts_pNms = Mat_VarGetStructFieldByName(opts,"pNms",0);
			if(opts_pNms!=NULL){
				//opts.pNms.type
				matvar_t* opts_pNms_type = Mat_VarGetStructFieldByName(opts_pNms,"type",0);
				char * pNmsType = (char*) opts_pNms_type->data;
				OUT("opts.pNms.type");
				OUT(pNmsType);

				//opts.pNms.overlap
				matvar_t* opts_pNms_overlap = Mat_VarGetStructFieldByName(opts_pNms,"overlap",0);
				double * overlap = (double*) opts_pNms_overlap->data;
				OUT("opts.pNms.overlap");
				OUT(*overlap);

				//opts.pNms.ovrDnm
				matvar_t* opts_pNms_ovrDnm = Mat_VarGetStructFieldByName(opts_pNms,"ovrDnm",0);
				char * ovrDnm = (char*) opts_pNms_ovrDnm->data;
				OUT("opts.pNms.ovrDnm");
				OUT(ovrDnm);
			}

			//opts.stride
			matvar_t* opts_stride = Mat_VarGetStructFieldByName(opts,"stride",0);
			double *stride = (double*) opts_stride->data;
			OUT("opts.Stride");
			OUT(*stride);

			//opts.cascThr
			matvar_t* opts_cascThr = Mat_VarGetStructFieldByName(opts,"cascThr",0);
			double *cascThr = (double*) opts_cascThr->data;
			OUT("opts.cascThr");
			OUT(*cascThr);

			//opts.cascCal
			matvar_t* opts_cascCal = Mat_VarGetStructFieldByName(opts,"cascCal",0);
			double *cascCal = (double*) opts_cascCal->data;
			OUT("opts.cascCal");
			OUT(*cascCal);

			//opts.nWeakl
			matvar_t* opts_nWeak = Mat_VarGetStructFieldByName(opts,"nWeak",0);
			double *nWeak = (double*) opts_nWeak->data;
			OUT("opts.nWeak");
			int n = opts_nWeak->dims[1];
			for(int i=0;i<n;i++) OUT(nWeak[i]);

			//opts.pBoost
			matvar_t* opts_pBoost = Mat_VarGetStructFieldByName(opts,"pBoost",0);
			if(opts_pBoost!=NULL){
				//opts.pBoost.pTree
				matvar_t* opts_pBoost_pTree = Mat_VarGetStructFieldByName(opts_pBoost,"pTree",0);
				//opts.pBoost.pTree.nBins
				matvar_t* opts_pBoost_pTree_nBins = Mat_VarGetStructFieldByName(opts_pBoost_pTree,"nBins",0);
				double *nBins = (double*) opts_pBoost_pTree_nBins->data;
				OUT("opts.pBoost.pTree.nBins");
				OUT(*nBins);

				//opts.pBoost.pTree.maxDepth
				matvar_t* opts_pBoost_pTree_maxDepth = Mat_VarGetStructFieldByName(opts_pBoost_pTree,"maxDepth",0);
				double *maxDepth = (double*) opts_pBoost_pTree_maxDepth->data;
				OUT("opts.pBoost.pTree.maxDepth");
				OUT(*maxDepth);

				//opts.pBoost.pTree.minWeight
				matvar_t* opts_pBoost_pTree_minWeight = Mat_VarGetStructFieldByName(opts_pBoost_pTree,"minWeight",0);
				double *minWeight = (double*) opts_pBoost_pTree_minWeight->data;
				OUT("opts.pBoost.pTree.minWeight");
				OUT(*minWeight);

				//opts.pBoost.pTree.fracFtrs
				matvar_t* opts_pBoost_pTree_fracFtrs = Mat_VarGetStructFieldByName(opts_pBoost_pTree,"fracFtrs",0);
				double *fracFtrs = (double*) opts_pBoost_pTree_fracFtrs->data;
				OUT("opts.pBoost.pTree.fracFtrs");
				OUT(*fracFtrs);

				//opts.pBoost.pTree.nThreads
				matvar_t* opts_pBoost_pTree_nThreads = Mat_VarGetStructFieldByName(opts_pBoost_pTree,"nThreads",0);
				double *nThreads = (double*) opts_pBoost_pTree_nThreads->data;
				OUT("opts.pBoost.pTree.nThreads");
				OUT(*nThreads);

				//opts.pBoost.nWeak
				matvar_t* opts_pBoost_nWeak = Mat_VarGetStructFieldByName(opts_pBoost,"nWeak",0);
				double *pBoostNWeak = (double*) opts_pBoost_nWeak->data;
				OUT("opts.pBoost.nWeak");
				OUT(*pBoostNWeak);

				//opts.pBoost.discrete
				matvar_t* opts_pBoost_discrete = Mat_VarGetStructFieldByName(opts_pBoost,"discrete",0);
				double *discrete = (double*) opts_pBoost_discrete->data;
				OUT("opts.pBoost.discrete");
				OUT(*discrete);

				//opts.pBoost.verbose
				matvar_t* opts_pBoost_verbose = Mat_VarGetStructFieldByName(opts_pBoost,"verbose",0);
				double *verbose = (double*) opts_pBoost_verbose->data;
				OUT("opts.pBoost.verbose");
				OUT(*verbose);
			}

			//opts.seed
//			matvar_t* opts_seed = Mat_VarGetStructFieldByName(opts,"seed",0);
			//opts.name
			matvar_t* opts_name = Mat_VarGetStructFieldByName(opts,"name",0);
			char* name = (char*)opts_name->data;
			OUT("opts.name");
			OUT(name);

			//opts.posGtDir
			matvar_t* opts_posGtDir = Mat_VarGetStructFieldByName(opts,"posGtDir",0);
			char* posGtDir = (char*)opts_posGtDir->data;
			OUT("opts.posGtDir");
			OUT(posGtDir);

			//opts.posImgDir
			matvar_t* opts_posImgDir = Mat_VarGetStructFieldByName(opts,"posImgDir",0);
			char* posImgDir = (char*)opts_posImgDir->data;
			OUT("opts.posImgDir");
			OUT(posImgDir);

			//opts.negImgDir
			matvar_t* opts_negImgDir = Mat_VarGetStructFieldByName(opts,"negImgDir",0);
			char* negImgDir = (char*)opts_negImgDir->data;
			OUT("opts.negImgDir");
			OUT(negImgDir);

			//opts.posWinDir
//			matvar_t* opts_posWinDir = Mat_VarGetStructFieldByName(opts,"posWinDir",0);
//			char* posWinDir = (char*)opts_posWinDir->data;
//			OUT("opts.posWinDir");
//			OUT(posWinDir);

			//opts.negWinDir
//			matvar_t* opts_negWinDir = Mat_VarGetStructFieldByName(opts,"negWinDir",0);
//			char* negWinDir = (char*)opts_negWinDir->data;
//			OUT("opts.negWinDir");
//			OUT(negWinDir);

			//opts.nPos
			matvar_t* opts_nPos = Mat_VarGetStructFieldByName(opts,"nPos",0);
			double *nPos = (double*) opts_nPos->data;
			OUT("opts.nPos");
			OUT(*nPos);

			//opts.nNeg
			matvar_t* opts_nNeg = Mat_VarGetStructFieldByName(opts,"nNeg",0);
			double *nNeg = (double*) opts_nNeg->data;
			OUT("opts.nNeg");
			OUT(*nNeg);

			//opts.nPerNeg
			matvar_t* opts_nPerNeg = Mat_VarGetStructFieldByName(opts,"nPerNeg",0);
			double *nPerNeg = (double*) opts_nPerNeg->data;
			OUT("opts.nPerNeg");
			OUT(*nPerNeg);

			//opts.nAccNeg
			matvar_t* opts_nAccNeg = Mat_VarGetStructFieldByName(opts,"nAccNeg",0);
			double *nAccNeg = (double*) opts_nAccNeg->data;
			OUT("opts.nAccNeg");
			OUT(*nAccNeg);

			//opts.winsSave
			matvar_t* opts_winsSave = Mat_VarGetStructFieldByName(opts,"winsSave",0);
			double *winsSave = (double*) opts_winsSave->data;
			OUT("opts.winsSave");
			OUT(*winsSave);
		}//end opts

		matvar_t* clf = Mat_VarGetStructFieldByName(matvar,"clf",0);
		if(clf!=NULL){
			OUT("Read Detector clf Field");
			//clf.fids
			matvar_t* clf_fids = Mat_VarGetStructFieldByName(clf,"fids",0);
			unsigned int * fids = (unsigned int*) clf_fids->data;
			OUT("cls.fids");
			OUT(clf_fids->dims[0]);
			OUT(clf_fids->dims[1]);
//			OUT(*(fids+2));

			//clf.thrs
			matvar_t* clf_thrs = Mat_VarGetStructFieldByName(clf,"thrs",0);
			float *thrs = (float*) clf_thrs->data;
			OUT("cls.thrs");
			OUT(clf_thrs->dims[0]);
			OUT(clf_thrs->dims[1]);
//			OUT(*(thrs+2));

			//clf.child
			matvar_t* clf_child = Mat_VarGetStructFieldByName(clf,"child",0);
			unsigned int *child = (unsigned int*) clf_child->data;
			OUT("cls.child");
			OUT(clf_child->dims[0]);
			OUT(clf_child->dims[1]);
//			OUT(*(child+2));

			//clf.hs
			matvar_t* clf_hs = Mat_VarGetStructFieldByName(clf,"hs",0);
			float *hs = (float*) clf_hs->data;
			OUT("cls.hs");
			OUT(clf_hs->dims[0]);
			OUT(clf_hs->dims[1]);
//			OUT(*(hs+2));

			//clf.weights
			matvar_t* clf_weights = Mat_VarGetStructFieldByName(clf,"weights",0);
			float *weights = (float*) clf_weights->data;
			OUT("cls.weights");
			OUT(clf_weights->dims[0]);
			OUT(clf_weights->dims[1]);
//			OUT(*(weights+2));

			//clf.depth
			matvar_t* clf_depth = Mat_VarGetStructFieldByName(clf,"depth",0);
			unsigned int  *depth = (unsigned int *) clf_depth->data;
			OUT("cls.depth");
			OUT(clf_depth->dims[0]);
			OUT(clf_depth->dims[1]);
//			OUT(*(depth+2));

			//clf.errs
			matvar_t* clf_errs = Mat_VarGetStructFieldByName(clf,"errs",0);
			double *errs = (double*) clf_errs->data;
			OUT("cls.errs");
			OUT(clf_errs->dims[0]);
			OUT(clf_errs->dims[1]);
//			OUT(*(errs+2));

			//clf.losses
			matvar_t* clf_losses = Mat_VarGetStructFieldByName(clf,"losses",0);
			double *losses = (double*) clf_losses->data;
			OUT("cls.losses");
			OUT(clf_losses->dims[0]);
			OUT(clf_losses->dims[1]);
//			OUT(*(losses+2));

			//clf.treeDepth
			matvar_t* clf_treeDepth = Mat_VarGetStructFieldByName(clf,"treeDepth",0);
			unsigned int *treeDepth = (unsigned int*) clf_treeDepth->data;
			OUT("cls.treeDepth");
			OUT(*treeDepth);
		}//end clf

		matvar_t* info = Mat_VarGetStructFieldByName(matvar,"info",0);
		if(info!=NULL){
			OUT("Read detector info field");
			//info
			int idx = 0;
			matvar_t* info_name = Mat_VarGetStructFieldByName(info,"name",idx);
			matvar_t* info_pChn = Mat_VarGetStructFieldByName(info,"pChn",idx);
//			matvar_t* info_nChns = Mat_VarGetStructFieldByName(info,"nChns",idx);
//			matvar_t* info_padWith = Mat_VarGetStructFieldByName(info,"padWith",idx);

			//color channel
			char *colorName = (char*) info_name->data;
			OUT("info.name");
			OUT(colorName);
			matvar_t* info_pChn_enabled = Mat_VarGetStructFieldByName(info_pChn,"enabled",0);
			double * colorEnabled = (double *)info_pChn_enabled->data;
			OUT("info.pChn.enabled");
			OUT(*colorEnabled);
			matvar_t* info_pChn_smooth = Mat_VarGetStructFieldByName(info_pChn,"smooth",0);
			double * colorSmooth = (double *)info_pChn_smooth->data;
			OUT("info.pChn.smooth");
			OUT(*colorSmooth);
			matvar_t* info_pChn_colorSpace = Mat_VarGetStructFieldByName(info_pChn,"colorSpace",0);
			char * colorSpace = (char *)info_pChn_colorSpace->data;
			OUT("info.pChn.colorSpace");
			OUT(colorSpace);

			//gradient magnitude channel
			idx = 1;
			info_name = Mat_VarGetStructFieldByName(info,"name",idx);
			char* magName = (char*) info_name->data;
			OUT("info.name");
			OUT(magName);
			info_pChn = Mat_VarGetStructFieldByName(info,"pChn",idx);
			info_pChn_enabled = Mat_VarGetStructFieldByName(info_pChn,"enabled",0);
			double * magEnabled = (double *)info_pChn_enabled->data;
			OUT("info.pChn.enabled");
			OUT(*magEnabled);
			matvar_t* info_pChn_colorChn = Mat_VarGetStructFieldByName(info_pChn,"colorChn",0);
			double * colorChn = (double *)info_pChn_colorChn->data;
			OUT("info.pChn.colorChn");
			OUT(*colorChn);
			matvar_t* info_pChn_normRad = Mat_VarGetStructFieldByName(info_pChn,"normRad",0);
			double * normRad = (double *)info_pChn_normRad->data;
			OUT("info.pChn.normRad");
			OUT(*normRad);
			matvar_t* info_pChn_normConst = Mat_VarGetStructFieldByName(info_pChn,"normConst",0);
			double * normConst = (double *)info_pChn_normConst->data;
			OUT("info.pChn.normConst");
			OUT(*normConst);
			matvar_t* info_pChn_full = Mat_VarGetStructFieldByName(info_pChn,"full",0);
			double * full = (double *)info_pChn_full->data;
			OUT("info.pChn.full");
			OUT(*full);


			//gradient histogram channel
			idx = 2;
			info_name = Mat_VarGetStructFieldByName(info,"name",idx);
			char* gradName = (char*) info_name->data;
			OUT("info.name");
			OUT(gradName);
			info_pChn = Mat_VarGetStructFieldByName(info,"pChn",idx);
			info_pChn_enabled = Mat_VarGetStructFieldByName(info_pChn,"enabled",0);
			double * gradEnabled = (double *)info_pChn_enabled->data;
			OUT("info.pChn.enabled");
			OUT(*gradEnabled);
//			matvar_t* info_pChn_binSize = Mat_VarGetStructFieldByName(info_pChn,"binSize",0);
//			double * binSize = (double *)info_pChn_binSize->data;
//			OUT("info.pChn.binSize");
//			OUT(*binSize);
			matvar_t* info_pChn_nOrients = Mat_VarGetStructFieldByName(info_pChn,"nOrients",0);
			double * nOrients = (double *)info_pChn_nOrients->data;
			OUT("info.pChn.nOrients");
			OUT(*nOrients);
			matvar_t* info_pChn_softBin = Mat_VarGetStructFieldByName(info_pChn,"softBin",0);
			double * softBin = (double *)info_pChn_softBin->data;
			OUT("info.pChn.softBin");
			OUT(*softBin);
			matvar_t* info_pChn_useHog = Mat_VarGetStructFieldByName(info_pChn,"useHog",0);
			double * useHog = (double *)info_pChn_useHog->data;
			OUT("info.pChn.useHog");
			OUT(*useHog);
			matvar_t* info_pChn_clipHog = Mat_VarGetStructFieldByName(info_pChn,"clipHog",0);
			double * clipHog = (double *)info_pChn_clipHog->data;
			OUT("info.pChn.clipHog");
			OUT(*clipHog);
		}//end info

		Mat_VarFree(matvar);
	}
	else{
		printf("detector content is null\n");
	}
	Mat_Close(matfp);
}

#if NOW_TESTING == TEST_IO

int main( int argc, char** argv ){
	//image with multi channels
	unsigned char cData[24] = {'a','a','a','a','a','a','b','b','b','b','b','b',
			'c','c','c','c','c','c','d','d','d','d','d','d'};
	void * data = &cData;
    Mat image(2, 2, CV_8UC(6), data);
    OUT("init image");
	cout << image << endl;

//	testReadShowImage();
//	testMatRead(argv[1]);
}

#endif
