/*
 * ParamPyramid.h
 *
 *  Created on: 2015年11月25日
 *      Author: edison
 */

#ifndef SRC_FEATURES_PARAMS_H_
#define SRC_FEATURES_PARAMS_H_

class ParamPyramid{
private:
	int perOct;
	int nOctUp;
	int nApprox;
	std::vector<float> lambdas;
	cv::Size pad;
	cv::Size minDs;
	bool smooth;
	bool concat;
	bool complete;
	int shrink;
};

class ParamChns{
public:
	virtual ~ParamChns(){}
};

class ParamChnsColor:public ParamChns{

};

class ParamChnsGrad:public ParamChns{

};

class ParamChnsMag:public ParamChns{

};



#endif /* SRC_FEATURES_PARAMS_H_ */
