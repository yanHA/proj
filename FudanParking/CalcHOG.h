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
 * HOG(Histograms of Oriented Gradients)���������㷨��.
 * CalcFeature���㷨����������Ҫ����һ�ŻҶ�ͼ��Ȼ�����HOG����ֵ.
 */
class CCalcHOG  
{
public:
    /** 
    * @brief ����ͼ���HOG��������֧�ֵ�ͨ��ͼ��
    * 
    * @param[in] imgSrc ����ͼ�񣬵�ͨ��
    * @param[out] feature ���������
    * @param[in] ntotalBW HOG������ˮƽblock����
    * @param[in] ntotalBH HOG�����Ĵ�ֱblock����
    * 
    * @return ������ά��
    */
	int CalcFeature(IplImage *imgSrc, double *feature, int ntotalBW, int ntotalBH);

private:
	void CalcGradient(IplImage *imgSrc, IplImage *magnitude, IplImage *angle);

private:
	double m_hist3d[CELL_Y+2][CELL_X+2][ANGLE_BIN+2];
};
#endif
