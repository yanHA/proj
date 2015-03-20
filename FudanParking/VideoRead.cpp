#include "stdafx.h"
#include "VideoRead.h"
#include "resource.h"

CVideoRead::CVideoRead()
{
	
}

CVideoRead::~CVideoRead()
{
	pAcqThread->StopAcq();
}

void CVideoRead::VideoInitialize()
{
	vBuffer = new CVideoBuffer();
	char *path;
	HWND hwnd_path = GetDlgItem(AfxGetApp()->GetMainWnd()->GetSafeHwnd(), IDC_VIDEOPATH);

	//读取配置文件参数
	
	m_itemName = "Section0";
	vBuffer->CreateBuffer(25, CONFIG_FILE_NAME, m_itemName);
	int type = GetPrivateProfileIntA(m_itemName, "AcqMode", 0, CONFIG_FILE_NAME);
	
	if(type == 1)
	{
		//本地视屏文件
		pAcqThread = new CVideoAcqAvi();
		GetPrivateProfileStringA(m_itemName, "AcqVideo", "TestVideo.avi", m_filePath, sizeof(m_filePath), CONFIG_FILE_NAME);
		param.frameRate = GetPrivateProfileIntA(m_itemName, "VideoFps", 0, CONFIG_FILE_NAME);
		param.fileName = m_filePath;
		path = m_filePath;
		SetWindowTextA(hwnd_path, path);
	}
	else if(type == 2)
	{
		//摄像头获取视屏数据
		char str[128];
		pAcqThread = new CVideoAcqAxis();
		GetPrivateProfileStringA(m_itemName, "AcqCamIP", "192.16.8.1.1", m_tmpStr1, sizeof(m_tmpStr1), CONFIG_FILE_NAME);
		param.channel = 0;
		param.ipv4 = m_tmpStr1;
		param.port = GetPrivateProfileIntA(m_itemName, "AxisPort", 8000, CONFIG_FILE_NAME);
		sprintf(str, "%s:%d", m_tmpStr1, param.port);
		path = str;
		SetWindowTextA(hwnd_path, path);
	}
	else if(type == 3)
	{
		//睿捷平台
		char str[128];
		pAcqThread = new CVideoAcqRJ();
		GetPrivateProfileStringA(m_itemName, "AcqCamIP", "192.168.1.1", m_tmpStr1, sizeof(m_tmpStr1), CONFIG_FILE_NAME);
		GetPrivateProfileStringA(m_itemName, "User", "root", m_tmpStr2, sizeof(m_tmpStr2), CONFIG_FILE_NAME);
		GetPrivateProfileStringA(m_itemName, "PassWord", "password", m_tmpStr3, sizeof(m_tmpStr3), CONFIG_FILE_NAME);

		param.channel = 0;
		param.ipv4 = m_tmpStr1;
		param.user = m_tmpStr2;
		param.pass = m_tmpStr3;
		param.port = GetPrivateProfileIntA(m_itemName, "AxisPort", 8000, CONFIG_FILE_NAME);
		sprintf(str,"%s:%d", m_tmpStr1, param.port);
		path = str;
		SetWindowTextA(hwnd_path, path);
	}

	//启动读取视屏线程

	pAcqThread->Initialize(vBuffer, param);

	pAcqThread->StartAcq();

}