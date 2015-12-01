#pragma once

/*******************************************************************************
 * lib
 */
#include<iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>

/*******************************************************************************
 * util
 */
#include "IOUtil.h"

using namespace cv;
using  namespace std;

/*******************************************************************************
 * settings
 */
#define TESTING
//#undef TESTING

/*******************************************************************************
 * conditional compilation
 */
#ifdef TESTING
		// list  test cases, cannot use enum since we need it done when preprocessing the code
		#define  TEST_ALL					1
		#define	TEST_CHANNEL		2
		#define  TEST_PYRAMID		3
		// add your test cases here
		// #define  TEST_XXXXX		  N

		// specify what is testing now
		#define NOW_TESTING	TEST_CHANNEL

		#define OUT(x)  do{ cout << x << endl;}while(0)

#else
		#define OUT(x)
#endif
