
// ColorRecDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ColorRec.h"
#include "ColorRecDlg.h"
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


// CColorRecDlg �Ի���




CColorRecDlg::CColorRecDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CColorRecDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CColorRecDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CColorRecDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_OPEN, &CColorRecDlg::OnBnClickedOpen)
	ON_BN_CLICKED(IDC_BLACK, &CColorRecDlg::OnBnClickedBlack)
	ON_BN_CLICKED(IDC_YELLOW, &CColorRecDlg::OnBnClickedYellow)
	ON_BN_CLICKED(IDC_BLUE, &CColorRecDlg::OnBnClickedBlue)
	ON_BN_CLICKED(IDC_GREEN, &CColorRecDlg::OnBnClickedGreen)
	ON_BN_CLICKED(IDC_RED, &CColorRecDlg::OnBnClickedRed)
	ON_BN_CLICKED(IDC_SILVERY, &CColorRecDlg::OnBnClickedSilvery)
	ON_BN_CLICKED(IDC_WHITE, &CColorRecDlg::OnBnClickedWhite)
	ON_BN_CLICKED(IDC_BROWN, &CColorRecDlg::OnBnClickedBrown)
	ON_BN_CLICKED(IDC_NEXT, &CColorRecDlg::OnBnClickedNext)
	ON_BN_CLICKED(IDC_SAVE, &CColorRecDlg::OnBnClickedSave)
	ON_BN_CLICKED(IDC_CANCEL, &CColorRecDlg::OnBnClickedCancel)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CColorRecDlg ��Ϣ�������

BOOL CColorRecDlg::OnInitDialog()
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

	CBitmap m_bmpblack;
	m_bmpblack.LoadBitmapA(IDB_BITMAP1);
	HBITMAP hBitmapblack = (HBITMAP)m_bmpblack.GetSafeHandle();
	((CButton*)GetDlgItem(IDC_BLACK))->SetBitmap(hBitmapblack);

	CBitmap m_bmpblue;
	m_bmpblue.LoadBitmapA(IDB_BITMAP2);
	HBITMAP hBitmapblue = (HBITMAP)m_bmpblue.GetSafeHandle();
	((CButton*)GetDlgItem(IDC_BLUE))->SetBitmap(hBitmapblue);

	CBitmap m_bmpgreen;
	m_bmpgreen.LoadBitmapA(IDB_BITMAP3);
	HBITMAP hBitmapgreen = (HBITMAP)m_bmpgreen.GetSafeHandle();
	((CButton*)GetDlgItem(IDC_GREEN))->SetBitmap(hBitmapgreen);

	CBitmap m_bmpred;
	m_bmpred.LoadBitmapA(IDB_BITMAP4);
	HBITMAP hBitmapred = (HBITMAP)m_bmpred.GetSafeHandle();
	((CButton*)GetDlgItem(IDC_RED))->SetBitmap(hBitmapred);
	
	CBitmap m_bmpsilvery;
	m_bmpsilvery.LoadBitmapA(IDB_BITMAP5);
	HBITMAP hBitmapsilvery = (HBITMAP)m_bmpsilvery.GetSafeHandle();
	((CButton*)GetDlgItem(IDC_SILVERY))->SetBitmap(hBitmapsilvery);

	CBitmap m_bmpwhite;
	m_bmpwhite.LoadBitmapA(IDB_BITMAP6);
	HBITMAP hBitmapwhite = (HBITMAP)m_bmpwhite.GetSafeHandle();
	((CButton*)GetDlgItem(IDC_WHITE))->SetBitmap(hBitmapwhite);

	CBitmap m_bmpyellow;
	m_bmpyellow.LoadBitmapA(IDB_BITMAP7);
	HBITMAP hBitmapyellow = (HBITMAP)m_bmpyellow.GetSafeHandle();
	((CButton*)GetDlgItem(IDC_YELLOW))->SetBitmap(hBitmapyellow);

	CBitmap m_bmpbrown;
	m_bmpbrown.LoadBitmapA(IDB_BITMAP8);
	HBITMAP hBitmapbrown = (HBITMAP)m_bmpbrown.GetSafeHandle();
	((CButton*)GetDlgItem(IDC_BROWN))->SetBitmap(hBitmapbrown);

	showhdc = GetDlgItem(IDC_SHOWPIC)->GetDC()->GetSafeHdc();
	GetDlgItem(IDC_SHOWPIC)->GetClientRect(rect_showpic);
	colorhdc = GetDlgItem(IDC_COLOR)->GetDC()->GetSafeHdc();
	GetDlgItem(IDC_COLOR)->GetClientRect(rect_color);

	GetDlgItem(IDC_NEXT)->EnableWindow(FALSE);
	GetDlgItem(IDC_BLACK)->EnableWindow(FALSE);
	GetDlgItem(IDC_BLUE)->EnableWindow(FALSE);
	GetDlgItem(IDC_RED)->EnableWindow(FALSE);
	GetDlgItem(IDC_GREEN)->EnableWindow(FALSE);
	GetDlgItem(IDC_WHITE)->EnableWindow(FALSE);
	GetDlgItem(IDC_SILVERY)->EnableWindow(FALSE);
	GetDlgItem(IDC_BROWN)->EnableWindow(FALSE);

	curcolorImage  = NULL;
	curshowImage = NULL;
	m_picnameShow = (CEdit*)GetDlgItem(IDC_EDIT2);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CColorRecDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CColorRecDlg::GetImageFile(CString srcPath, std::vector<CString> &pathfile, std::vector<CString> &titlefile, std::vector<CString> &namefile)
{
	//assert(srcPath != "");

    std::vector<CString> ext;
    ext.push_back(".jpg");
    ext.push_back(".jpeg");
    ext.push_back(".bmp");
    ext.push_back(".png");

    char path[MAX_PATH];
    sprintf(path, "%s\\*.*", srcPath);
    CFileFind finder;
    BOOL isFinded = finder.FindFile(CString(path));
    while(isFinded)
    {
        isFinded = finder.FindNextFile();
        if(finder.IsDots()) continue;
        if(finder.IsDirectory())        // �ļ��еݹ�
        {
            GetImageFile(finder.GetFilePath(), pathfile, titlefile, namefile);
            continue;
        }

        // ��ȡ�ļ��ĺ�׺��
        CString name    = finder.GetFileName();
        CString title   = finder.GetFileTitle();
        int extLen      = name.GetLength() - title.GetLength();
        CString ex      = name.Right(extLen);

        // �б��Ƿ�ΪͼƬ�ļ�
        bool flag = false;
        for(int i = 0; i < (int)ext.size(); i ++)
        {
            if(ex.MakeLower() != ext[i]) continue;
            flag = true;
            break;
        }
        if(!flag) continue;

        pathfile.push_back(finder.GetFilePath());
		titlefile.push_back(finder.GetFileTitle());
		namefile.push_back(finder.GetFileName());
    }
    finder.Close();
}

