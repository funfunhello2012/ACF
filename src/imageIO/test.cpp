/*
 * test.cpp
 *
 *  Created on: 2015年11月3日
 *      Author: edison
 */
#include "imageInOut.h"

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
