
// FudanParkingDlg.h : 头文件
//

#pragma once
#include "MyThread.h"
#include "VideoRead.h"
#include "DBThread.h"



// CFudanParkingDlg 对话框
class CFudanParkingDlg : public CDialogEx
{
// 构造
public:
	CFudanParkingDlg(CWnd* pParent = NULL);	// 标准构造函数

	HDC pic_hdc;
	CRect rect;
	CString filePath;
	CMyThread carDetectThread;
	CVideoRead videoreadIn;
	CDBThread dbthread;
	TQueue<struct CarStatus> *queue;

// 对话框数据
	enum { IDD = IDD_FUDANPARKING_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg void OnBnClickedView();
};
