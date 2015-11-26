
#pragma once
// 这里提供了积分通道图的三种特征，可以通过继承抽象类Chn 添加自定义通道

#include "common.h"

// abstract base class
class Chn {
public:
	bool 	enabled;
	char	name[20]; // 注意，通道名称不能超过20个字符
	
	Chn(Mat img): enabled(true), pad(0), padType(NONE){
		img.copyTo(this -> img);
	}
	virtual void compute() = 0;
	Mat data(){
		return img;
	}
	
	// padWith
	int		pad;	 // pad value
	typedef enum{NONE,REPLICATE,SYMMETRIC,CIRCULAR} padType_e;
	padType_e padType;

protected:
	Mat img; // 输入时拷贝到类内部，在内部进行处理
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
