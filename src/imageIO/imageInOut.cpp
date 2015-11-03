/*
 * imageInOut.cpp
 *
 *  Created on: 2015年10月28日
 *      Author: edison
 *      read ,write and show  image like matlab format
 */

#include <stdexcept>
#include <cv.h>
#include <highgui.h>

namespace acf{

using std::string;
using std::invalid_argument;
using cv::Mat;

Mat imread(const char* filename){
	Mat image;
	image = cv::imread(filename,CV_LOAD_IMAGE_COLOR);
	if(!image.data){
		throw invalid_argument(string(filename)+" can not  be open or read in!");
	}
	return image;
}

void imwrite(const string& filename,Mat image){
	cv::imwrite(filename,image);
}

void imshow(const Mat image,const string  windowName="figure"){
	cv::namedWindow(windowName,CV_WINDOW_AUTOSIZE);
	cv::imshow(windowName,image);
	cv::waitKey(0);
}

}


int main( int argc, char** argv ){
	try{
		cv::Mat image;
		image = acf::imread( argv[1] );
		acf::imshow(image);
		acf::imwrite("test.jpg",image);
	}
	catch(const std::invalid_argument& ia){
		std::cout << argv[1] << " is not a valid for read!" << std::endl;
	}
	return 0;
}
