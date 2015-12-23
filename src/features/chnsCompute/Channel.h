
#pragma once
// 这里提供了积分通道图的三种特征，可以通过继承抽象类Chn 添加自定义通道

#include "../../Util/common.h"

// abstract base class
class Chn {
public:
	void setEnabled(bool e){
		enabled = e;
	}
	Chn(): enabled(true), pad(0), padType(NONE){}
	Chn(Mat img): enabled(true), pad(0), padType(NONE){
		img.copyTo(this -> img);
	}
	virtual void compute() = 0;
	virtual  ~Chn() {}
	Mat data(){
		return img;
	}
private:


protected:
	bool 	enabled;
	char	name[20]; // 注意，通道名称不能超过20个字符
	
	// padWith
	int		pad;	 // pad value
	typedef enum{NONE,REPLICATE,SYMMETRIC,CIRCULAR} padType_e;
	padType_e padType;
	Mat img; // 输入时拷贝到类内部，在内部进行处理  // 需要修改为引用外部，该类只负责提供计算方法
};

class ColorChn : public Chn { // 颜色通道，三个分量
public:
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// %   .pColor       - parameters for color space:
	// %     .enabled      - [1] if true enable color channels
	// %     .smooth       - [1] radius for image smoothing (using convTri)
	// %     .colorSpace   - ['luv'] choices are: 'gray', 'rgb', 'hsv', 'orig'
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	ColorChn(Mat img, int colorSpace = CV_BGR2Luv, int smooth = 1) :
		Chn(img), colorSpace(colorSpace), smooth(smooth){
			strcpy(name,  "color channels");
			padType = REPLICATE;
	}
	void compute();
private:
	int colorSpace;
	int smooth;
};

class GradHistChn : public Chn { // 颜色通道，三个分量
public:
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// %   .pGradHist    - parameters for gradient histograms:
	// %     .enabled      - [1] if true enable gradient histogram channels
	// %     .binSize      - [shrink] spatial bin size (defaults to shrink)
	// %     .nOrients     - [6] number of orientation channels
	// %     .softBin      - [0] if true use "soft" bilinear spatial binning
	// %     .useHog       - [0] if true perform 4-way hog normalization/clipping
	// %     .clipHog      - [.2] value at which to clip hog histogram bins
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	GradHistChn(Mat img, int _nOrients = 6) :
		Chn(img), binSize(8), nOrients(_nOrients),softBin(0), clipHog(.2){
			strcpy(name,  "Gradient Histogram Channels");
			padType = REPLICATE;
	}

	void compute();
private: // settings
	int binSize;
	unsigned int nOrients;
	bool softBin;
	float clipHog;
};

class ChnsManager{

public:
	ChnsManager(){};
	void addChn(Chn* ch){
		OUT("add channel");
	}

	void compute(Mat& chnDatas,Mat image){
		OUT( "compute channle data");
	}
};