bool CColorRecDlg::GetImagecolor(CString imgFilePath)
{
	string indicator;
	string imagePath = Imagepath.GetBuffer(0);
	indicator = imagePath.substr(imagePath.find_last_of("(")+1, imagePath.find_last_of(")")-imagePath.find_last_of("(")-1);

	printf("%s\n", indicator.c_str());
	
	if(indicator == "��")
	{
		IplImage *color = cvLoadImage("etc\\black.jpg");
		if(curcolorImage != NULL)
		{ 
			cvReleaseImage(&curcolorImage);
			curcolorImage = cvLoadImage("etc\\black.jpg");
		}
		else
			curcolorImage = cvLoadImage("etc\\black.jpg");
		DrawImage.CopyOf(color);
		DrawImage.DrawToHDC(colorhdc, rect_color);
		cvReleaseImage(&color);

		return true;
	}
	else if(indicator == "��")
	{
		IplImage *color = cvLoadImage("etc\\red.jpg");
		if(curcolorImage != NULL)
		{ 
			cvReleaseImage(&curcolorImage);
			curcolorImage = cvLoadImage("etc\\red.jpg");
		}
		else
			curcolorImage = cvLoadImage("etc\\red.jpg");
		DrawImage.CopyOf(color);
		DrawImage.DrawToHDC(colorhdc, rect_color);
		cvReleaseImage(&color);

		return true;
	}
	else if(indicator == "��")
	{
		IplImage *color = cvLoadImage("etc\\yellow.jpg");
		if(curcolorImage != NULL)
		{ 
			cvReleaseImage(&curcolorImage);
			curcolorImage = cvLoadImage("etc\\yellow.jpg");
		}
		else
			curcolorImage = cvLoadImage("etc\\yellow.jpg");
		DrawImage.CopyOf(color);
		DrawImage.DrawToHDC(colorhdc, rect_color);
		cvReleaseImage(&color);

		return true;
	}
	else if(indicator == "��")
	{
		IplImage *color = cvLoadImage("etc\\white.jpg");
		if(curcolorImage != NULL)
		{ 
			cvReleaseImage(&curcolorImage);
			curcolorImage = cvLoadImage("etc\\white.jpg");
		}
		else
			curcolorImage = cvLoadImage("etc\\white.jpg");
		DrawImage.CopyOf(color);
		DrawImage.DrawToHDC(colorhdc, rect_color);
		cvReleaseImage(&color);

		return true;
	}
	else if(indicator == "��")
	{
		IplImage *color = cvLoadImage("etc\\blue.jpg");
		if(curcolorImage != NULL)
		{ 
			cvReleaseImage(&curcolorImage);
			curcolorImage = cvLoadImage("etc\\blue.jpg");
		}
		else
			curcolorImage = cvLoadImage("etc\\blue.jpg");
		DrawImage.CopyOf(color);
		DrawImage.DrawToHDC(colorhdc, rect_color);
		cvReleaseImage(&color);

		return true;
	}
	else if(indicator == "��")
	{
		IplImage *color = cvLoadImage("etc\\silvery.jpg");
		if(curcolorImage != NULL)
		{ 
			cvReleaseImage(&curcolorImage);
			curcolorImage = cvLoadImage("etc\\silvery.jpg");
		}
		else
			curcolorImage = cvLoadImage("etc\\silvery.jpg");
		DrawImage.CopyOf(color);
		DrawImage.DrawToHDC(colorhdc, rect_color);
		cvReleaseImage(&color);

		return true;
	}
	else if(indicator == "��")
	{
		IplImage *color = cvLoadImage("etc\\green.jpg");
		if(curcolorImage != NULL) 
		{
			cvReleaseImage(&curcolorImage);
			curcolorImage = cvLoadImage("etc\\green.jpg");
		}
		else
			curcolorImage = cvLoadImage("etc\\green.jpg");
		DrawImage.CopyOf(color);
		DrawImage.DrawToHDC(colorhdc, rect_color);
		cvReleaseImage(&color);

		return true;
	}
	else if(indicator == "��")
	{
		IplImage *color = cvLoadImage("etc\\brown.jpg");
		if(curcolorImage != NULL) 
		{
			cvReleaseImage(&curcolorImage);
			curcolorImage = cvLoadImage("etc\\brown.jpg");
		}
		else
			curcolorImage = cvLoadImage("etc\\brown.jpg");
		DrawImage.CopyOf(color);
		DrawImage.DrawToHDC(colorhdc, rect_color);
		cvReleaseImage(&color);

		return true;
	}
	else
		return false;
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CColorRecDlg::OnPaint()
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
		if(curcolorImage != NULL)
		{
			DrawImage.CopyOf(curcolorImage);
			DrawImage.DrawToHDC(colorhdc, rect_color);
		}
		if(curshowImage != NULL)
		{
			DrawImage.CopyOf(curshowImage);
			DrawImage.DrawToHDC(showhdc, rect_showpic);
		}
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CColorRecDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CColorRecDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
		return TRUE;
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		return TRUE;

	return CDialogEx::PreTranslateMessage(pMsg);
}


