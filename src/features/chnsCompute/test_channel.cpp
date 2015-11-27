#include "Channel.h"

#if NOW_TESTING == TEST_CHANNEL

int main( int argc, char** argv )
{
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

#endif
