
// FudanParkingDlg.h : ͷ�ļ�
//

#pragma once
#include "MyThread.h"
#include "VideoRead.h"
#include "DBThread.h"



// CFudanParkingDlg �Ի���
class CFudanParkingDlg : public CDialogEx
{
// ����
public:
	CFudanParkingDlg(CWnd* pParent = NULL);	// ��׼���캯��

	HDC pic_hdc;
	CRect rect;
	CString filePath;
	CMyThread carDetectThread;
	CVideoRead videoreadIn;
	CDBThread dbthread;
	TQueue<struct CarStatus> *queue;

// �Ի�������
	enum { IDD = IDD_FUDANPARKING_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
	afx_msg void OnBnClickedView();
};
