
// CarRecDlg.h : ͷ�ļ�
//

#pragma once

#include "CvvImage.h"
#include "afxwin.h"
#include "CarDisThread.h"

// CCarRecDlg �Ի���
class CCarRecDlg : public CDialogEx
{
// ����
public:
	CCarRecDlg(CWnd* pParent = NULL);	// ��׼���캯��

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

// �Ի�������
	enum { IDD = IDD_CARREC_DIALOG };

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
