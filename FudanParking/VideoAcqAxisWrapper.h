#ifndef VideoAcqAxisWrapper_H
#define VideoAcqAxisWrapper_H

#include <string>
using namespace std;

#ifdef FrVideoAcqAxis_DLL
#define FrVideoAcqAxis_DLL __declspec(dllimport)
#else
#define FrVideoAcqAxis_DLL __declspec(dllexport)
#endif

/** ��Ƶ�ɼ�ģ�����AxisWrapperר�� */
struct AcqParamAxis
{
    string ipv4;                // ip��ַ
    double frameRate;           // ֡��
    int channel;                // ͨ���ţ���ͨ�������Ϊ0����ͨ��Ӳ��¼���Ϊ>0
	int port;					// �˿ںţ�һ��Ϊ8000
	string user;                // �û���
	string pass;                // ����
	int codec;					// ��������.0:h264
};

/** ��Ƶ�ɼ�axis��װ�� */
class FrVideoAcqAxis_DLL VideoAcqAxisWrapper
{
public:
	VideoAcqAxisWrapper();
	~VideoAcqAxisWrapper();
	bool AxisInit(AcqParamAxis param);
	int AxisStart(void (*inCallBackFunc)(void *imageBuffer,int width,int height,void *pUserData),void *pUserData);
	void AxisStop();

private:
	string URL;	
	string UsrName;
	string PASSWORD;

	void *iData;				// �ڲ�����
};


#endif