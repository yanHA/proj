
// FudanParking.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CFudanParkingApp:
// �йش����ʵ�֣������ FudanParking.cpp
//

class CFudanParkingApp : public CWinApp
{
public:
	CFudanParkingApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CFudanParkingApp theApp;