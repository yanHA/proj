// QmImageTL.cpp: implementation of the CQmImageTL class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MqImageTL.h"

using std::min;
using std::max;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CvRect CMqImageTL::RectResize(CvRect rect, double scale)
{
	rect.x		= int(rect.x * scale);
	rect.y		= int(rect.y * scale);
	rect.width	= int(rect.width * scale);
	rect.height = int(rect.height * scale);

	return rect;
}

IplImage* CMqImageTL::CopySubImage(IplImage *imgSrc, CvRect region)
{
	IplImage *header = GetSubHeader(imgSrc, region);
	IplImage *patch = cvCloneImage(header);
	cvReleaseImageHeader(&header);

	return patch;
}

IplImage* CMqImageTL::GetSubHeader(IplImage *imgSrc, CvRect region)
{
	CvMat subMat;
	IplImage *header = cvCreateImageHeader(cvSize(region.width, region.height), 
		imgSrc->depth, imgSrc->nChannels);
	cvGetSubRect(imgSrc, &subMat, region);
	header = cvGetImage(&subMat, header);

	return header;
}

double CMqImageTL::CalcOverlapRate(CvRect b1, CvRect b2)
{
	double bb1[4] = {b1.x, b1.y, b1.x + b1.width, b1.y + b1.height};
	double bb2[4] = {b2.x, b2.y, b2.x + b2.width, b2.y + b2.height};

	if(bb1[0] > bb2[2] || bb1[1] > bb2[3] || bb1[2] < bb2[0] || bb1[3] < bb2[1]) return 0;
	
	double colInt = min(bb1[2], bb2[2]) - max(bb1[0], bb2[0]) + 1;
	double rowInt = min(bb1[3], bb2[3]) - max(bb1[1], bb2[1]) + 1;

	double intersection = colInt * rowInt;
	double area1 = (bb1[2] - bb1[0] + 1) * (bb1[3] - bb1[1] + 1);
	double area2 = (bb2[2] - bb2[0] + 1) * (bb2[3] - bb2[1] + 1);
	
	return intersection / (area1 + area2 - intersection);
}

bool CMqImageTL::RectangleCut(CvRect &rect, CvSize sz)
{
	int x1 = rect.x;
	int y1 = rect.y;
	int x2 = rect.x + rect.width - 1;
	int y2 = rect.y + rect.height - 1;

	rect.x		= max(x1, 0);
	rect.y		= max(y1, 0);
	rect.width	= min(x2, sz.width) - x1 + 1;
	rect.height = min(y2, sz.height) - y1 + 1;

	return true;
}

void CMqImageTL::DrawRectangle(IplImage *imgSrc, CvRect r, CvScalar color, int thickness)
{
	cvRectangle(imgSrc, cvPoint(r.x, r.y), cvPoint(r.x + r.width, r.y + r.height), color, thickness);
}

void CMqImageTL::GetCurTime(char *strTime, int addMS)
{
    assert(addMS >= 0);
	SYSTEMTIME sys;
	GetLocalTime(&sys);
	sprintf(
		strTime, 
		"%04d%02d%02d%02d%02d%02d%03d", 
		sys.wYear, 
		sys.wMonth, 
		sys.wDay, 
		sys.wHour, 
		sys.wMinute, 
		sys.wSecond, 
		min(sys.wMilliseconds + addMS, 999)
	);
}

bool CMqImageTL::LineIntersect(LINE l1, LINE l2)
{
	// Box test
	CvRect b1 = GetLineHull(l1);
	CvRect b2 = GetLineHull(l2);
	if(b1.x > b2.width || b1.y > b2.height || b1.width < b2.x || b1.height < b2.y) return false;

	int flag = 0;

	CvPoint p1 = cvPoint(l2.x1 - l1.x1, l2.y1 - l1.y1);
	CvPoint p2 = cvPoint(l2.x2 - l1.x1, l2.y2 - l1.y1);
	CvPoint p3 = cvPoint(l1.x2 - l1.x1, l1.y2 - l1.y1);

	int v1 = p1.x * p3.y - p1.y * p3.x;
	int v2 = p2.x * p3.y - p2.y * p3.x;

	if((v1 >= 0 && v2 <= 0) || (v1 <= 0 && v2 >= 0)) flag ++;

	p1 = cvPoint(l1.x1 - l2.x1, l1.y1 - l2.y1);
	p2 = cvPoint(l1.x2 - l2.x1, l1.y2 - l2.y1);
	p3 = cvPoint(l2.x2 - l2.x1, l2.y2 - l2.y1);

	v1 = p1.x * p3.y - p1.y * p3.x;
	v2 = p2.x * p3.y - p2.y * p3.x;

	if((v1 >= 0 && v2 <= 0) || (v1 <= 0 && v2 >= 0)) flag ++;

	if(flag == 2) return true;

	return false;
}

