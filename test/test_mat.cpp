/*
 * test_mat.cpp
 *
 *  Created on: 2016年1月4日
 *      Author: edison
 */

#include "../src/Util/Util.h"
#include "../src/Util/common.h"

using namespace acf;
using namespace std;

#if NOW_TESTING == TEST_MAT
int main( int argc, char** argv ){
	MatrixD mat(2,3,2);
	cout << mat;

	MatrixD* m2 = new MatrixD();
	float* data = new float[24];
	m2->setData(data,3,4,2);
	cout << (*m2) << endl;
	delete m2;
}
#endif

