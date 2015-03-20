#include "stdafx.h"
#include "CalcHOG.h"

int CCalcHOG::CalcFeature(IplImage *imgSrc, double *feature, int ntotalBW, int ntotalBH)
{
    CV_FUNCNAME("CCalcHOG::CalcFeature");

    int dim = 0;        // 特征维度
	const int nblockW		= 2;
	const int nblockH		= 2;
	const int nthet			= 9;
	const int ncellX        = ntotalBW * nblockW;       // cell在x方向的数量
	const int ncellY        = ntotalBH * nblockH;       // cell在y方向的数量

	const CvSize imgSz = cvGetSize(imgSrc);
	const int m = imgSz.height;
	const int n = imgSz.width;

	// P表示Pix
	const double cellPW	= (double)n / (ntotalBW * nblockW);     // cell的宽度
	const double cellPH	= (double)m / (ntotalBH * nblockH);     // cell的高度
	const int nblockPW	= (int)ceil((double)n / ntotalBW);      // block的宽度
	const int nblockPH	= (int)ceil((double)m / ntotalBH);      // block的高度
	const double angleStep = CV_PI / nthet;

    __BEGIN__;

	CV_ASSERT(imgSrc->nChannels == 1);
    CV_ASSERT(ncellX <= 16 && ncellY <= 18);
	memset(m_hist3d, 0, sizeof(m_hist3d));

	// 计算图像梯度强度和方向
	IplImage *magnitude = cvCreateImage(imgSz, 32, 1);
	IplImage *angle		= cvCreateImage(imgSz, 32, 1);
	CalcGradient(imgSrc, magnitude, angle);
	
#define M_PIX(y, x) ((float*)(magnitude->imageData + magnitude->widthStep * y))[x]
#define A_PIX(y, x) ((float*)(angle->imageData + angle->widthStep * y))[x]

	double z;
	float gs, go;
	int ch, cw, ci, cj, cy, cx, i, j, binZ1, binZ2, fi, fj;

    const int cyMax = (int)ceil(cellPH);
    const int cxMax = (int)ceil(cellPW);
    for(ch = 0; ch < ncellY; ch ++)
    {
        for(cw = 0; cw < ncellX; cw ++)
        {
            ci = (int)floor(cellPH * ch);
            cj = (int)floor(cellPW * cw);
            for(cy = 0; cy < cyMax; cy ++)
            {
                for(cx = 0; cx < cxMax; cx ++)
                {
                    i = ci + cy;
                    j = cj + cx;
                    
					gs = M_PIX(i, j);
					go = A_PIX(i, j);

					if(gs == 0) continue;

					binZ1 = (int)floor((go + angleStep / 2) / angleStep);
					binZ2 = binZ1 + 1;
					z = (go - (binZ1 - 0.5) * angleStep) / angleStep;

                    m_hist3d[ch+1][cw+1][binZ1] += (1 - z) * gs;
                    m_hist3d[ch+1][cw+1][binZ2] += z * gs;
                }
            }
        }
    }
	cvReleaseImage(&magnitude);
	cvReleaseImage(&angle);

	// 将直方图数据填充到特征向量中
	double *ptrf = feature;
	double btlyMax	= m - nblockH * cellPH;
	double btlxMax	= n - nblockW * cellPW;
	int ibin, jbin, kbin;
	for(i = 1; i < ncellY; i += nblockH)
	{
		for(j = 1; j < ncellX; j += nblockW)
		{
			for(ibin = 0; ibin < nblockH; ibin ++)
			{
				for(jbin = 0; jbin < nblockW; jbin ++)
				{
					for(kbin = 1; kbin <= nthet; kbin ++)
					{
						*ptrf ++ = m_hist3d[i+ibin][j+jbin][kbin];
                        dim ++;
					}
				}
			}
		}
	}

   	// 第一范式归一化
	double *pf, sum;
	const double e = 0.001;
	const int fslideStep = nblockW * nblockH * nthet;
	for(fi = 0; fi < dim; fi += fslideStep)
	{
		sum = 0;
		pf = feature + fi;
		for(fj = 0; fj < fslideStep; fj ++) sum += fabs(pf[fj]);
		for(fj = 0; fj < fslideStep; fj ++) feature[fi+fj] = feature[fi+fj] / (sum + e);
	}

    __END__;

    return dim;
}

void CCalcHOG::CalcGradient(IplImage *imgSrc, IplImage *magnitude, IplImage *angle)
{
	CvSize imgSz = cvGetSize(imgSrc);
    IplImage *gradX = cvCreateImage(imgSz, 32, 1);
    IplImage *gradY = cvCreateImage(imgSz, 32, 1);
    cvSobel(imgSrc, gradX, 1, 0, 1);
    cvSobel(imgSrc, gradY, 0, 1, 1);

    for(int i = 0; i < imgSrc->height; i ++)
    {
        float *ptrX = (float*)(gradX->imageData + gradX->widthStep * i);
        float *ptrY = (float*)(gradY->imageData + gradY->widthStep * i);
		float *ptrM	= (float*)(magnitude->imageData + magnitude->widthStep * i);
		float *ptrA	= (float*)(angle->imageData + angle->widthStep * i);
        for(int j = 0; j < imgSrc->width; j ++)
        {
            float dx = ptrX[j];
            float dy = ptrY[j];
			ptrM[j] = (float)sqrt(double(dx * dx + dy * dy));
			ptrA[j] = (float)(atan(dy / (dx + 10e-4)) + CV_PI / 2);
        }
    }

	cvReleaseImage(&gradX);
	cvReleaseImage(&gradY);
}
