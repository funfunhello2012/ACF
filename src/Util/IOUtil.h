/*
 * IOUtil.h
 *
 *  Created on: 2015年11月3日
 *      Author: edison
 */

#ifndef SRC_UTIL_IOUTIL_H_
#define SRC_UTIL_IOUTIL_H_

#include <iostream>
#include <stdexcept>
#include <cv.h>
#include "../detector/ACFDetector.h"

using std::string;
using std::invalid_argument;
using cv::Mat;
using acf::ACFDetector;


namespace acf{

/********************************************************
 * read image like matlab format
 * @param filename : the image path for reading
 * @return : cv::Mat object
 * @throws invalid_argument exception if the input file is not valid
 */
Mat imread(const char* filename) throw(invalid_argument);

/********************************************************
 * write the image to the disk
 * @param filename : the path to store image
 * @param : cv::Mat object for store
 *
 */
void imwrite(const string& filename,Mat image);

/********************************************************
 *  show image like matlab format
 *  @param image : cv::Mat object to show
 *  @param windowName : the name of the window
 */
void imshow(const Mat image,const string  windowName="figure");

/*********************************************************
 *  load detector from .mat(MATLAB) file
 *  @param mathPath : .mat filepath
 *  @return : the ACFDetector loaded
 */
ACFDetector loadDetectorFromMat(const string matPath);

/*********************************************************
 *  load detector from .json file
 *  @param jsonPath : detector.json filepath
 *  @return : the ACFDetector loaded
 */
ACFDetector loadDetectorFromJson(const string jsonPath);

/*********************************************************
 *  write detector to  filepath
 *  @param filePath : detector filepath
 *  @return : the ACFDetector loaded
 */
void writeDetectorToJson(const string filePath);
}



#endif /* SRC_UTIL_IOUTIL_H_ */
