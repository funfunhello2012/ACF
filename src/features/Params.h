/*
 * ParamPyramid.h
 *
 *  Created on: 2015年11月25日
 *      Author: edison
 */

#ifndef SRC_FEATURES_PARAMS_H_
#define SRC_FEATURES_PARAMS_H_

using std::string;
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

enum ChnsType{
	Color= 1,
	GradHist = 2,
	GradMag = 3,
	Custom = 4
};

class IParamChns{
public:
	virtual ~IParamChns(){}
	virtual ChnsType getChnsType() = 0;
};

class ParamChnsColor:public IParamChns{
public:
	ChnsType getChnsType(){return Color;}
};

class ParamChnsGrad:public IParamChns{
	ChnsType getChnsType(){return GradHist;}
};

class ParamChnsMag:public IParamChns{
	ChnsType getChnsType(){return GradMag;}
};

#endif /* SRC_FEATURES_PARAMS_H_ */
