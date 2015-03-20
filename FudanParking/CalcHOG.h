#ifndef CalcHOG_H
#define CalcHOG_H

#include "stdafx.h"
#include "MqImageTL.h"
#include <cv.h>
#include <cvaux.h>
#include <highgui.h>
#include <math.h>

#define CELL_X			16
#define CELL_Y			18
#define ANGLE_BIN		9

/**
 * HOG(Histograms of Oriented Gradients)特征计算算法类.
 * CalcFeature是算法主函数，需要输入一张灰度图，然后计算HOG特征值.
 */
class CCalcHOG  
{
public:
    /** 
    * @brief 计算图像的HOG特征，仅支持单通道图像
    * 
    * @param[in] imgSrc 输入图像，单通道
    * @param[out] feature 输出的特征
    * @param[in] ntotalBW HOG特征的水平block数量
    * @param[in] ntotalBH HOG特征的垂直block数量
    * 
    * @return 特征的维度
    */
	int CalcFeature(IplImage *imgSrc, double *feature, int ntotalBW, int ntotalBH);

private:
	void CalcGradient(IplImage *imgSrc, IplImage *magnitude, IplImage *angle);

private:
	double m_hist3d[CELL_Y+2][CELL_X+2][ANGLE_BIN+2];
};
#endif
