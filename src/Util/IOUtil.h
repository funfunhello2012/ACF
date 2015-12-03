/*
 * IOUtil.h
 *
 *  Created on: 2015年11月3日
 *      Author: edison
 */

#ifndef SRC_UTIL_IOUTIL_H_
#define SRC_UTIL_IOUTIL_H_

#include "common.h"
#include <stdexcept>


using std::string;
using std::invalid_argument;
using cv::Mat;

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


}



#endif /* SRC_UTIL_IOUTIL_H_ */