bool CMqImageTL::LineLeftPoint(LINE line, CvPoint pt)
{
	CvPoint v1	= cvPoint(line.x2 - line.x1, line.y2 - line.y1);
	CvPoint v2	= cvPoint(pt.x - line.x1, pt.y - line.y1);
	int cross	= v1.x * v2.y - v1.y * v2.x;
	return cross > 0;
}

CvRect CMqImageTL::GetLineHull(LINE l)
{
	CvRect b;
	b.x			= min(l.x1, l.x2);
	b.y			= min(l.y1, l.y2);
	b.width		= max(l.x1, l.x2);
	b.height	= max(l.y1, l.y2);

	return b;
}

void CMqImageTL::FloatImage2UChar(IplImage *imgSrc, IplImage *imgDst)
{
	int i, j;

	CvSize imgSz = cvGetSize(imgSrc);

	float maxPix = 0;
	for(i = 0; i < imgSz.height; i ++)
	{
		float *ptr = (float*)(imgSrc->imageData + imgSrc->widthStep * i);
		for(j = 0; j < imgSz.width; j ++)
		{
			maxPix = max(maxPix, ptr[j]);
		}
	}

	for(i = 0; i < imgSz.height; i ++)
	{
		uchar *ptr	= (uchar*)(imgDst->imageData + imgDst->widthStep * i);
		float *ptrS = (float*)(imgSrc->imageData + imgSrc->widthStep * i);
		for(j = 0; j < imgSz.width; j ++)
		{
			ptr[j] = (uchar)(ptrS[j] / maxPix * 255);
		}
	}
}

void CMqImageTL::Image2Array(IplImage *imgSrc, void *data)
{
    int i, j;
#define IMAGE2ARRAY(type){                                                  \
    for(i = 0; i < imgSrc->height; i ++)                                    \
    {                                                                       \
        type *ptr = (type*)(imgSrc->imageData + imgSrc->widthStep * i);     \
        for(j = 0; j < imgSrc->width; j ++)                                 \
        {                                                                   \
            ((type*)data)[i*imgSrc->width+j] = ptr[j];                      \
        }                                                                   \
	}}

	if(imgSrc->depth == IPL_DEPTH_8U) IMAGE2ARRAY(uchar)
	else if(imgSrc->depth == IPL_DEPTH_32F) IMAGE2ARRAY(float)
}

void CMqImageTL::PrintImage(char *path, IplImage *imgSrc)
{
	int i, j;
	FILE *f = fopen(path, "w");

#define IMG_PRINT(type, sss)		{										\
	for(i = 0; i < imgSrc->height; i ++)									\
	{																		\
		type *ptr = (type*)(imgSrc->imageData + imgSrc->widthStep * i);		\
		for(j = 0; j < imgSrc->width; j ++)									\
		{																	\
			fprintf(f, (sss), ptr[j]);										\
		}																	\
		fprintf(f, "\n");													\
	}}

	if(imgSrc->depth == IPL_DEPTH_8U)			IMG_PRINT(uchar, "%d ")
	else if(imgSrc->depth == IPL_DEPTH_32F)		IMG_PRINT(float, "%g ")

	fclose(f);
}

void CMqImageTL::ReadImage(char *path, IplImage *imgDst)
{
	int i, j;
	FILE *f = fopen(path, "r");

#define IMG_READ(type, sss)			{										\
	for(i = 0; i < imgDst->height; i ++)									\
	{																		\
		type *ptr = (type*)(imgDst->imageData + imgDst->widthStep * i);		\
		for(j = 0; j < imgDst->width; j ++)									\
		{																	\
			fscanf(f, (sss), ptr + j);										\
		}																	\
	}}																		\

	if(imgDst->depth == IPL_DEPTH_8U)			IMG_READ(uchar, "%d")
	else if(imgDst->depth == IPL_DEPTH_32F)		IMG_READ(float, "%f")

	fclose(f);
}

