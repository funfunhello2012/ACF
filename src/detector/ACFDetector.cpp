/*
 * ACFDetector.cpp
 *
 *  Created on: 2015年11月9日
 *      Author: edison
 */


#include "ACFDetector.h"


using namespace acf;
using namespace std;
using cv::Size;
using cv::Mat;



ACFDetector::ACFDetector(ACFDetector::Builder* builder) {
	this->_builder = builder;
	OUT("ACFDetector(Builder*)");
	this->_gtDir = builder->_gtDir;
	this->_modelDs = builder->_modelDs;
	this->_modelDsPad = builder->_modelDsPad;
	this->_name = builder->_name;
	this->_negImgDir = builder->_negImgDir;
	this->_negWinDir = builder->_negWinDir;
	this->_posImgDir = builder->_posImgDir;
	this->_posWinDir = builder->_posWinDir;
	this->_stride = builder->_stride;
	this->_shrink = builder->_shrink;
	this->_cascThr = builder->_cascThr;
	this->_chnsManager = builder->_chnsManager;
	this->_clf = builder->_clf;
	this->_pyramid = builder->_pyramid;
}

ACFDetector::	~ACFDetector(){
	if(this->_clf!=NULL){
		delete[] this->_clf->child;
		delete[] this->_clf->fids;
		delete[] this->_clf->hs;
		delete[] this->_clf->thrs;
		delete this->_clf;
	}
	delete this->_pyramid;
	delete this->_builder;
	OUT("~ACFDetector()");
}

/**
 * Detector is init with its' builder
 */
ACFDetector::Builder::Builder(const string name,const string posDir,const string gtDir){
	OUT("Builder(string,string,string)");
	this->_name = name;
	this->_posImgDir = posDir;
	this->_gtDir = gtDir;
	this->_chnsManager = new ChnsManager();
	this->_pyramid = new Pyramid(this->_chnsManager);
}

ACFDetector::Builder::~Builder(){
	OUT("~Builder() ");
}

//ostream& acf::operator<< (ostream& os,const acf::ACFDetector::Builder& b){
//	cout<< "Builder<<";
//	return os;
//}

std::ostream& acf::operator<<(std::ostream&os ,const ACFDetector& d){
	cout<< "ACFDetector{";
	cout << "name:"<<d._name<<',';
	cout << "posDir:"<<d._posImgDir<<',';
	cout << "gtDir:"<<d._gtDir<<',';
	cout << "negDir:"<<d._negImgDir<<',';
	cout << "posWinDir:"<<d._posWinDir<<',';
	cout << "negWinDir:"<<d._negWinDir<<',';
	cout << "stride:"<<d._stride<<',';
	cout << "modelDsPad:"<<d._modelDsPad<<',';
	cout << "modelDs:"<<d._modelDs<<"...}";
	return os;
}

ACFDetector::Builder* ACFDetector::Builder::negImgDir(std::string negDir){
	this->_negImgDir = negDir;
	return this;
}

ACFDetector::Builder* ACFDetector::Builder::posWinDir(std::string posWinDir){
	this->_posWinDir = posWinDir;
	return this;
}

ACFDetector::Builder* ACFDetector::Builder::negWinDir(std::string negWinDir){
	this->_negWinDir = negWinDir;
	return this;
}

ACFDetector::Builder* ACFDetector::Builder::modelDs(Size size){
	this->_modelDs = size;
	return this;
}

ACFDetector::Builder* ACFDetector::Builder::modelDsPad(cv::Size size){
	this->_modelDsPad = size;
	return this;
}

ACFDetector::Builder* ACFDetector::Builder::stride(int s){
	this->_stride = s;
	return this;
}
ACFDetector::Builder* ACFDetector::Builder::shrink(int s){
	this->_shrink = s;
	return this;
}

ACFDetector::Builder* ACFDetector::Builder::cascThr(double t){
	this->_cascThr = t;
	return this;
}

ACFDetector::Builder* ACFDetector::Builder::classifier(Clf* c){
	this->_clf = c;
	return this;
}

Pyramid* ACFDetector::Builder::getPyramid(){
	return this->_pyramid;
}

ChnsManager* ACFDetector::Builder::getChnsManager(){
	return this->_chnsManager;
}
/**
 * Builder constructor to get a object
 */
ACFDetector ACFDetector:: Builder::build(){
	OUT("Build ACF Detector From Builder");
	return ACFDetector(this);
}

inline void getChild( float *chns1, uint32 *cids, uint32 *fids,
  float *thrs, uint32 offset, uint32 &k0, uint32 &k ){
  float ftr = chns1[cids[fids[k]]];
  k = (ftr<thrs[k]) ? 1 : 2;
  k0=k+=k0*2; k+=offset;
}

/**
 * detect one scale boundbox
 * @param chns : all channel feature were hold in one array chns and were stored in column first order like [R...RG...GB...BM...MG1...G1...]
 * @param bbs :  return the bounding box detected in current scale
 * @param rows :  height of one channel feature
 * @param cols : width of one channel feature
 * @param nC : total number of channel feature map in chns
 */