void CColorRecDlg::OnBnClickedOpen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	count = 0;
	Imagefilepath.clear();
	Imagefilename.clear();
	Imagefiletitle.clear();

	//CString path;
	GetDlgItem(IDC_EDIT1)->GetWindowTextA(filepath);
	
	if(filepath.GetLength() == 0)
	{
		//CString filepath;
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

		if(filepath.GetLength() != 0)
		{
			CString showtotal;
			GetImageFile(filepath, Imagefilepath, Imagefilename, Imagefiletitle);
			int total = Imagefilepath.size();
			printf("%d\n", total);
			showtotal.Format("%d", total);
			GetDlgItem(IDC_TOTALFILE)->SetWindowTextA(showtotal);

			if(total != 0)
			{
				Imagepath = Imagefilepath[count];
				m_picname = Imagefiletitle[count];
				m_picnameShow->SetWindowTextA(m_picname);

				if(curshowImage != NULL) 
				{ 
					cvReleaseImage(&curshowImage);
					curshowImage = cvLoadImage(Imagepath);
				}
				else 
					curshowImage = cvLoadImage(Imagepath);

				DrawImage.Load(Imagepath);
				DrawImage.DrawToHDC(showhdc, rect_showpic);
				CString showcount;
				showcount.Format("%d", count+1);
				GetDlgItem(IDC_NOWFILE)->SetWindowTextA(showcount);

				getcolor = GetImagecolor(Imagepath);
				if(getcolor)
				{
					GetDlgItem(IDC_NEXT)->EnableWindow(TRUE);
					GetDlgItem(IDC_BLACK)->EnableWindow(TRUE);
					GetDlgItem(IDC_WHITE)->EnableWindow(TRUE);
					GetDlgItem(IDC_YELLOW)->EnableWindow(TRUE);
					GetDlgItem(IDC_BLUE)->EnableWindow(TRUE);
					GetDlgItem(IDC_GREEN)->EnableWindow(TRUE);
					GetDlgItem(IDC_RED)->EnableWindow(TRUE);
					GetDlgItem(IDC_SILVERY)->EnableWindow(TRUE);
					GetDlgItem(IDC_BROWN)->EnableWindow(TRUE);
				}
				else
				{
					GetDlgItem(IDC_NEXT)->EnableWindow(FALSE);
					GetDlgItem(IDC_BLACK)->EnableWindow(TRUE);
					GetDlgItem(IDC_WHITE)->EnableWindow(TRUE);
					GetDlgItem(IDC_YELLOW)->EnableWindow(TRUE);
					GetDlgItem(IDC_BLUE)->EnableWindow(TRUE);
					GetDlgItem(IDC_GREEN)->EnableWindow(TRUE);
					GetDlgItem(IDC_RED)->EnableWindow(TRUE);
					GetDlgItem(IDC_SILVERY)->EnableWindow(TRUE);
					GetDlgItem(IDC_BROWN)->EnableWindow(TRUE);
				}
			}
		}
	}
	else
	{
		CString showtotal;
		GetImageFile(filepath, Imagefilepath, Imagefilename, Imagefiletitle);
		int total = Imagefilepath.size();
		printf("%d\n", total);
		showtotal.Format("%d", total);
		GetDlgItem(IDC_TOTALFILE)->SetWindowTextA(showtotal);

		if(total != 0)
		{
			Imagepath = Imagefilepath[count];
			m_picname = Imagefiletitle[count];
			m_picnameShow->SetWindowTextA(m_picname);

			if(curshowImage != NULL)
			{ 
				cvReleaseImage(&curshowImage);
				curshowImage = cvLoadImage(Imagepath);
			}
			else
				curshowImage = cvLoadImage(Imagepath);

			DrawImage.Load(Imagepath);
			DrawImage.DrawToHDC(showhdc, rect_showpic);
			CString showcount;
			showcount.Format("%d", count+1);
			GetDlgItem(IDC_NOWFILE)->SetWindowTextA(showcount);

			getcolor = GetImagecolor(Imagepath);
			if(getcolor)
			{
				GetDlgItem(IDC_NEXT)->EnableWindow(TRUE);
				GetDlgItem(IDC_BLACK)->EnableWindow(TRUE);
				GetDlgItem(IDC_WHITE)->EnableWindow(TRUE);
				GetDlgItem(IDC_YELLOW)->EnableWindow(TRUE);
				GetDlgItem(IDC_BLUE)->EnableWindow(TRUE);
				GetDlgItem(IDC_GREEN)->EnableWindow(TRUE);
				GetDlgItem(IDC_RED)->EnableWindow(TRUE);
				GetDlgItem(IDC_SILVERY)->EnableWindow(TRUE);
				GetDlgItem(IDC_BROWN)->EnableWindow(TRUE);
			}
			else
			{
				GetDlgItem(IDC_NEXT)->EnableWindow(FALSE);
				GetDlgItem(IDC_BLACK)->EnableWindow(TRUE);
				GetDlgItem(IDC_WHITE)->EnableWindow(TRUE);
				GetDlgItem(IDC_YELLOW)->EnableWindow(TRUE);
				GetDlgItem(IDC_BLUE)->EnableWindow(TRUE);
				GetDlgItem(IDC_GREEN)->EnableWindow(TRUE);
				GetDlgItem(IDC_RED)->EnableWindow(TRUE);
				GetDlgItem(IDC_SILVERY)->EnableWindow(TRUE);
				GetDlgItem(IDC_BROWN)->EnableWindow(TRUE);
			}
		}
	}
}


void CColorRecDlg::OnBnClickedBlack()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	if(count >= (int)Imagefilepath.size())
	{
		MessageBox("ͼƬ��ע��ϣ�");
		return;
	}
	else
	{
		if(getcolor)
		{
			string imgColor;
			string imagePath = Imagepath.GetBuffer(0);
			printf("%s\n", Imagepath);
			imagePath.erase(imagePath.find_last_of("(")+1, 2);
			imagePath.insert(imagePath.find_last_of("(")+1, "��");

			IplImage *Image = cvLoadImage(Imagepath);
			IplImage *color = cvLoadImage("etc\\black.jpg");

			if(curcolorImage != NULL)
			{ 
				cvReleaseImage(&curcolorImage);
				curcolorImage = cvLoadImage("etc\\black.jpg");
			}
			else
				curcolorImage = cvLoadImage("etc\\black.jpg");

			DrawImage.CopyOf(color);
			DrawImage.DrawToHDC(colorhdc, rect_color);
			movefile.Remove(Imagepath);
			printf("%s\n", imagePath.c_str());
			cvSaveImage(imagePath.c_str(), Image);
			cvReleaseImage(&Image);
			cvReleaseImage(&color);
		}
		else
		{
			IplImage *Image = cvLoadImage(Imagepath);
			IplImage *color = cvLoadImage("etc\\black.jpg");

			if(curcolorImage != NULL)
			{ 
				cvReleaseImage(&curcolorImage);
				curcolorImage = cvLoadImage("etc\\black.jpg");
			}
			else
				curcolorImage = cvLoadImage("etc\\black.jpg");

			DrawImage.CopyOf(color);
			DrawImage.DrawToHDC(colorhdc, rect_color);

			CString Imagename = Imagefilename[count];
			CString Imagetitle = Imagefiletitle[count];
		

			int pathlen = Imagepath.GetLength() - Imagetitle.GetLength();
			CString newpath = Imagepath.Left(pathlen);
			int extlen = Imagetitle.GetLength() - Imagename.GetLength();
			CString ex = Imagetitle.Right(extlen);
	
			Imagename += "(��)";
			Imagename += ex;
			newpath += Imagename;
			printf("%s\n", newpath);
			movefile.Remove(Imagepath);
			cvSaveImage(newpath, Image);
			cvReleaseImage(&Image);
			cvReleaseImage(&color);
		}

		count++;
		CString showcount;
		showcount.Format("%d", count);
		GetDlgItem(IDC_NOWFILE)->SetWindowTextA(showcount);

		if(count < (int)Imagefilepath.size())
		{
			Imagepath = Imagefilepath[count];
			m_picname = Imagefiletitle[count];
			m_picnameShow->SetWindowTextA(m_picname);

			if(curshowImage != NULL)
			{ 
				cvReleaseImage(&curshowImage);
				curshowImage = cvLoadImage(Imagepath);
			}
			else
				curshowImage = cvLoadImage(Imagepath);

			DrawImage.Load(Imagepath);
			DrawImage.DrawToHDC(showhdc, rect_showpic);

			getcolor = GetImagecolor(Imagepath);
			if(getcolor)
			{
				GetDlgItem(IDC_NEXT)->EnableWindow(TRUE);
				GetDlgItem(IDC_BLACK)->EnableWindow(TRUE);
				GetDlgItem(IDC_WHITE)->EnableWindow(TRUE);
				GetDlgItem(IDC_YELLOW)->EnableWindow(TRUE);
				GetDlgItem(IDC_BLUE)->EnableWindow(TRUE);
				GetDlgItem(IDC_GREEN)->EnableWindow(TRUE);
				GetDlgItem(IDC_RED)->EnableWindow(TRUE);
				GetDlgItem(IDC_SILVERY)->EnableWindow(TRUE);
				GetDlgItem(IDC_BROWN)->EnableWindow(TRUE);
			}
			else
			{
				GetDlgItem(IDC_NEXT)->EnableWindow(FALSE);
				GetDlgItem(IDC_BLACK)->EnableWindow(TRUE);
				GetDlgItem(IDC_WHITE)->EnableWindow(TRUE);
				GetDlgItem(IDC_YELLOW)->EnableWindow(TRUE);
				GetDlgItem(IDC_BLUE)->EnableWindow(TRUE);
				GetDlgItem(IDC_GREEN)->EnableWindow(TRUE);
				GetDlgItem(IDC_RED)->EnableWindow(TRUE);
				GetDlgItem(IDC_SILVERY)->EnableWindow(TRUE);
				GetDlgItem(IDC_BROWN)->EnableWindow(TRUE);
			}
		}
		else
			return;
	}
}


