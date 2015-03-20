
// ColorRecDlg.h : ͷ�ļ�
//

#pragma once
#include "CvvImage.h"
#include <vector>

using namespace std;


// CColorRecDlg �Ի���
class CColorRecDlg : public CDialogEx
{
// ����
public:
	CColorRecDlg(CWnd* pParent = NULL);	// ��׼���캯��

	CFile movefile;
	CString filepath;
	CString Imagepath;
	CString m_picname;
	vector<CString> Imagefilepath;
	vector<CString> Imagefilename;
	vector<CString> Imagefiletitle;
	IplImage *curcolorImage;
	IplImage *curshowImage;
	CEdit *m_picnameShow;
	CvvImage DrawImage;
	HDC showhdc;
	CRect rect_showpic;
	HDC colorhdc;
	CRect rect_color;
	int count;
	bool getcolor;
	void GetImageFile(CString srcPath, std::vector<CString> &pathfile, std::vector<CString> &titlefile, std::vector<CString> &namefile);
	bool GetImagecolor(CString imgFilePath);

// �Ի�������
	enum { IDD = IDD_COLORREC_DIALOG };

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
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnBnClickedOpen();
	afx_msg void OnBnClickedBlack();
	afx_msg void OnBnClickedYellow();
	afx_msg void OnBnClickedBlue();
	afx_msg void OnBnClickedGreen();
	afx_msg void OnBnClickedRed();
	afx_msg void OnBnClickedSilvery();
	afx_msg void OnBnClickedWhite();
	afx_msg void OnBnClickedBrown();
	afx_msg void OnBnClickedNext();
	afx_msg void OnBnClickedSave();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnClose();
};
