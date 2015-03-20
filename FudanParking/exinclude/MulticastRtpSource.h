#pragma once

#include "MirMediaSource.h"
#include "MediaData.h"
#include <string>
using namespace std;

class RTPVIDEO_DLL_EXPORT_IMPORT MulticastRtpSource : public MirMediaSource
{
public:
	MulticastRtpSource(string strGroupIp,int iGroupPort,Codec codec);
	virtual ~MulticastRtpSource(void);

	virtual int open(MediaSourceCallbackFun callbackFun,
		void *pUserData ,unsigned char rtpPayloadFormat);
	virtual void close();

public:
	void afterGettingFrameCallback(unsigned frameSize,
					unsigned numTruncatedBytes,
					struct timeval presentationTime,
					unsigned durationInMicroseconds);
	void onSourceCloseCallback();

	void loopThreadCallback();
private:
	static void afterGettingFrame(void* clientData, unsigned frameSize,
					unsigned numTruncatedBytes,
					struct timeval presentationTime,
					unsigned durationInMicroseconds);
	static void onSourceClose(void *pUserData);

	static DWORD WINAPI loopThread(void *param);//
	HANDLE	m_hThread;
private:
	string	m_strGroupIp;
	int		m_iGroupPort;
	bool	m_bIsEventLoopThreadExit;

	class LiveParam
	{
	public:
		LiveParam();
		~LiveParam();

		void *pEnv;
		void *pScheduler;
		void *pRTPSource;
		void *pGroupsock;

		int	iBufferSize;
		unsigned char *pBuffer;
	}*m_pLiveParam;

	int		m_iHadDataOffset;//在H264的RTP流中需要用到，因为有可能SPS和PPS和视频帧不是在一起的。
};
