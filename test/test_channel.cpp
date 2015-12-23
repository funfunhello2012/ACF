#include "../src/features/chnsCompute/Channel.h"

using namespace cv;

#if NOW_TESTING == TEST_CHANNEL

int main( int argc, char** argv )
{

	OUT("load image.");


	  Mat image, imageResized, image2,image3;
	  image = acf::imread( "data/I00000.png" ); // test/crop_000001a.png
	  resize( image, imageResized, Size(512,512));  // test/crop_000001a.png

	  OUT_V(image.size()); // image.size():[1060 x 605]

	  OUT("====== TEST COLOR CHANNEL =======");

	  ColorChn colorChn(image);
	  colorChn.compute();
	 image2 =  colorChn.data();

	  namedWindow( "Original Image", CV_WINDOW_AUTOSIZE );
	  imshow( "Original Image", image );

	  namedWindow( "Color Channel", CV_WINDOW_AUTOSIZE );
	  imshow( "Color Channel", image2 );

	  OUT("====== TEST GRAD HIST CHANNEL =======");

	  GradHistChn gradHistChn(imageResized,4); // 4 channel at most
	  gradHistChn.compute();


	  image3 =  gradHistChn.data();

	 namedWindow( "Original Image", CV_WINDOW_AUTOSIZE );
	 imshow( "Original Image", image );

	 namedWindow( "Grad Hist Channel", CV_WINDOW_AUTOSIZE );
	 imshow( "Grad Hist Channel", image3 );

	  waitKey(0);
	  return 0;
}

#endif
