
#pragma once
// 这里提供了积分通道图的三种特征，可以通过继承抽象类Chn 添加自定义通道

#include "../../Util/common.h"

/**
 * abstract base class
 * You can extended Chn and re-implement the virtual compute method
 * then the feature in you defined can be used in ACF detect framework
 */
class Chn {
public:
	void setEnabled(bool e){
		enabled = e;
	}

	void setShrink(int s){
		shrink = s;
	}

	/**
	 *	@param numChn : the number of channel image for this channel
	 */
	Chn(int numChn): enabled(true), shrink(2), pad(0), numChns(numChn), padType(NONE){}

	/**
	 * @param image : pointer to the image data in column first order
	 * @param dims : a Vec3i hold the image (height,width,channels)
	 */
	virtual void compute(float * const image,const cv::Vec3i dims) = 0;
	virtual int getChnNum()=0;
	virtual  ~Chn() {}
	float* data(){
		return chnData;
	}
private:


protected:
	bool 	enabled;
	char	name[20]; // 注意，通道名称不能超过20个字符
	
	int shrink;
	// padWith
	int		pad;	 // pad value
	int numChns;
	typedef enum{NONE,REPLICATE,SYMMETRIC,CIRCULAR} padType_e;
	padType_e padType;
	float* chnData; // 输入时拷贝到类内部，在内部进行处理  // 需要修改为引用外部，该类只负责提供计算方法
};

class ColorChn : public Chn { // 颜色通道，三个分量
public:
	ColorChn(int colorSpace = CV_BGR2Luv, int smooth = 1) :
		Chn(3), colorSpace(colorSpace), smooth(smooth){
			strcpy(name,  "color channels");
			padType = REPLICATE;
	}
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// %   .pColor       - parameters for color space:
	// %     .enabled      - [1] if true enable color channels
	// %     .smooth       - [1] radius for image smoothing (using convTri)
	// %     .colorSpace   - ['luv'] choices are: 'gray', 'rgb', 'hsv', 'orig'
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//	ColorChn(Mat img, int colorSpace = CV_BGR2Luv, int smooth = 1) :
//		Chn(img), colorSpace(colorSpace), smooth(smooth){
//			strcpy(name,  "color channels");
//			padType = REPLICATE;
//	}
	void compute(float * const image,const cv::Vec3i dims);
	int getChnNum(){return numChns;}
private:
	int colorSpace;
	int smooth;
};


class GradHistChn : public Chn { // 颜色通道，三个分量
public:
	GradHistChn(int _nOrients = 6) :
		Chn(nOrients), binSize(8), nOrients(_nOrients),softBin(0), clipHog(.2),useHog(false){
			strcpy(name,  "Gradient Histogram Channels");
			padType = REPLICATE;
	}
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// %   .pGradHist    - parameters for gradient histograms:
	// %     .enabled      - [1] if true enable gradient histogram channels
	// %     .binSize      - [shrink] spatial bin size (defaults to shrink)
	// %     .nOrients     - [6] number of orientation channels
	// %     .softBin      - [0] if true use "soft" bilinear spatial binning
	// %     .useHog       - [0] if true perform 4-way hog normalization/clipping
	// %     .clipHog      - [.2] value at which to clip hog histogram bins
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	GradHistChn(int binS,int nO,bool softB,bool useH,double cH) :
		Chn(nO), binSize(binS),nOrients(nO),softBin(softB),clipHog(cH),useHog(useH){
			strcpy(name,  "gradient histogram");
	}
//	GradHistChn(Mat img, int _nOrients = 6) :
//		Chn(img), binSize(8), nOrients(_nOrients),softBin(0), clipHog(.2){
//			strcpy(name,  "Gradient Histogram Channels");
//			padType = REPLICATE;
//	}

	void compute(float * const image,const cv::Vec3i dims);
	int getChnNum(){return numChns;}
private: // settings
	int binSize;
	unsigned int nOrients;
	bool softBin;
	float clipHog;
	bool useHog;
};

class ChnsManager{
private:
	std::vector<Chn*> chns;
	std::vector<cv::Vec3i> chnSize;
public:
	ChnsManager(){};
	void addChn(Chn* ch){
		OUT("add channel");
		chns.push_back(ch);
	}

	int getNTypes(){
		return chns.size();
	}

	/**
	 * return the chnType sizes
	 */
	std::vector<cv::Vec3i> getChnSize(){
		return chnSize;
	}

	void compute(std::vector<float*>& chnDatas,float* image,const cv::Vec3i dims);
};

class MagChn : public Chn { // 颜色通道，三个分量
public:
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	//	%   .pGradMag     - parameters for gradient magnitude:
	//	%     .enabled      - [1] if true enable gradient magnitude channel
	//	%     .colorChn     - [0] if>0 color channel to use for grad computation
	//	%     .normRad      - [5] normalization radius for gradient
	//	%     .normConst    - [.005] normalization constant for gradient
	//	%     .full         - [0] if true compute angles in [0,2*pi) else in [0,pi)
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	MagChn(bool colorUsed,int normR,double normC,bool f) :
		Chn(1), colorChnUsed(colorUsed),normRad(normR),normConst(normC),full(f){
			strcpy(name,  "gradient magnitude");
	}
	void compute(float * const image,const cv::Vec3i dims);
	int getChnNum(){return numChns;}
private:
	bool colorChnUsed;
	int normRad;
	double normConst;
	bool full;
};

