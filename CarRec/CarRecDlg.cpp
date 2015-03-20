
// CarRecDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CarRec.h"
#include "CarRecDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCarRecDlg �Ի���




CCarRecDlg::CCarRecDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCarRecDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCarRecDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LOG_STATIC, m_showlogo);
	DDX_Control(pDX, IDC_EDIT2, m_showText);
}

BEGIN_MESSAGE_MAP(CCarRecDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_OPEN, &CCarRecDlg::OnBnClickedOpen)
	ON_BN_CLICKED(IDC_STARTPRO, &CCarRecDlg::OnBnClickedStartpro)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CCarRecDlg ��Ϣ�������

BOOL CCarRecDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	pProgCtrl = (CProgressCtrl*)GetDlgItem(IDC_PROGRESS1);
	eEditControl = (CEdit*)GetDlgItem(IDC_EDIT2);
	hdc_Image = GetDlgItem(IDC_PIC)->GetDC()->GetSafeHdc();
	GetDlgItem(IDC_PIC)->GetClientRect(rect_Image);
	hdc_Log = GetDlgItem(IDC_LOG)->GetDC()->GetSafeHdc();
	GetDlgItem(IDC_LOG)->GetClientRect(rect_log);
	GetDlgItem(IDC_EDIT3)->SetWindowTextA("30");

	eEditInput = (CEdit*)GetDlgItem(IDC_EDIT1);
	eEditControlTime = (CEdit*)GetDlgItem(IDC_EDIT3);
	buttonOpen = (CButton*)GetDlgItem(IDC_OPEN);
	buttonProc = (CButton*)GetDlgItem(IDC_STARTPRO);
	Text = (CStatic*)GetDlgItem(IDC_Text1);
	TextfileCount = (CStatic*)GetDlgItem(IDC_FILECOUNT);
	TextCorrect = (CStatic*)GetDlgItem(IDC_CORRECT);
	TextalreadCount = (CStatic*)GetDlgItem(IDC_ALREADCOUNT);
	TextCorrectCount = (CStatic*)GetDlgItem(IDC_CORRECTCOUNT);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CCarRecDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCarRecDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{	
		IplImage *image = cvLoadImage("LOGO.bmp");
		CvvImage LogImage;
		LogImage.CopyOf(image, 1);
		LogImage.DrawToHDC(hdc_Log, rect_log);
		cvReleaseImage(&image);
		
		if(carDis.imgSrc != NULL)
		{
			LogImage.CopyOf(carDis.imgSrc,1);
			LogImage.DrawToHDC(hdc_Image, rect_Image);
		}
		
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCarRecDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCarRecDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	/*
	if(nIDEvent == 1)
	{
		pProgCtrl->StepIt();
		int nCurPos = pProgCtrl->GetPos();

		int showStatic = nCurPos*100 / (m_nMax - 0);
		CString str;
		str.Format("%d", showStatic);
		str = str + "%";
		GetDlgItem(IDC_Text1)->SetWindowTextA(str);

		if(nCurPos == m_nMax)
		{
			KillTimer(1);
		}
	}
	*/
	CDialogEx::OnTimer(nIDEvent);
}


void CCarRecDlg::OnBnClickedOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	BROWSEINFO bi;
	char Buffer[MAX_PATH];
	ZeroMemory(&bi, sizeof(BROWSEINFO));

	LPITEMIDLIST pid1 = SHBrowseForFolder(&bi);

	//TCHAR *path = new TCHAR[MAX_PATH];
	
	if(pid1 != NULL)
	{
		SHGetPathFromIDList(pid1, Buffer);
		filepath = Buffer;
		GetDlgItem(IDC_EDIT1)->SetWindowTextA(filepath);
	}

	IMalloc *imalloc = NULL;
	if(SUCCEEDED(SHGetMalloc(&imalloc)))
	{
		imalloc->Free(pid1);
		imalloc->Release();
	}
    /*
    CFileDialog fileDlg(TRUE, NULL, NULL, NULL, NULL, this);

    if(fileDlg.DoModal() == IDOK)
    {
		filepath = fileDlg.GetPathName();
		GetDlgItem(IDC_EDIT1)->SetWindowTextA(filepath);

        Image = cvLoadImage(fileDlg.GetPathName());

		if(Image != NULL)
		{
			showImage.CopyOf(Image, 1);
			showImage.DrawToHDC(hdc_Image, rect_Image);
		}
    }
	*/
}


void CCarRecDlg::OnBnClickedStartpro()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	GetDlgItem(IDC_EDIT1)->GetWindowTextA(filepath_1);

	if(filepath_1.GetLength() == 0)
	{
		MessageBoxA("δ����·�����������ļ�·����", "�Ϻ����ӳ���ʶ�����v1.0", MB_ICONWARNING);
	}
	else
	{
		bool Intial = carDis.InitalizeCar(filepath_1, hdc_Image, rect_Image, pProgCtrl, eEditControl, eEditInput, eEditControlTime, buttonOpen, buttonProc, Text, TextfileCount, TextCorrect, TextalreadCount, TextCorrectCount);
		if(Intial)
		{
			carDis.StartThread();

			GetDlgItem(IDC_ALREADCOUNT)->SetWindowTextA("0");
			GetDlgItem(IDC_CORRECT)->SetWindowTextA("0");
			GetDlgItem(IDC_CORRECTCOUNT)->SetWindowTextA("0");
			GetDlgItem(IDC_OPEN)->EnableWindow(FALSE);
			GetDlgItem(IDC_STARTPRO)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT1)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT2)->EnableWindow(FALSE);
			GetDlgItem(IDC_EDIT3)->EnableWindow(FALSE);
		}
		else
		{
			MessageBoxA("��ʼ��ʧ�ܣ�������ܹ��Ƿ���ϣ�", "�Ϻ����ӳ���ʶ�����v1.0", MB_ICONWARNING);
		}
	}
}


void CCarRecDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ

	if(carDis.m_bThreadRuning)
		carDis.StopThread();

	CDialogEx::OnClose();
}


BOOL CCarRecDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
		return TRUE;
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}
