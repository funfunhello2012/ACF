/*
 * ACFDetector.cpp
 *
 *  Created on: 2015年11月9日
 *      Author: edison
 */

#include "../Util/Builder.h"

namespace acf{

class ACFDetector {
private:
	ACFDetector();
	ACFDetector& operator=(const ACFDetector&);//prevent the compiler to generate copying assignment

public:
	~ACFDetector();
	ACFDetector(const ACFDetector& origin);

	class Builder : public IBuilder<ACFDetector>{
	public:
		Builder();
		~Builder();
		ACFDetector build();
	};
};

}