void CColorRecDlg::OnBnClickedYellow()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(count >= (int)Imagefilepath.size())
	{
		MessageBox("ͼƬ��ע��ϣ�");
		return;
	}
	else
	{
		if(getcolor)
		{
			string imgColor;
			string imagePath = Imagepath.GetBuffer(0);
			printf("%s\n", Imagepath);
			imagePath.erase(imagePath.find_last_of("(")+1, 2);
			imagePath.insert(imagePath.find_last_of("(")+1, "��");

			IplImage *Image = cvLoadImage(Imagepath);
			IplImage *color = cvLoadImage("etc\\yellow.jpg");

			if(curcolorImage != NULL)
			{ 
				cvReleaseImage(&curcolorImage);
				curcolorImage = cvLoadImage("etc\\yellow.jpg");
			}
			else
				curcolorImage = cvLoadImage("etc\\yellow.jpg");

			DrawImage.CopyOf(color);
			DrawImage.DrawToHDC(colorhdc, rect_color);
			movefile.Remove(Imagepath);
			printf("%s\n", imagePath.c_str());
			cvSaveImage(imagePath.c_str(), Image);
			cvReleaseImage(&Image);
			cvReleaseImage(&color);
		}
		else
		{
			IplImage *Image = cvLoadImage(Imagepath);
			IplImage *color = cvLoadImage("etc\\yellow.jpg");

			if(curcolorImage != NULL)
			{ 
				cvReleaseImage(&curcolorImage);
				curcolorImage = cvLoadImage("etc\\yellow.jpg");
			}
			else
				curcolorImage = cvLoadImage("etc\\yellow.jpg");

			DrawImage.CopyOf(color);
			DrawImage.DrawToHDC(colorhdc, rect_color);

			CString Imagename = Imagefilename[count];
			CString Imagetitle = Imagefiletitle[count];
	
			int pathlen = Imagepath.GetLength() - Imagetitle.GetLength();
			CString newpath = Imagepath.Left(pathlen);
			int extlen = Imagetitle.GetLength() - Imagename.GetLength();
			CString ex = Imagetitle.Right(extlen);
	
			Imagename += "(��)";
			Imagename += ex;
			newpath += Imagename;
			printf("%s\n", newpath);
			movefile.Remove(Imagepath);
			cvSaveImage(newpath, Image);
			cvReleaseImage(&Image);
			cvReleaseImage(&color);
		}

		count++;
		CString showcount;
		showcount.Format("%d", count);
		GetDlgItem(IDC_NOWFILE)->SetWindowTextA(showcount);
		if(count < (int)Imagefilepath.size())
		{
			Imagepath = Imagefilepath[count];
			m_picname = Imagefiletitle[count];
			m_picnameShow->SetWindowTextA(m_picname);

			if(curshowImage != NULL)
			{ 
				cvReleaseImage(&curshowImage);
				curshowImage = cvLoadImage(Imagepath);
			}
			else
				curshowImage = cvLoadImage(Imagepath);

			DrawImage.Load(Imagepath);
			DrawImage.DrawToHDC(showhdc, rect_showpic);

			getcolor = GetImagecolor(Imagepath);
			if(getcolor)
			{
				GetDlgItem(IDC_NEXT)->EnableWindow(TRUE);
				GetDlgItem(IDC_BLACK)->EnableWindow(TRUE);
				GetDlgItem(IDC_WHITE)->EnableWindow(TRUE);
				GetDlgItem(IDC_YELLOW)->EnableWindow(TRUE);
				GetDlgItem(IDC_BLUE)->EnableWindow(TRUE);
				GetDlgItem(IDC_GREEN)->EnableWindow(TRUE);
				GetDlgItem(IDC_RED)->EnableWindow(TRUE);
				GetDlgItem(IDC_SILVERY)->EnableWindow(TRUE);
				GetDlgItem(IDC_BROWN)->EnableWindow(TRUE);
			}
			else
			{
				GetDlgItem(IDC_NEXT)->EnableWindow(FALSE);
				GetDlgItem(IDC_BLACK)->EnableWindow(TRUE);
				GetDlgItem(IDC_WHITE)->EnableWindow(TRUE);
				GetDlgItem(IDC_YELLOW)->EnableWindow(TRUE);
				GetDlgItem(IDC_BLUE)->EnableWindow(TRUE);
				GetDlgItem(IDC_GREEN)->EnableWindow(TRUE);
				GetDlgItem(IDC_RED)->EnableWindow(TRUE);
				GetDlgItem(IDC_SILVERY)->EnableWindow(TRUE);
				GetDlgItem(IDC_BROWN)->EnableWindow(TRUE);
			}
		}
		else
			return;
	}
}


