#include "Channel.h"

void test_channel(void) {
	  Mat image, image2;
	  image = imread( "lena.jpg" );

	  ColorChn colorChn(image);
	  colorChn.compute();
	 image2 =  colorChn.data();

	  namedWindow( "Original Image", CV_WINDOW_AUTOSIZE );
	  imshow( "Original Image", image );

	  namedWindow( "Color Channel", CV_WINDOW_AUTOSIZE );
	  imshow( "Color Channel", image2 );
}
