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
 * 描述直线结构体.
 * 注意，该结构体很有可能会被别的库定义.
 */
struct LINE{
	int x1;		/**< 端点1的x坐标 */
	int y1;		/**< 端点1的y坐标 */
	int x2;		/**< 端点2的x坐标 */
	int y2;		/**< 端点2的y坐标 */
};

/**
 * mqfcu7的工具箱.
 * 这里只是一个函数库.
 */
class CMqImageTL
{
public:
	/**
	 * 从txt中读入图像数据，一般用于测试
	 * @param[in] path txt文件路径
	 * @param[in] imgDst 支持uchar、float的单通道图像
	 */
	static void ReadImage(char *path, IplImage *imgDst);

	/**
	 * 将图像数据输出到txt文件，一般用于测试
	 * @param[in] path txt文件路径
	 * @param[in] imgSrc 支持uchar、float的单通道图像
	 */
	static void PrintImage(char *path, IplImage *imgSrc);

	/**
	 * 计算直线的外接矩形
	 * @param[in] l 直线
	 * @return 矩形
	 */
	static CvRect GetLineHull(LINE l);

	/**
	 * 判断两直线是否相交
	 * @param[in] l1 直线1
	 * @param[in] l2 直线2
	 * @return 是否相交
	 */
	static bool LineIntersect(LINE l1, LINE l2);

	/**
	 * 判断直线是否在点的左边
	 * @param[in] line 直线
	 * @param[in] pt 点
	 * @return 直线是否在点的左边
	 */
	static bool LineLeftPoint(LINE line, CvPoint pt);

	/**
	 * 获取当前时间
	 * @param[out] strTime 时间，如201207281111064
	 * @param[in] addMS 毫秒的偏移，不能为负数
	 */
	static void GetCurTime(char *strTime, int addMS = 0);

	/**
	 * 在图像中画矩形
	 * @param[in] imgSrc 图像
	 * @param[in] r 矩形
	 * @param[in] color 颜色
	 * @param[in] thickness 线条类型
	 */
	static void DrawRectangle(IplImage *imgSrc, CvRect r, CvScalar color, int thickness = 1);

	/**
	 * float图像转化成uchar图像
	 * @param[in] imgSrc float的单通道图像
	 * @param[in] imgDst uchar的单通道图像
	 */
	static void FloatImage2UChar(IplImage *imgSrc, IplImage *imgDst);

    /** 
    * 图像的数据域填充到data中，只支持uchar单通道图像
    * @param[in] imgSrc 源图像
    * @param[in] data 目的地
    */
    static void Image2Array(IplImage *imgSrc, void *data);

	/**
	 * 裁剪矩形
	 * @param[in] rect 矩形
	 * @param[in] sz 边界大小
	 * @return 是否越界
	 */
	static bool RectangleCut(CvRect &rect, CvSize sz);

	/**
	 * 计算两个矩形的重叠率 = (a n b) / (a u b)
	 * @param[in] b1 矩形1
	 * @param[in] b2 矩形2
	 * @return 重叠率
	 */
	static double CalcOverlapRate(CvRect b1, CvRect b2);

	/**
	 * 获取region区域的图像头，返回的内存需要在外部释放(cvReleaseImageHeader)
	 * @param[in] imgSrc 图像
	 * @param[in] region 区域
	 * @return 图像头
	 */
	static IplImage* GetSubHeader(IplImage *imgSrc, CvRect region);

	/**
	 * 获取region区域的图像，返回的内存需要外部释放(cvReleaseImage)
	 * @param[in] imgSrc 图像
	 * @param[in] region 区域
	 * @return 图像
	 */
	static IplImage* CopySubImage(IplImage *imgSrc, CvRect region);

	/**
	 * 矩形缩放
	 * @param[in] rect 矩形
	 * @param[in] scale 缩放比例
	 * @return 缩放后的矩形
	 */
	static CvRect RectResize(CvRect rect, double scale);

	/**
	 * 旋转图像，返回的内存需要外部释放(cvReleaseImage)
	 * @param[in] img 图像
	 * @param[in] degree 旋转角度
	 * @return 旋转后的图像，大小可能与原图不一致
	 */
	static IplImage* RotateImage(IplImage* img, double degree);
	
    /**
     * 获取文件夹下所有图片文件的路径（递归），支持JPG、JPEG、BMP、PNG
     * @param[in] srcPath 文件夹路径
     * @param[out] files 所有图片文件路径
     */
	static void GetImageFiles(CString srcPath, std::vector<CString> &files);

    /** 
    * 获取文件夹下所有视频文件的路径（递归），支持AVI、MP4
    * @param[in] srcPath 文件夹路径
    * @param[out] files 所有视频文件路径
    */
    static void GetVideoFiles(CString srcPath, std::vector<CString> &files);
};

#endif