IplImage* CMqImageTL::RotateImage(IplImage* img, double degree)
{
	degree = - degree;
	double angle = degree * CV_PI / 180.;
    double a = sin(angle), b = cos(angle);   
    int width = img->width;    
    int height = img->height;    
    int width_rotate= int(height * fabs(a) + width * fabs(b));    
    int height_rotate=int(width * fabs(a) + height * fabs(b));
    float map[6];  
    CvMat map_matrix = cvMat(2, 3, CV_32F, map);
    CvPoint2D32f center = cvPoint2D32f(width / 2, height / 2);    
    cv2DRotationMatrix(center, degree, 1.0, &map_matrix);    
    map[2] += (width_rotate - width) / 2;    
    map[5] += (height_rotate - height) / 2;    
	IplImage* img_rotate = cvCreateImage(cvSize(width_rotate, height_rotate), img->depth, img->nChannels);
    cvWarpAffine( img,img_rotate, &map_matrix, CV_INTER_LINEAR | CV_WARP_FILL_OUTLIERS, cvScalarAll(0));    
    return img_rotate;  
}


void CMqImageTL::SplitPathName(char *path, char *name, char *folder)
{
    assert(path != NULL && name != NULL);

    char *pstr = strrchr(path, '\\');
    if(pstr == NULL) return;

    strcpy(name, pstr + 1);

    if(folder == NULL) return;

    strcpy(folder, path);
    folder[pstr-path] = '\0';
}

void CMqImageTL::GetImageFiles(CString srcPath, std::vector<CString> &files)
{
    assert(srcPath != "");

    std::vector<CString> ext;
    ext.push_back(".jpg");
    ext.push_back(".jpeg");
    ext.push_back(".bmp");
    ext.push_back(".png");

    char path[MAX_PATH];
    sprintf(path, "%s\\*.*", srcPath);
    CFileFind finder;
    BOOL isFinded = finder.FindFile(CString(path));
    while(isFinded)
    {
        isFinded = finder.FindNextFile();
        if(finder.IsDots()) continue;
        if(finder.IsDirectory())        // 文件夹递归
        {
            GetImageFiles(finder.GetFilePath(), files);
            continue;
        }

        // 获取文件的后缀名
        CString name    = finder.GetFileName();
        CString title   = finder.GetFileTitle();
        int extLen      = name.GetLength() - title.GetLength();
        CString ex      = name.Right(extLen);

        // 判别是否为图片文件
        bool flag = false;
        for(int i = 0; i < (int)ext.size(); i ++)
        {
            if(ex.MakeLower() != ext[i]) continue;
            flag = true;
            break;
        }
        if(!flag) continue;

        files.push_back(finder.GetFilePath());
    }
    finder.Close();
}

void CMqImageTL::GetVideoFiles(CString srcPath, std::vector<CString> &files)
{
    assert(srcPath != "");

    std::vector<CString> ext;
    ext.push_back(".avi");
    ext.push_back(".mp4");

    char path[MAX_PATH];
    sprintf(path, "%s\\*.*", srcPath);
    CFileFind finder;
    BOOL isFinded = finder.FindFile(CString(path));
    while(isFinded)
    {
        isFinded = finder.FindNextFile();
        if(finder.IsDots()) continue;
        if(finder.IsDirectory())        // 文件夹递归
        {
            GetVideoFiles(finder.GetFilePath(), files);
            continue;
        }

        // 获取文件的后缀名
        CString name    = finder.GetFileName();
        CString title   = finder.GetFileTitle();
        int extLen      = name.GetLength() - title.GetLength();
        CString ex      = name.Right(extLen);

        // 判别是否为视频文件
        bool flag = false;
        for(int i = 0; i < (int)ext.size(); i ++)
        {
            if(ex.MakeLower() != ext[i]) continue;
            flag = true;
            break;
        }
        if(!flag) continue;

        files.push_back(finder.GetFilePath());
    }
    finder.Close();
}
