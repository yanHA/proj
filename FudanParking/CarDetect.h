#ifndef CarDetect_H
#define CarDetect_H


#include "stdafx.h"
#include "MqImageTL.h"
#include "CalcHOG.h"
#include "svm.h"

using namespace std;

/************************************************************************/
/* ���������                                                           */
/************************************************************************/


class CCarDetect
{
public:
	CCarDetect();
	~CCarDetect();

	double result[128];
	IplImage *Detection(IplImage *imgSrc, struct svm_model *testmodel, vector<CvRect> carmark);

private:
	CCalcHOG m_calc;
	double features[100][512];
	struct svm_model *m_testmodel;
	
};

#endif