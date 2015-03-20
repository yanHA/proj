/*
 * Copyright (C) 2012, Freative, Corporation.
 * All Rights Reserved.
 * Version: V1.0
 * Owner: mqfcu7
 * Data: 2012-12-03
 */

#ifndef MqImageTL_H
#define MqImageTL_H

#include <afx.h>
#include <cv.h>
#include <cvaux.h>
#include <highgui.h>
#include <vector>

#ifndef MAX_FILE
#define MAX_FILE	256
#endif

#ifndef max
#define max(x, y)	((x) > (y) ? (x) : (y))
#endif

#ifndef min
#define min(x, y)	((x) < (y) ? (x) : (y))
#endif

/**
 * ����ֱ�߽ṹ��.
 * ע�⣬�ýṹ����п��ܻᱻ��Ŀⶨ��.
 */
struct LINE{
	int x1;		/**< �˵�1��x���� */
	int y1;		/**< �˵�1��y���� */
	int x2;		/**< �˵�2��x���� */
	int y2;		/**< �˵�2��y���� */
};

/**
 * mqfcu7�Ĺ�����.
 * ����ֻ��һ��������.
 */
class CMqImageTL
{
public:
	/**
	 * ��txt�ж���ͼ�����ݣ�һ�����ڲ���
	 * @param[in] path txt�ļ�·��
	 * @param[in] imgDst ֧��uchar��float�ĵ�ͨ��ͼ��
	 */
	static void ReadImage(char *path, IplImage *imgDst);

	/**
	 * ��ͼ�����������txt�ļ���һ�����ڲ���
	 * @param[in] path txt�ļ�·��
	 * @param[in] imgSrc ֧��uchar��float�ĵ�ͨ��ͼ��
	 */
	static void PrintImage(char *path, IplImage *imgSrc);

	/**
	 * ����ֱ�ߵ���Ӿ���
	 * @param[in] l ֱ��
	 * @return ����
	 */
	static CvRect GetLineHull(LINE l);

	/**
	 * �ж���ֱ���Ƿ��ཻ
	 * @param[in] l1 ֱ��1
	 * @param[in] l2 ֱ��2
	 * @return �Ƿ��ཻ
	 */
	static bool LineIntersect(LINE l1, LINE l2);

	/**
	 * �ж�ֱ���Ƿ��ڵ�����
	 * @param[in] line ֱ��
	 * @param[in] pt ��
	 * @return ֱ���Ƿ��ڵ�����
	 */
	static bool LineLeftPoint(LINE line, CvPoint pt);

	/**
	 * ��ȡ��ǰʱ��
	 * @param[out] strTime ʱ�䣬��201207281111064
	 * @param[in] addMS �����ƫ�ƣ�����Ϊ����
	 */
	static void GetCurTime(char *strTime, int addMS = 0);

	/**
	 * ��ͼ���л�����
	 * @param[in] imgSrc ͼ��
	 * @param[in] r ����
	 * @param[in] color ��ɫ
	 * @param[in] thickness ��������
	 */
	static void DrawRectangle(IplImage *imgSrc, CvRect r, CvScalar color, int thickness = 1);

	/**
	 * floatͼ��ת����ucharͼ��
	 * @param[in] imgSrc float�ĵ�ͨ��ͼ��
	 * @param[in] imgDst uchar�ĵ�ͨ��ͼ��
	 */
	static void FloatImage2UChar(IplImage *imgSrc, IplImage *imgDst);

    /** 
    * ͼ�����������䵽data�У�ֻ֧��uchar��ͨ��ͼ��
    * @param[in] imgSrc Դͼ��
    * @param[in] data Ŀ�ĵ�
    */
    static void Image2Array(IplImage *imgSrc, void *data);

	/**
	 * �ü�����
	 * @param[in] rect ����
	 * @param[in] sz �߽��С
	 * @return �Ƿ�Խ��
	 */
	static bool RectangleCut(CvRect &rect, CvSize sz);

	/**
	 * �����������ε��ص��� = (a n b) / (a u b)
	 * @param[in] b1 ����1
	 * @param[in] b2 ����2
	 * @return �ص���
	 */
	static double CalcOverlapRate(CvRect b1, CvRect b2);

	/**
	 * ��ȡregion�����ͼ��ͷ�����ص��ڴ���Ҫ���ⲿ�ͷ�(cvReleaseImageHeader)
	 * @param[in] imgSrc ͼ��
	 * @param[in] region ����
	 * @return ͼ��ͷ
	 */
	static IplImage* GetSubHeader(IplImage *imgSrc, CvRect region);

	/**
	 * ��ȡregion�����ͼ�񣬷��ص��ڴ���Ҫ�ⲿ�ͷ�(cvReleaseImage)
	 * @param[in] imgSrc ͼ��
	 * @param[in] region ����
	 * @return ͼ��
	 */
	static IplImage* CopySubImage(IplImage *imgSrc, CvRect region);

	/**
	 * ��������
	 * @param[in] rect ����
	 * @param[in] scale ���ű���
	 * @return ���ź�ľ���
	 */
	static CvRect RectResize(CvRect rect, double scale);

	/**
	 * ��תͼ�񣬷��ص��ڴ���Ҫ�ⲿ�ͷ�(cvReleaseImage)
	 * @param[in] img ͼ��
	 * @param[in] degree ��ת�Ƕ�
	 * @return ��ת���ͼ�񣬴�С������ԭͼ��һ��
	 */
	static IplImage* RotateImage(IplImage* img, double degree);
	
    /**
     * ��ȡ�ļ���������ͼƬ�ļ���·�����ݹ飩��֧��JPG��JPEG��BMP��PNG
     * @param[in] srcPath �ļ���·��
     * @param[out] files ����ͼƬ�ļ�·��
     */
	static void GetImageFiles(CString srcPath, std::vector<CString> &files);

    /** 
    * ��ȡ�ļ�����������Ƶ�ļ���·�����ݹ飩��֧��AVI��MP4
    * @param[in] srcPath �ļ���·��
    * @param[out] files ������Ƶ�ļ�·��
    */
    static void GetVideoFiles(CString srcPath, std::vector<CString> &files);
};

#endif
