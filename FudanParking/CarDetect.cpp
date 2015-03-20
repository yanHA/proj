#include "stdafx.h"
#include "CarDetect.h"


using namespace std;

CCarDetect::CCarDetect()
{
	
}

IplImage *CCarDetect::Detection(IplImage *imgSrc, struct svm_model *testmodel, vector<CvRect> carmask)
{
	IplImage *image = CMqImageTL::RotateImage(imgSrc, 45);
	IplImage *gray = cvCreateImage(cvGetSize(image), 8, 1);

	cvCvtColor(image, gray, CV_RGB2GRAY);

	int dimension;
	for (int i = 0; i < (int)carmask.size(); i++)
	{
		IplImage *Header = CMqImageTL::GetSubHeader(gray, carmask[i]);
		dimension = m_calc.CalcFeature(Header, features[i], 4, 2);
		cvReleaseImageHeader(&Header);
	}

	m_testmodel = testmodel;
	struct svm_node *testX = new struct svm_node[dimension+1];

	for (int i = 0; i < (int)carmask.size(); i++)
	{
		for(int j = 0; j < dimension; j++)
		{
			testX[j].index = j+1;
			testX[j].value = features[i][j];
		}

		testX[dimension].index = -1;

		result[i] = svm_predict(m_testmodel, testX);
	}

	for (int i = 0; i < (int)carmask.size(); i++)
	{
		if(result[i] > 0.5)
			CMqImageTL::DrawRectangle(image, carmask[i], cvScalar(255,0,0));
		else
			CMqImageTL::DrawRectangle(image, carmask[i], cvScalar(0,0,255));
	}

	delete[]testX;
	

	//cvReleaseImage(&image);
	cvReleaseImage(&gray);
	return image;
}

CCarDetect::~CCarDetect()
{

}