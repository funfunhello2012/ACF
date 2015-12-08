/*
 * IODetector.h
 *
 *  Created on: 2015年12月3日
 *      Author: edison
 */

#ifndef SRC_UTIL_IODETECTOR_H_
#define SRC_UTIL_IODETECTOR_H_

#include "common.h"
#include "../detector/ACFDetector.h"
extern "C"{
#include "matio.h"
}

namespace acf{
/*********************************************************
 *  load detector from .mat(MATLAB) file
 *  @param mathPath : .mat filepath
 *  @return : the ACFDetector loaded
 */
ACFDetector loadDetectorFromMat(const string matPath);

/*********************************************************
 *  load detector from .json file
 *  @param jsonPath : detector.json filepath
 *  @return : the ACFDetector loaded
 */
ACFDetector loadDetectorFromJson(const string jsonPath);

/*********************************************************
 *  write detector to  filepath
 *  @param filePath : detector filepath
 *  @return : the ACFDetector loaded
 */
void writeDetectorToJson(const string filePath);

//ACFDetector::Builder* loadBuilderConfig(const string configFile);
}



#endif /* SRC_UTIL_IODETECTOR_H_ */