void CColorRecDlg::OnBnClickedBlue()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(count >= (int)Imagefilepath.size())
	{
		MessageBox("ͼƬ��ע��ϣ�");
		return;
	}
	else
	{
		if(getcolor)
		{
			string imgColor;
			string imagePath = Imagepath.GetBuffer(0);
			printf("%s\n", Imagepath);
			imagePath.erase(imagePath.find_last_of("(")+1, 2);
			imagePath.insert(imagePath.find_last_of("(")+1, "��");

			IplImage *Image = cvLoadImage(Imagepath);
			IplImage *color = cvLoadImage("etc\\blue.jpg");

			if(curcolorImage != NULL)
			{ 
				cvReleaseImage(&curcolorImage);
				curcolorImage = cvLoadImage("etc\\blue.jpg");
			}
			else
				curcolorImage = cvLoadImage("etc\\blue.jpg");

			DrawImage.CopyOf(color);
			DrawImage.DrawToHDC(colorhdc, rect_color);
			movefile.Remove(Imagepath);
			printf("%s\n", imagePath.c_str());
			cvSaveImage(imagePath.c_str(), Image);
			cvReleaseImage(&Image);
			cvReleaseImage(&color);
		}
		else
		{
			IplImage *Image = cvLoadImage(Imagepath);
			IplImage *color = cvLoadImage("etc\\blue.jpg");

			if(curcolorImage != NULL)
			{ 
				cvReleaseImage(&curcolorImage);
				curcolorImage = cvLoadImage("etc\\blue.jpg");
			}
			else
				curcolorImage = cvLoadImage("etc\\blue.jpg");

			DrawImage.CopyOf(color);
			DrawImage.DrawToHDC(colorhdc, rect_color);

			CString Imagename = Imagefilename[count];
			CString Imagetitle = Imagefiletitle[count];
	
			int pathlen = Imagepath.GetLength() - Imagetitle.GetLength();
			CString newpath = Imagepath.Left(pathlen);
			int extlen = Imagetitle.GetLength() - Imagename.GetLength();
			CString ex = Imagetitle.Right(extlen);
	
			Imagename += "(��)";
			Imagename += ex;
			newpath += Imagename;
			printf("%s\n", newpath);
			movefile.Remove(Imagepath);
			cvSaveImage(newpath, Image);
			cvReleaseImage(&Image);
			cvReleaseImage(&color);
		}

		count++;
		CString showcount;
		showcount.Format("%d", count);
		GetDlgItem(IDC_NOWFILE)->SetWindowTextA(showcount);
		if(count < (int)Imagefilepath.size())
		{
			Imagepath = Imagefilepath[count];
			m_picname = Imagefiletitle[count];
			m_picnameShow->SetWindowTextA(m_picname);

			if(curshowImage != NULL)
			{ 
				cvReleaseImage(&curshowImage);
				curshowImage = cvLoadImage(Imagepath);
			}
			else
				curshowImage = cvLoadImage(Imagepath);

			DrawImage.Load(Imagepath);
			DrawImage.DrawToHDC(showhdc, rect_showpic);

			getcolor = GetImagecolor(Imagepath);
			if(getcolor)
			{
				GetDlgItem(IDC_NEXT)->EnableWindow(TRUE);
				GetDlgItem(IDC_BLACK)->EnableWindow(TRUE);
				GetDlgItem(IDC_WHITE)->EnableWindow(TRUE);
				GetDlgItem(IDC_YELLOW)->EnableWindow(TRUE);
				GetDlgItem(IDC_BLUE)->EnableWindow(TRUE);
				GetDlgItem(IDC_GREEN)->EnableWindow(TRUE);
				GetDlgItem(IDC_RED)->EnableWindow(TRUE);
				GetDlgItem(IDC_SILVERY)->EnableWindow(TRUE);
				GetDlgItem(IDC_BROWN)->EnableWindow(TRUE);
			}
			else
			{
				GetDlgItem(IDC_NEXT)->EnableWindow(FALSE);
				GetDlgItem(IDC_BLACK)->EnableWindow(TRUE);
				GetDlgItem(IDC_WHITE)->EnableWindow(TRUE);
				GetDlgItem(IDC_YELLOW)->EnableWindow(TRUE);
				GetDlgItem(IDC_BLUE)->EnableWindow(TRUE);
				GetDlgItem(IDC_GREEN)->EnableWindow(TRUE);
				GetDlgItem(IDC_RED)->EnableWindow(TRUE);
				GetDlgItem(IDC_SILVERY)->EnableWindow(TRUE);
				GetDlgItem(IDC_BROWN)->EnableWindow(TRUE);
			}
		}
		else
			return;
	}
}


void CColorRecDlg::OnBnClickedGreen()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(count >= (int)Imagefilepath.size())
	{
		MessageBox("ͼƬ��ע��ϣ�");
		return;
	}
	else
	{
		if(getcolor)
		{
			string imgColor;
			string imagePath = Imagepath.GetBuffer(0);
			printf("%s\n", Imagepath);
			imagePath.erase(imagePath.find_last_of("(")+1, 2);
			imagePath.insert(imagePath.find_last_of("(")+1, "��");

			IplImage *Image = cvLoadImage(Imagepath);
			IplImage *color = cvLoadImage("etc\\green.jpg");

			if(curcolorImage != NULL)
			{ 
				cvReleaseImage(&curcolorImage);
				curcolorImage = cvLoadImage("etc\\green.jpg");
			}
			else
				curcolorImage = cvLoadImage("etc\\green.jpg");

			DrawImage.CopyOf(color);
			DrawImage.DrawToHDC(colorhdc, rect_color);
			movefile.Remove(Imagepath);
			printf("%s\n", imagePath.c_str());
			cvSaveImage(imagePath.c_str(), Image);
			cvReleaseImage(&Image);
			cvReleaseImage(&color);
		}
		else
		{
			IplImage *Image = cvLoadImage(Imagepath);
			IplImage *color = cvLoadImage("etc\\green.jpg");

			if(curcolorImage != NULL)
			{ 
				cvReleaseImage(&curcolorImage);
				curcolorImage = cvLoadImage("etc\\green.jpg");
			}
			else
				curcolorImage = cvLoadImage("etc\\green.jpg");

			DrawImage.CopyOf(color);
			DrawImage.DrawToHDC(colorhdc, rect_color);

			CString Imagename = Imagefilename[count];
			CString Imagetitle = Imagefiletitle[count];
	
			int pathlen = Imagepath.GetLength() - Imagetitle.GetLength();
			CString newpath = Imagepath.Left(pathlen);
			int extlen = Imagetitle.GetLength() - Imagename.GetLength();
			CString ex = Imagetitle.Right(extlen);
	
			Imagename += "(��)";
			Imagename += ex;
			newpath += Imagename;
			printf("%s\n", newpath);
			movefile.Remove(Imagepath);
			cvSaveImage(newpath, Image);
			cvReleaseImage(&Image);
			cvReleaseImage(&color);
		}

		count++;
		CString showcount;
		showcount.Format("%d", count);
		GetDlgItem(IDC_NOWFILE)->SetWindowTextA(showcount);
		if(count < (int)Imagefilepath.size())
		{
			Imagepath = Imagefilepath[count];
			m_picname = Imagefiletitle[count];
			m_picnameShow->SetWindowTextA(m_picname);

			if(curshowImage != NULL)
			{ 
				cvReleaseImage(&curshowImage);
				curshowImage = cvLoadImage(Imagepath);
			}
			else
				curshowImage = cvLoadImage(Imagepath);

			DrawImage.Load(Imagepath);
			DrawImage.DrawToHDC(showhdc, rect_showpic);

			getcolor = GetImagecolor(Imagepath);
			if(getcolor)
			{
				GetDlgItem(IDC_NEXT)->EnableWindow(TRUE);
				GetDlgItem(IDC_BLACK)->EnableWindow(TRUE);
				GetDlgItem(IDC_WHITE)->EnableWindow(TRUE);
				GetDlgItem(IDC_YELLOW)->EnableWindow(TRUE);
				GetDlgItem(IDC_BLUE)->EnableWindow(TRUE);
				GetDlgItem(IDC_GREEN)->EnableWindow(TRUE);
				GetDlgItem(IDC_RED)->EnableWindow(TRUE);
				GetDlgItem(IDC_SILVERY)->EnableWindow(TRUE);
				GetDlgItem(IDC_BROWN)->EnableWindow(TRUE);
			}
			else
			{
				GetDlgItem(IDC_NEXT)->EnableWindow(FALSE);
				GetDlgItem(IDC_BLACK)->EnableWindow(TRUE);
				GetDlgItem(IDC_WHITE)->EnableWindow(TRUE);
				GetDlgItem(IDC_YELLOW)->EnableWindow(TRUE);
				GetDlgItem(IDC_BLUE)->EnableWindow(TRUE);
				GetDlgItem(IDC_GREEN)->EnableWindow(TRUE);
				GetDlgItem(IDC_RED)->EnableWindow(TRUE);
				GetDlgItem(IDC_SILVERY)->EnableWindow(TRUE);
				GetDlgItem(IDC_BROWN)->EnableWindow(TRUE);
			}
		}
		else
			return;
	}
}


