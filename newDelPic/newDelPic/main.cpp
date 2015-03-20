/**
 *Copyright(c)2014,Freative
 *
 *�ж�ɾ�������ļ�
 *author yh
 *version 1.0
 *date 2014-08-08
 */

#include <stdio.h>
#include <Windows.h>

#include <vector>
#include <string>
#include <string.h>
#include <algorithm>

#include <opencv2\opencv.hpp>

//��ȡĿ¼�����е�ͼƬ�ļ�·����ͼƬ��ʽΪ .jpg .png .bmp
void GetImagePath(std::string src, std::vector<std::string> &imagePath)
{
	int picCount = 0;
	WIN32_FIND_DATA findFileData;
	HANDLE hFile = NULL;
	std::string tmpPath = src;

	// ��ʽ����ʼ·��
	if(tmpPath.substr((tmpPath.length() - 1), 1) != "\\")
	{
		tmpPath += "\\*.*";
	}
	else
	{
		tmpPath += "*.*";
	}
	
	hFile = FindFirstFile(tmpPath.c_str(), &findFileData);
	
	if(hFile != INVALID_HANDLE_VALUE)
	{
		do
		{
			std::string filename = findFileData.cFileName;
			std::string next = src + "\\" + filename;
			if(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if(filename[0] != '.' && filename[0] != '..')
					GetImagePath(next, imagePath);                      //�ݹ���������ļ���
			}
			else if(filename.find(".jpg") != -1 || filename.find(".bmp") != -1 || filename.find(".png") != -1)
			{
				picCount++;
				imagePath.push_back(next);                              //�����ļ�·����vector��
			}
		}while(FindNextFile(hFile, &findFileData));
	}
	FindClose(hFile);
}

//����ÿ��ͼ���hashֵ������ͼ����8*8��ÿ��ͼ����64λ����������Ϊ����ͼ���ָ��
int ImgHash(char *path, char *status)
{
	int isImage;
	if(path == NULL)
	{
		assert(path != NULL);
		isImage = 2;
		return isImage;
	}

	IplImage *img = cvLoadImage(path);
	if(img == NULL)
	{
		isImage = 0;
		for(int i = 0; i < 64; i ++)
		{
			status[i] = -1;
		}
	}
	else
	{
		isImage = 1;
		IplImage *resize = cvCreateImage(cvSize(8, 8), img->depth, img->nChannels);
		IplImage *gray = cvCreateImage(cvSize(8, 8), 8, 1);
		cvResize(img, resize);
		cvCvtColor(resize, gray, CV_BGR2GRAY);
		int pixCount = 0;
		int k = 0;

		for(int i = 0; i < gray->height; i ++)
		{
			uchar *ptr = (uchar*)(gray->imageData + gray->widthStep * i);
			for(int j = 0; j < gray->width; j ++)
			{
				pixCount += ptr[j];
			}
		}

		int avg = (int)(pixCount / 64);

		for(int i = 0; i < gray->height; i ++)
		{
			uchar *uptr = (uchar*)(gray->imageData + gray->widthStep * i);
			for(int j = 0; j < gray->width; j ++)
			{
				if(uptr[j] < avg)
				{
					status[k] = 0;
					k++;
				}
				else
				{
					status[k] = 1;
					k++;
				}
			}
		}

		cvReleaseImage(&img);
		cvReleaseImage(&resize);
		cvReleaseImage(&gray);
	}

	return isImage;
}

//�Ƚ�����ͼ���ָ�ƣ�����Ƚϵ�ָ�ƣ�64λ���в�ͬ��λ��
int HammingDis(char *sat1, char *sat2)
{
	int count = 0;
	for(int i = 0; i < 64; i ++)
	{
		if(sat1[i] == -1 || sat2[i] == -1)
		{
			count = 65;
			break;
		}
		else if((sat1[i] != -1) && (sat2[i] != -1) && (sat1[i] != sat2[i]))
			count++;
	}

	return count;
}

