#ifndef VideoAcqAxisWrapper_H
#define VideoAcqAxisWrapper_H

#include <string>
using namespace std;

#ifdef FrVideoAcqAxis_DLL
#define FrVideoAcqAxis_DLL __declspec(dllimport)
#else
#define FrVideoAcqAxis_DLL __declspec(dllexport)
#endif

/** 视频采集模块参数AxisWrapper专用 */
struct AcqParamAxis
{
    string ipv4;                // ip地址
    double frameRate;           // 帧率
    int channel;                // 通道号，单通道摄像机为0；多通道硬盘录像机为>0
	int port;					// 端口号，一般为8000
	string user;                // 用户名
	string pass;                // 密码
	int codec;					// 编码类型.0:h264
};

/** 视频采集axis封装类 */
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

	void *iData;				// 内部数据
};


#endif