void CColorRecDlg::OnBnClickedRed()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(count >= (int)Imagefilepath.size())
	{
		MessageBox("ͼƬ��ע��ϣ�");
		return;
	}
	else
	{
		if(getcolor)
		{
			string imgColor;
			string imagePath = Imagepath.GetBuffer(0);
			printf("%s\n", Imagepath);
			imagePath.erase(imagePath.find_last_of("(")+1, 2);
			imagePath.insert(imagePath.find_last_of("(")+1, "��");

			IplImage *Image = cvLoadImage(Imagepath);
			IplImage *color = cvLoadImage("etc\\red.jpg");

			if(curcolorImage != NULL)
			{ 
				cvReleaseImage(&curcolorImage);
				curcolorImage = cvLoadImage("etc\\red.jpg");
			}
			else
				curcolorImage = cvLoadImage("etc\\red.jpg");

			DrawImage.CopyOf(color);
			DrawImage.DrawToHDC(colorhdc, rect_color);
			movefile.Remove(Imagepath);
			printf("%s\n", imagePath.c_str());
			cvSaveImage(imagePath.c_str(), Image);
			cvReleaseImage(&Image);
			cvReleaseImage(&color);
		}
		else
		{
			IplImage *Image = cvLoadImage(Imagepath);
			IplImage *color = cvLoadImage("etc\\red.jpg");

			if(curcolorImage != NULL)
			{ 
				cvReleaseImage(&curcolorImage);
				curcolorImage = cvLoadImage("etc\\red.jpg");
			}
			else
				curcolorImage = cvLoadImage("etc\\red.jpg");

			DrawImage.CopyOf(color);
			DrawImage.DrawToHDC(colorhdc, rect_color);

			CString Imagename = Imagefilename[count];
			CString Imagetitle = Imagefiletitle[count];
	
			int pathlen = Imagepath.GetLength() - Imagetitle.GetLength();
			CString newpath = Imagepath.Left(pathlen);
			int extlen = Imagetitle.GetLength() - Imagename.GetLength();
			CString ex = Imagetitle.Right(extlen);
	
			Imagename += "(��)";
			Imagename += ex;
			newpath += Imagename;
			printf("%s\n", newpath);
			movefile.Remove(Imagepath);
			cvSaveImage(newpath, Image);
			cvReleaseImage(&Image);
			cvReleaseImage(&color);
		}

		count++;
		CString showcount;
		showcount.Format("%d", count);
		GetDlgItem(IDC_NOWFILE)->SetWindowTextA(showcount);
		if(count < (int)Imagefilepath.size())
		{
			Imagepath = Imagefilepath[count];
			m_picname = Imagefiletitle[count];
			m_picnameShow->SetWindowTextA(m_picname);

			if(curshowImage != NULL)
			{ 
				cvReleaseImage(&curshowImage);
				curshowImage = cvLoadImage(Imagepath);
			}
			else
				curshowImage = cvLoadImage(Imagepath);

			DrawImage.Load(Imagepath);
			DrawImage.DrawToHDC(showhdc, rect_showpic);

			getcolor = GetImagecolor(Imagepath);
			if(getcolor)
			{
				GetDlgItem(IDC_NEXT)->EnableWindow(TRUE);
				GetDlgItem(IDC_BLACK)->EnableWindow(TRUE);
				GetDlgItem(IDC_WHITE)->EnableWindow(TRUE);
				GetDlgItem(IDC_YELLOW)->EnableWindow(TRUE);
				GetDlgItem(IDC_BLUE)->EnableWindow(TRUE);
				GetDlgItem(IDC_GREEN)->EnableWindow(TRUE);
				GetDlgItem(IDC_RED)->EnableWindow(TRUE);
				GetDlgItem(IDC_SILVERY)->EnableWindow(TRUE);
				GetDlgItem(IDC_BROWN)->EnableWindow(TRUE);
			}
			else
			{
				GetDlgItem(IDC_NEXT)->EnableWindow(FALSE);
				GetDlgItem(IDC_BLACK)->EnableWindow(TRUE);
				GetDlgItem(IDC_WHITE)->EnableWindow(TRUE);
				GetDlgItem(IDC_YELLOW)->EnableWindow(TRUE);
				GetDlgItem(IDC_BLUE)->EnableWindow(TRUE);
				GetDlgItem(IDC_GREEN)->EnableWindow(TRUE);
				GetDlgItem(IDC_RED)->EnableWindow(TRUE);
				GetDlgItem(IDC_SILVERY)->EnableWindow(TRUE);
				GetDlgItem(IDC_BROWN)->EnableWindow(TRUE);
			}
		}
		else
			return;
	}
}


void CColorRecDlg::OnBnClickedSilvery()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(count >= (int)Imagefilepath.size())
	{
		MessageBox("ͼƬ��ע��ϣ�");
		return;
	}
	else
	{
		if(getcolor)
		{
			string imgColor;
			string imagePath = Imagepath.GetBuffer(0);
			printf("%s\n", Imagepath);
			imagePath.erase(imagePath.find_last_of("(")+1, 2);
			imagePath.insert(imagePath.find_last_of("(")+1, "��");

			IplImage *Image = cvLoadImage(Imagepath);
			IplImage *color = cvLoadImage("etc\\silvery.jpg");

			if(curcolorImage != NULL)
			{ 
				cvReleaseImage(&curcolorImage);
				curcolorImage = cvLoadImage("etc\\silvery.jpg");
			}
			else
				curcolorImage = cvLoadImage("etc\\silvery.jpg");

			DrawImage.CopyOf(color);
			DrawImage.DrawToHDC(colorhdc, rect_color);
			movefile.Remove(Imagepath);
			printf("%s\n", imagePath.c_str());
			cvSaveImage(imagePath.c_str(), Image);
			cvReleaseImage(&Image);
			cvReleaseImage(&color);
		}
		else
		{
			IplImage *Image = cvLoadImage(Imagepath);
			IplImage *color = cvLoadImage("etc\\silvery.jpg");

			if(curcolorImage != NULL)
			{ 
				cvReleaseImage(&curcolorImage);
				curcolorImage = cvLoadImage("etc\\silvery.jpg");
			}
			else
				curcolorImage = cvLoadImage("etc\\silvery.jpg");

			DrawImage.CopyOf(color);
			DrawImage.DrawToHDC(colorhdc, rect_color);

			CString Imagename = Imagefilename[count];
			CString Imagetitle = Imagefiletitle[count];
		
			int pathlen = Imagepath.GetLength() - Imagetitle.GetLength();
			CString newpath = Imagepath.Left(pathlen);
			int extlen = Imagetitle.GetLength() - Imagename.GetLength();
			CString ex = Imagetitle.Right(extlen);
	
			Imagename += "(��)";
			Imagename += ex;
			newpath += Imagename;
			printf("%s\n", newpath);
			movefile.Remove(Imagepath);
			cvSaveImage(newpath, Image);
			cvReleaseImage(&Image);
			cvReleaseImage(&color);
		}

		count++;
		CString showcount;
		showcount.Format("%d", count);
		GetDlgItem(IDC_NOWFILE)->SetWindowTextA(showcount);
		if(count < (int)Imagefilepath.size())
		{
			Imagepath = Imagefilepath[count];
			m_picname = Imagefiletitle[count];
			m_picnameShow->SetWindowTextA(m_picname);

			if(curshowImage != NULL)
			{ 
				cvReleaseImage(&curshowImage);
				curshowImage = cvLoadImage(Imagepath);
			}
			else
				curshowImage = cvLoadImage(Imagepath);

			DrawImage.Load(Imagepath);
			DrawImage.DrawToHDC(showhdc, rect_showpic);

			getcolor = GetImagecolor(Imagepath);
			if(getcolor)
			{
				GetDlgItem(IDC_NEXT)->EnableWindow(TRUE);
				GetDlgItem(IDC_BLACK)->EnableWindow(TRUE);
				GetDlgItem(IDC_WHITE)->EnableWindow(TRUE);
				GetDlgItem(IDC_YELLOW)->EnableWindow(TRUE);
				GetDlgItem(IDC_BLUE)->EnableWindow(TRUE);
				GetDlgItem(IDC_GREEN)->EnableWindow(TRUE);
				GetDlgItem(IDC_RED)->EnableWindow(TRUE);
				GetDlgItem(IDC_SILVERY)->EnableWindow(TRUE);
				GetDlgItem(IDC_BROWN)->EnableWindow(TRUE);
			}
			else
			{
				GetDlgItem(IDC_NEXT)->EnableWindow(FALSE);
				GetDlgItem(IDC_BLACK)->EnableWindow(TRUE);
				GetDlgItem(IDC_WHITE)->EnableWindow(TRUE);
				GetDlgItem(IDC_YELLOW)->EnableWindow(TRUE);
				GetDlgItem(IDC_BLUE)->EnableWindow(TRUE);
				GetDlgItem(IDC_GREEN)->EnableWindow(TRUE);
				GetDlgItem(IDC_RED)->EnableWindow(TRUE);
				GetDlgItem(IDC_SILVERY)->EnableWindow(TRUE);
				GetDlgItem(IDC_BROWN)->EnableWindow(TRUE);
			}
		}
		else
			return;
	}
}


