
// CarRecDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CarRec.h"
#include "CarRecDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CCarRecDlg 对话框




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


// CCarRecDlg 消息处理程序

BOOL CCarRecDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

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

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCarRecDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
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

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCarRecDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCarRecDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
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
	// TODO: 在此添加控件通知处理程序代码

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
	// TODO: 在此添加控件通知处理程序代码

	GetDlgItem(IDC_EDIT1)->GetWindowTextA(filepath_1);

	if(filepath_1.GetLength() == 0)
	{
		MessageBoxA("未输入路径，请输入文件路径！", "上海亚视车辆识别程序v1.0", MB_ICONWARNING);
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
			MessageBoxA("初始化失败，请检查加密狗是否插上！", "上海亚视车辆识别程序v1.0", MB_ICONWARNING);
		}
	}
}


void CCarRecDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	if(carDis.m_bThreadRuning)
		carDis.StopThread();

	CDialogEx::OnClose();
}


BOOL CCarRecDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
		return TRUE;
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}