void Process(std::vector<std::string> &imgPath, std::vector<std::string> &imgBroken)
{
	int preNum = (int)imgPath.size();

	char **status = new char*[preNum];

	//��������ͼ���ָ�Ʋ����棬ͬʱͳ���޷�ʶ���ͼ��
	for(int i = 0; i < preNum; i ++)
	{
		std::string str = imgPath[i];
		status[i] = new char[64];
		memset(status[i], 0, 64*sizeof(char));
		int isImg = ImgHash(const_cast<char *>(str.c_str()), status[i]);
		if(isImg == 0)
		{
			imgBroken.push_back(str);
		}
	}

	//��ÿ��ͼƬ�ȽϺ���������ͼƬ��ָ�ƣ���ָ�Ʋ���ͬ��λ��������5ʱ��Ϊ����ͼƬʱ���Ƶ�ͼƬ��������·������ɾ����vector��
	std::vector<std::string> delPath;
	for(int i = 0; i < preNum; i ++)
	{
		for(int j = i+1; j < preNum; j ++)
		{
			std::string pa = imgPath[i];
			int Num = HammingDis(status[i], status[j]);
			if(Num <= 5)
			{
				delPath.push_back(pa);
			}
		}
	}

	//�Ա����ɾ�����ļ�·����vector(delPath)����ɾ�������ظ���·��
	std::sort(delPath.begin(), delPath.end());
	std::vector<std::string>::iterator iter = unique(delPath.begin(), delPath.end());
	delPath.erase(iter, delPath.end());

	//ɾ������֮�󱣴���delPath�е��ļ�·����Ӧ���ļ�
	for(int i = 0; i < (int)delPath.size(); i ++)
	{
		std::string delpa = delPath[i];
		DeleteFile(delpa.c_str());
	}

	//�ͷ�ǰ����new������
	for(int i = 0; i < preNum; i ++)
	{
		delete []status[i];
	}
	delete []status;
}

int main(int argc, char *argv[])
{
	char inputPath[MAX_PATH] = "";

	for(int i = 1; i < argc; i ++)
	{
		if(std::strcmp(argv[i], "-src") == 0)
		{
			std::strcpy(inputPath, argv[++i]);
		}
	}

	if(std::strcmp(inputPath, "") == 0)
	{
		printf("\n"
			   "Usage: %s"
			   " -src <src path>\n",
			   argv[0]);
		return 0;
	}

	std::vector<std::string> inputImgPath;
	std::vector<std::string> afterImgPath;
	std::vector<std::string> brokenImg;

	time_t begin = GetTickCount();

	printf("*****************************************************************************\n");
	GetImagePath(inputPath, inputImgPath);
	std::reverse(inputImgPath.begin(), inputImgPath.end());
	int prefileNum = (int)inputImgPath.size();
	printf("�ļ�������%d\n", prefileNum);

	printf("��ʼ����ɾ������ͼƬ...\n");
	Process(inputImgPath, brokenImg);
	
	GetImagePath(inputPath, afterImgPath);
	int nowfileNum = (int)afterImgPath.size();
	int delNum = prefileNum - nowfileNum;
	printf("ɾ����ͼƬ����%d\n", delNum);

	time_t end = GetTickCount();
	double totaltime = (double)(end - begin);
	printf("����ʱ��%0.2lfms\n", totaltime);
	printf("ƽ��ÿ��ͼƬ��ʱ��%0.2lfms\n", (double)(totaltime / prefileNum));

	int brokenImgNum = (int)(brokenImg.size());
	printf("�޷�ʶ���ͼ����Ŀ��%d\n", brokenImgNum);

	if(brokenImgNum != 0)
	{
		printf("�޷�ʶ��ͼ��·����");
		for(int i = 0; i < brokenImgNum; i ++)
		{
			if(i == 0)
			{
				printf("%s\n", brokenImg[i].c_str());
			}
			else
			{
				printf("\t\t  %s\n", brokenImg[i].c_str());
			}
		}
	}

	printf("complete!\n");
	printf("*****************************************************************************\n");
	return 0;
}
