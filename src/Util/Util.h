/*
 * Util.h
 *
 *  Created on: 2015年11月25日
 *      Author: edison
 */

#ifndef SRC_UTIL_UTIL_H_
#define SRC_UTIL_UTIL_H_

#include "common.h"

//enum COLORSPACE{
//	YUV,RGB,HSV,GRAY
//};

class BoundingBox{
private:
	cv::Rect_<float> box;
	float score;
public:
	BoundingBox(float x,float y,float width,float height,float score):box(x,y,width,height),score(score){};
	~BoundingBox(){};
};



#endif /* SRC_UTIL_UTIL_H_ */