void ACFDetector::detectOneScale(std::vector<BoundingBox>& bbs,float* chns,int rows,int cols,int nC){
	OUT("Detect One Scale");
	//  // get inputs
	int shrink = this->_shrink;
	const int modelHt = this->_modelDsPad.height;
	const int modelWd = this->_modelDsPad.width;
	const int stride = this->_stride;
	const float cascThr = this->_cascThr;

	// extract relevant fields from trees
	float *thrs =  this->_clf->thrs;
	float *hs =  this->_clf->hs;
	uint32 *fids = this->_clf->fids;
	uint32 *child = this->_clf->child;
	const int treeDepth = this->_clf->treeDepth;
	const int nTreeNodes = (int) this->_clf->nTreeNodes;
	const int nTrees = (int) this->_clf->nTrees;

//	float *chns;//= chnImgs.data();// = (float*) mxGetData(prhs[0]);
	const int height = rows;
	const int width = cols;

	// get dimensions and constants
	const int nChns = nC;

	const int height1 = (int) ceil(float(height*shrink-modelHt+1)/stride);
	const int width1 = (int) ceil(float(width*shrink-modelWd+1)/stride);

	// construct cids array
	int nFtrs = modelHt/shrink*modelWd/shrink*nChns;
	uint32 *cids = new uint32[nFtrs]; int m=0;
	for( int z=0; z<nChns; z++ )
		for( int c=0; c<modelWd/shrink; c++ )
			for( int r=0; r<modelHt/shrink; r++ )
				cids[m++] = z*width*height + c*height + r;

	// apply classifier to each patch
	vector<int> rs, cs; vector<float> hs1;
	for( int c=0; c<width1; c++ )
		for( int r=0; r<height1; r++ ) {
			float h=0, *chns1=chns+(r*stride/shrink) + (c*stride/shrink)*height;
			if( treeDepth==1 ) {
				// specialized case for treeDepth==1
					for( int t = 0; t < nTrees; t++ ) {
						uint32 offset=t*nTreeNodes, k=offset, k0=0;
						getChild(chns1,cids,fids,thrs,offset,k0,k);
						h += hs[k]; if( h<=cascThr ) break;
					}
				} else if( treeDepth==2 ) {
					// specialized case for treeDepth==2
					for( int t = 0; t < nTrees; t++ ) {
						uint32 offset=t*nTreeNodes, k=offset, k0=0;
						getChild(chns1,cids,fids,thrs,offset,k0,k);
						getChild(chns1,cids,fids,thrs,offset,k0,k);
						h += hs[k]; if( h<=cascThr ) break;
					}
				} else if( treeDepth>2) {
					// specialized case for treeDepth>2
					for( int t = 0; t < nTrees; t++ ) {
						uint32 offset=t*nTreeNodes, k=offset, k0=0;
						for( int i=0; i<treeDepth; i++ )
							getChild(chns1,cids,fids,thrs,offset,k0,k);
							h += hs[k]; if( h<=cascThr ) break;
						}
				} else {
					// general case (variable tree depth)
					for( int t = 0; t < nTrees; t++ ) {
						uint32 offset=t*nTreeNodes, k=offset, k0=k;
						while( child[k] ) {
							float ftr = chns1[cids[fids[k]]];
							k = (ftr<thrs[k]) ? 1 : 0;
							k0 = k = child[k0]-k+offset;
						}
						h += hs[k]; if( h<=cascThr ) break;
					}
				}
				if(h>cascThr) { cs.push_back(c); rs.push_back(r); hs1.push_back(h); }
		}
	delete [] cids;

	int nBB=cs.size();
	// convert to bbs
	for( int i=0; i<nBB; i++ ) {
		BoundingBox bb(cs[i]*stride,rs[i]*stride,modelWd,modelHt,hs1[i]);
		bbs.push_back(bb);
//		bbs[i+0*m]=cs[i]*stride;
//		bbs[i+2*m]=modelWd;
//		bbs[i+1*m]=rs[i]*stride;
//		bbs[i+3*m]=modelHt;
//		bbs[i+4*m]=hs1[i];
	}
}

void ACFDetector::detectImg(std::vector<BoundingBox>& bbs,cv::Mat image){
	OUT("detect image");
	Pyramid* pyramid = this->getPyramid();
	vector<vector<float*> > datas;
	vector<vector<cv::Vec3i>> scaleSizes;
	pyramid->computeData(image,datas,scaleSizes);
	OUT_V(datas.size());
	for(int i=0;i<datas.size();i++){
		OUT("Detect one scale");
		vector<BoundingBox> currentScales;
		vector<float*> currentData = datas[i];
		vector<cv::Vec3i> currentChn = scaleSizes[i];
		float* chnsInOne = (float*)currentData[0]; // copy the scale data into a float*

		for(int j=0;j<currentData.size();j++){//free the memory here
			OUT_V(currentChn[j]);
			delete[] currentData[j]; //change the malloc to new
		}
//		detectOneScale(currentScales,)
	}
}


void ACFDetector::train(){
	OUT("train a detector here ");
}

void ACFDetector::test(){
	OUT("test module here");
}