void CColorRecDlg::OnBnClickedWhite()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(count >= (int)Imagefilepath.size())
	{
		MessageBox("ͼƬ��ע��ϣ�");
		return;
	}
	else
	{
		if(getcolor)
		{
			string imgColor;
			string imagePath = Imagepath.GetBuffer(0);
			printf("%s\n", Imagepath);
			imagePath.erase(imagePath.find_last_of("(")+1, 2);
			imagePath.insert(imagePath.find_last_of("(")+1, "��");

			IplImage *Image = cvLoadImage(Imagepath);
			IplImage *color = cvLoadImage("etc\\white.jpg");

			if(curcolorImage != NULL)
			{
				cvReleaseImage(&curcolorImage);
				curcolorImage = cvLoadImage("etc\\white.jpg");
			}
			else
				curcolorImage = cvLoadImage("etc\\white.jpg");

			DrawImage.CopyOf(color);
			DrawImage.DrawToHDC(colorhdc, rect_color);
			movefile.Remove(Imagepath);
			printf("%s\n", imagePath.c_str());
			cvSaveImage(imagePath.c_str(), Image);
			cvReleaseImage(&Image);
			cvReleaseImage(&color);
		}
		else
		{
			IplImage *Image = cvLoadImage(Imagepath);
			IplImage *color = cvLoadImage("etc\\white.jpg");

			if(curcolorImage != NULL)
			{
				cvReleaseImage(&curcolorImage);
				curcolorImage = cvLoadImage("etc\\white.jpg");
			}
			else
				curcolorImage = cvLoadImage("etc\\white.jpg");

			DrawImage.CopyOf(color);
			DrawImage.DrawToHDC(colorhdc, rect_color);

			CString Imagename = Imagefilename[count];
			CString Imagetitle = Imagefiletitle[count];
	
			int pathlen = Imagepath.GetLength() - Imagetitle.GetLength();
			CString newpath = Imagepath.Left(pathlen);
			int extlen = Imagetitle.GetLength() - Imagename.GetLength();
			CString ex = Imagetitle.Right(extlen);
	
			Imagename += "(��)";
			Imagename += ex;
			newpath += Imagename;
			printf("%s\n", newpath);
			movefile.Remove(Imagepath);
			cvSaveImage(newpath, Image);
			cvReleaseImage(&Image);
			cvReleaseImage(&color);
		}

		count++;
		CString showcount;
		showcount.Format("%d", count);
		GetDlgItem(IDC_NOWFILE)->SetWindowTextA(showcount);
		if(count < (int)Imagefilepath.size())
		{
			Imagepath = Imagefilepath[count];
			m_picname = Imagefiletitle[count];
			m_picnameShow->SetWindowTextA(m_picname);

			if(curshowImage != NULL)
			{
				cvReleaseImage(&curshowImage);
				curshowImage = cvLoadImage(Imagepath);
			}
			else
				curshowImage = cvLoadImage(Imagepath);

			DrawImage.Load(Imagepath);
			DrawImage.DrawToHDC(showhdc, rect_showpic);

			getcolor = GetImagecolor(Imagepath);
			if(getcolor)
			{
				GetDlgItem(IDC_NEXT)->EnableWindow(TRUE);
				GetDlgItem(IDC_BLACK)->EnableWindow(TRUE);
				GetDlgItem(IDC_WHITE)->EnableWindow(TRUE);
				GetDlgItem(IDC_YELLOW)->EnableWindow(TRUE);
				GetDlgItem(IDC_BLUE)->EnableWindow(TRUE);
				GetDlgItem(IDC_GREEN)->EnableWindow(TRUE);
				GetDlgItem(IDC_RED)->EnableWindow(TRUE);
				GetDlgItem(IDC_SILVERY)->EnableWindow(TRUE);
				GetDlgItem(IDC_BROWN)->EnableWindow(TRUE);
			}
			else
			{
				GetDlgItem(IDC_NEXT)->EnableWindow(FALSE);
				GetDlgItem(IDC_BLACK)->EnableWindow(TRUE);
				GetDlgItem(IDC_WHITE)->EnableWindow(TRUE);
				GetDlgItem(IDC_YELLOW)->EnableWindow(TRUE);
				GetDlgItem(IDC_BLUE)->EnableWindow(TRUE);
				GetDlgItem(IDC_GREEN)->EnableWindow(TRUE);
				GetDlgItem(IDC_RED)->EnableWindow(TRUE);
				GetDlgItem(IDC_SILVERY)->EnableWindow(TRUE);
				GetDlgItem(IDC_BROWN)->EnableWindow(TRUE);
			}
		}
		else
			return;
	}
}


