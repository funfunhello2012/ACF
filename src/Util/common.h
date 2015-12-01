#pragma once

#include<iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

using namespace cv;
using  namespace std;

#define TESTING
//#undef TESTING

#ifdef TESTING
void test_channel(void);
#define OUT(x)  do{ cout << x << endl;}while(0)

#else
#define OUT(x)
#endif
