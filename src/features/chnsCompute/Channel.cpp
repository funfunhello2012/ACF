
#include "Channel.h"

extern void cvtColor2(Mat &II, Mat &JJ, int code);

void ColorChn::compute(void){
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// % compute color channels
	// p=pChns.pColor; nm='color channels';
	// I=rgbConvert(I,p.colorSpace); I=convTri(I,p.smooth);
	// if(p.enabled), chns=addChn(chns,I,nm,p,'replicate',h,w); end
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


	//cvtColor(img, img, colorSpace);
	cvtColor2(img, img,0);
	// smoothing is not available now.
}

void MagChn::compute(void){
	OUT("Computing gradient magnitude");
}

void GradChn::compute(void){
	OUT("Computing gradient histogram");
}
