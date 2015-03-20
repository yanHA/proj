
// FudanParkingDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "FudanParking.h"
#include "FudanParkingDlg.h"
#include "afxdialogex.h"
#include "CvvImage.h"


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


// CFudanParkingDlg �Ի���




CFudanParkingDlg::CFudanParkingDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFudanParkingDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFudanParkingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CFudanParkingDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_VIEW, &CFudanParkingDlg::OnBnClickedView)
END_MESSAGE_MAP()


// CFudanParkingDlg ��Ϣ�������

BOOL CFudanParkingDlg::OnInitDialog()
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
	//LPSYSTEM_INFO lpsysteminfo;
	//GetSystemInfo(lpsysteminfo);

	pic_hdc = GetDlgItem(IDC_PICTURE)->GetDC()->GetSafeHdc();
	GetDlgItem(IDC_PICTURE)->GetClientRect(rect);

	queue = new TQueue<struct CarStatus>(100);

	videoreadIn.VideoInitialize();

	carDetectThread.Initialize(pic_hdc, rect,videoreadIn.vBuffer, queue);
	dbthread.DBThreadInitialize(queue);
	
	carDetectThread.StartThread();
	dbthread.StartThread();
	
	//printf("hereAAAAA!!!\n");

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CFudanParkingDlg::OnSysCommand(UINT nID, LPARAM lParam)
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


void CFudanParkingDlg::OnPaint()
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
		CDialogEx::OnPaint();

		//GetDlgItem(IDC_ALLCAR)->SetWindowText("this is note info");
		//GetDlgItem(IDC_ALLCAR)->EnableWindow(FALSE);
		/*
		CRect rect;
		CvvImage ShowImage;
		ShowImage.Load("./etc/ParkingSpot.jpg");
		HDC Pic_hdc = GetDlgItem(IDC_PICTURE)->GetDC()->GetSafeHdc();
		GetDlgItem(IDC_PICTURE)->GetClientRect(rect);
		ShowImage.DrawToHDC(Pic_hdc, rect);
		printf("here!!!!!!\n");
		*/
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CFudanParkingDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CFudanParkingDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	carDetectThread.StopThread();
	dbthread.StopThread();

	delete[] queue;

	CDialogEx::OnClose();
}


void CFudanParkingDlg::OnBnClickedView()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//cvShowImage("Video", )
}
