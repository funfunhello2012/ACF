/*
 * Util.h
 *
 *  Created on: 2015年11月25日
 *      Author: edison
 */

#ifndef SRC_UTIL_UTIL_H_
#define SRC_UTIL_UTIL_H_

#include "common.h"

/**
 * Bounding box hold the value of detect bounding box (x,y,width,height,score)
 * (x,y) : the coordinate for the bounding box left top point
 * width : bounding box width
 * height : bounding box height
 * score : confidence value how a bounding box is a specific object
 */
class BoundingBox{
private:
	cv::Rect_<float> box;
	float score;
public:
	BoundingBox(float x,float y,float width,float height,float score):box(x,y,width,height),score(score){};
	~BoundingBox(){};
};

/**
 * convert a OpenCV Mat data to a column first order array,this is needed for calling function in mex file
 * @param image : OpenCV Mat
 * @return : float pointer to the Mat data with column first order
 */
float * matconvert(cv::Mat image);

/**
 * convert column first order array data to a OpenCV Mat object
 * @param ima : the image data
 * @param sz : the image size
 * @param nch : number channel of the image data
 * @return : a OpenCV object hold the data
 */
cv::Mat convertmat(float *ima,cv::Size sz,int nch);


#endif /* SRC_UTIL_UTIL_H_ */
