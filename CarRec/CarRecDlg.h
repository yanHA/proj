
// CarRecDlg.h : 头文件
//

#pragma once

#include "CvvImage.h"
#include "afxwin.h"
#include "CarDisThread.h"

// CCarRecDlg 对话框
class CCarRecDlg : public CDialogEx
{
// 构造
public:
	CCarRecDlg(CWnd* pParent = NULL);	// 标准构造函数

	CProgressCtrl *pProgCtrl;
	CEdit *eEditControl;
	CEdit *eEditInput;
	CEdit *eEditControlTime;
	CButton *buttonOpen;
	CButton *buttonProc;
	CStatic *Text;
	CStatic *TextfileCount;
	CStatic *TextCorrect;
	CStatic *TextalreadCount;
	CStatic *TextCorrectCount;

// 对话框数据
	enum { IDD = IDD_CARREC_DIALOG };

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

private:
	int m_nMax, m_nStep;
	IplImage *Image;
	CvvImage showImage;
	HDC hdc_Image;
	HDC hdc_Log;
	CRect rect_log;
	CRect rect_Image;
	CString filepath;
	CString filepath_1;
	CCarDisThread carDis;

public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedStartpro();
	CStatic m_showlogo;
	afx_msg void OnClose();
	CEdit m_showText;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
