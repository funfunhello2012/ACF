
#include "Channel.h"

void ColorChn::compute(void){
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	// % compute color channels
	// p=pChns.pColor; nm='color channels';
	// I=rgbConvert(I,p.colorSpace); I=convTri(I,p.smooth);
	// if(p.enabled), chns=addChn(chns,I,nm,p,'replicate',h,w); end
	// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	cvtColor(img, img, colorSpace);
	// smoothing is not available now.
}
