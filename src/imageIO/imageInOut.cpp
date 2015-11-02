/*
 * imageInOut.cpp
 *
 *  Created on: 2015年10月28日
 *      Author: edison
 *      read ,write and show  image like matlab format
 */

#include <cv.h>
#include <highgui.h>

namespace acf{

using namespace std;
using cv::Mat;

Mat imread(char* filename){
	Mat image;
	image = cv::imread(filename,1);
	return image;
}

void imwrite(const string& filename,Mat image){
	cv::imwrite(filename,image);
}

void imshow(Mat image,const string  windowName="figure"){
	cv::namedWindow(windowName,CV_WINDOW_AUTOSIZE);
	cv::imshow(windowName,image);
	cv::waitKey(0);
}

}


int main( int argc, char** argv ){
	cv::Mat image;
	image = acf::imread( argv[1] );
	acf::imshow(image);
	acf::imwrite("test.jpg",image);
	return 0;
}
