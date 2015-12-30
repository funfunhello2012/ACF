/*
 * convConst.hpp
 *
 *  Created on: 2015年12月30日
 *      Author: edison
 */

#ifndef SRC_FEATURES_CHNSCOMPUTE_MEX_CONVCONST_HPP_
#define SRC_FEATURES_CHNSCOMPUTE_MEX_CONVCONST_HPP_

/*******************************************************************************
* Piotr's Computer Vision Matlab Toolbox      Version 3.24
* Copyright 2014 Piotr Dollar & Ron Appel.  [pdollar-at-gmail.com]
* Licensed under the Simplified BSD License [see external/bsd.txt]
*******************************************************************************/


// convolve one column of I by a 2rx1 ones filter
void convBoxY( float *I, float *O, int h, int r, int s );

// convolve I by a 2r+1 x 2r+1 ones filter (uses SSE)
void convBox( float *I, float *O, int h, int w, int d, int r, int s );

// convolve one column of I by a [1; 1] filter (uses SSE)
void conv11Y( float *I, float *O, int h, int side, int s );

// convolve I by a [1 1; 1 1] filter (uses SSE)
void conv11( float *I, float *O, int h, int w, int d, int side, int s );

// convolve one column of I by a 2rx1 triangle filter
void convTriY( float *I, float *O, int h, int r, int s );

// convolve I by a 2rx1 triangle filter (uses SSE)
void convTri( float *I, float *O, int h, int w, int d, int r, int s );

// convolve one column of I by a [1 p 1] filter (uses SSE)
void convTri1Y( float *I, float *O, int h, float p, int s );

// convolve I by a [1 p 1] filter (uses SSE)
void convTri1( float *I, float *O, int h, int w, int d, float p, int s );

// convolve one column of I by a 2rx1 max filter
void convMaxY( float *I, float *O, float *T, int h, int r );

// convolve I by a 2rx1 max filter
void convMax( float *I, float *O, int h, int w, int d, int r );

#endif /* SRC_FEATURES_CHNSCOMPUTE_MEX_CONVCONST_HPP_ */