void CColorRecDlg::OnBnClickedBrown()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(count >= (int)Imagefilepath.size())
	{
		MessageBox("ͼƬ��ע��ϣ�");
		return;
	}
	else
	{
		if(getcolor)
		{
			string imgColor;
			string imagePath = Imagepath.GetBuffer(0);
			printf("%s\n", Imagepath);
			imagePath.erase(imagePath.find_last_of("(")+1, 2);
			imagePath.insert(imagePath.find_last_of("(")+1, "��");

			IplImage *Image = cvLoadImage(Imagepath);
			IplImage *color = cvLoadImage("etc\\brown.jpg");

			if(curcolorImage != NULL)
			{
				cvReleaseImage(&curcolorImage);
				curcolorImage = cvLoadImage("etc\\brown.jpg");
			}
			else
				curcolorImage = cvLoadImage("etc\\brown.jpg");

			DrawImage.CopyOf(color);
			DrawImage.DrawToHDC(colorhdc, rect_color);
			movefile.Remove(Imagepath);
			printf("%s\n", imagePath.c_str());
			cvSaveImage(imagePath.c_str(), Image);
			cvReleaseImage(&Image);
			cvReleaseImage(&color);
		}
		else
		{
			IplImage *Image = cvLoadImage(Imagepath);
			IplImage *color = cvLoadImage("etc\\brown.jpg");

			if(curcolorImage != NULL)
			{
				cvReleaseImage(&curcolorImage);
				curcolorImage = cvLoadImage("etc\\brown.jpg");
			}
			else
				curcolorImage = cvLoadImage("etc\\brown.jpg");
			DrawImage.CopyOf(color);
			DrawImage.DrawToHDC(colorhdc, rect_color);
			CString Imagename = Imagefilename[count];
			CString Imagetitle = Imagefiletitle[count];
	
			int pathlen = Imagepath.GetLength() - Imagetitle.GetLength();
			CString newpath = Imagepath.Left(pathlen);
			int extlen = Imagetitle.GetLength() - Imagename.GetLength();
			CString ex = Imagetitle.Right(extlen);
	
			Imagename += "(��)";
			Imagename += ex;
			newpath += Imagename;
			movefile.Remove(Imagepath);
			printf("%s\n", newpath);
			cvSaveImage(newpath, Image);
			cvReleaseImage(&Image);
			cvReleaseImage(&color);
		}

		count++;
		CString showcount;
		showcount.Format("%d", count);
		GetDlgItem(IDC_NOWFILE)->SetWindowTextA(showcount);
		if(count < (int)Imagefilepath.size())
		{
			Imagepath = Imagefilepath[count];
			m_picname = Imagefiletitle[count];
			m_picnameShow->SetWindowTextA(m_picname);

			if(curshowImage != NULL)
			{
				cvReleaseImage(&curshowImage);
				curshowImage = cvLoadImage(Imagepath);
			}
			else
				curshowImage = cvLoadImage(Imagepath);

			DrawImage.Load(Imagepath);
			DrawImage.DrawToHDC(showhdc, rect_showpic);

			getcolor = GetImagecolor(Imagepath);
			if(getcolor)
			{
				GetDlgItem(IDC_NEXT)->EnableWindow(TRUE);
				GetDlgItem(IDC_BLACK)->EnableWindow(TRUE);
				GetDlgItem(IDC_WHITE)->EnableWindow(TRUE);
				GetDlgItem(IDC_YELLOW)->EnableWindow(TRUE);
				GetDlgItem(IDC_BLUE)->EnableWindow(TRUE);
				GetDlgItem(IDC_GREEN)->EnableWindow(TRUE);
				GetDlgItem(IDC_RED)->EnableWindow(TRUE);
				GetDlgItem(IDC_SILVERY)->EnableWindow(TRUE);
				GetDlgItem(IDC_BROWN)->EnableWindow(TRUE);
			}
			else
			{
				GetDlgItem(IDC_NEXT)->EnableWindow(FALSE);
				GetDlgItem(IDC_BLACK)->EnableWindow(TRUE);
				GetDlgItem(IDC_WHITE)->EnableWindow(TRUE);
				GetDlgItem(IDC_YELLOW)->EnableWindow(TRUE);
				GetDlgItem(IDC_BLUE)->EnableWindow(TRUE);
				GetDlgItem(IDC_GREEN)->EnableWindow(TRUE);
				GetDlgItem(IDC_RED)->EnableWindow(TRUE);
				GetDlgItem(IDC_SILVERY)->EnableWindow(TRUE);
				GetDlgItem(IDC_BROWN)->EnableWindow(TRUE);
			}
		}
		else
			return;
	}
}


void CColorRecDlg::OnBnClickedNext()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	count++;

	if(count < (int)Imagefilepath.size())
	{
		CString showcount;
		showcount.Format("%d", count+1);
		GetDlgItem(IDC_NOWFILE)->SetWindowTextA(showcount);

		Imagepath = Imagefilepath[count];
		m_picname = Imagefiletitle[count];
		m_picnameShow->SetWindowTextA(m_picname);

		if(curshowImage != NULL)
		{
			cvReleaseImage(&curshowImage);
			curshowImage = cvLoadImage(Imagepath);
		}
		else
			curshowImage = cvLoadImage(Imagepath);

		DrawImage.Load(Imagepath);
		DrawImage.DrawToHDC(showhdc, rect_showpic);

		getcolor = GetImagecolor(Imagepath);
		if(getcolor)
		{
			GetDlgItem(IDC_NEXT)->EnableWindow(TRUE);
			GetDlgItem(IDC_BLACK)->EnableWindow(TRUE);
			GetDlgItem(IDC_WHITE)->EnableWindow(TRUE);
			GetDlgItem(IDC_YELLOW)->EnableWindow(TRUE);
			GetDlgItem(IDC_BLUE)->EnableWindow(TRUE);
			GetDlgItem(IDC_GREEN)->EnableWindow(TRUE);
			GetDlgItem(IDC_RED)->EnableWindow(TRUE);
			GetDlgItem(IDC_SILVERY)->EnableWindow(TRUE);
			GetDlgItem(IDC_BROWN)->EnableWindow(TRUE);
		}
		else
		{
			GetDlgItem(IDC_NEXT)->EnableWindow(FALSE);
			GetDlgItem(IDC_BLACK)->EnableWindow(TRUE);
			GetDlgItem(IDC_WHITE)->EnableWindow(TRUE);
			GetDlgItem(IDC_YELLOW)->EnableWindow(TRUE);
			GetDlgItem(IDC_BLUE)->EnableWindow(TRUE);
			GetDlgItem(IDC_GREEN)->EnableWindow(TRUE);
			GetDlgItem(IDC_RED)->EnableWindow(TRUE);
			GetDlgItem(IDC_SILVERY)->EnableWindow(TRUE);
			GetDlgItem(IDC_BROWN)->EnableWindow(TRUE);
		}
	}
	else
	{
		MessageBox("ͼƬ��ע��ϣ�");
	}
}


void CColorRecDlg::OnBnClickedSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	ShellExecute(NULL, _T("open"), _T(filepath), NULL, NULL, SW_SHOW);
}


void CColorRecDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(MessageBoxA("ȷ��Ҫ�˳���", "�˳�����", MB_YESNO) == IDYES)
	{
		DrawImage.Destroy();
		CColorRecDlg::OnCancel();
	}
}


void CColorRecDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	DrawImage.Destroy();

	CDialogEx::OnClose();
}
