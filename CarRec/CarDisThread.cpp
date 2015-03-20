#include "stdafx.h"
#include "CarDisThread.h"
#include "resource.h"

CCarDisThread::CCarDisThread()
{
	imgSrc = NULL;
}

CCarDisThread::~CCarDisThread()
{
	
}

bool CCarDisThread::InitalizeCar(CString pathSrc, HDC hdc, CRect rect, CProgressCtrl *ProgCtrl, CEdit *EditCtrl, CEdit *EditInput, CEdit *EditControlTime, CButton *open, CButton *proc, CStatic *text, CStatic *textfilecount, CStatic *textcorrect, CStatic *textalreadcount, CStatic *textcorrectcount)
{
	imgSize = cvSize(320, 240);
	totalTime = 0;
	m_correct = true;

	m_pathSrc = pathSrc;
	hdc_pic = hdc;
	m_rectImage = rect;
	m_ProgCtrl = ProgCtrl;
	m_editCtrl = EditCtrl;
	m_editInput = EditInput;
	m_editControlTime = EditControlTime;
	m_open = open;
	m_proc = proc;

	m_text = text;
	m_textfilecount = textfilecount;
	m_textcorrect = textcorrect;
	m_textalreadcount = textalreadcount;
	m_textcorrectcount = textcorrectcount;

	param = NULL;
	m_model = "etc\\vehicle.model";
	m_ret = FrPStateInitialize(m_model, &param);
	
	return m_ret;
}

void CCarDisThread::CountPicBatch(string src)
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = NULL;
	string str = src + "\\*.*";
	hFind = FindFirstFile(str.c_str(), &FindFileData);
	if(hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			string filename = FindFileData.cFileName;
			string next = src + "\\" + filename;
			if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if(filename[0] != '.')
					CountPicBatch(next);
			}
			else if(filename.find(".jpg") != -1 || filename.find(".bmp") != -1 || filename.find(".png") != -1)
			{
				picCount++;
			}
		}while(FindNextFile(hFind, &FindFileData) != 0);
	}
	FindClose(hFind);
}

void CCarDisThread::ProgressOne(string Src, string ImageName)
{
	if(imgSrc != NULL) cvReleaseImage(&imgSrc);
	imgSrc = cvLoadImage(Src.c_str());
	IplImage *image = cvCreateImage(imgSize, 8, 3);
	cvResize(imgSrc, image);
	IplImage *gray = cvCreateImage(imgSize, 8, 1);
	cvCvtColor(image, gray, CV_BGR2GRAY);
	char strOut[256];
	char correctproc[128];
	char correct[128];

	DrawImage.CopyOf(imgSrc, 1);
	DrawImage.DrawToHDC(hdc_pic, m_rectImage);
	//Sleep(100);

	begin = GetTickCount();
	int res = FrPStateDiscriminate(gray->imageData, param, imgSize.width, imgSize.height);
	end = GetTickCount();
	int last = end - begin;
	totalTime += last;
	if(res == -1)
	{
		;
	}
	else
	{
		//ʶ��������
		string indicator, predict_label, ground_truth;
		predict_label = (res == 0)? "��" : "��";
		if(Src.find_last_of("(") == -1 || Src.find_last_of(")") == -1)
			indicator = "�ޱ�ע";
		else
		{
			ground_truth = Src.substr(Src.find_last_of("(")+1, Src.find_last_of(")")-Src.find_last_of("(")-1);
			if(ground_truth == "��" || ground_truth == "��")
			{
				if(ground_truth == predict_label)
				{
					picCountCorrect++;
					indicator = "��ȷ";
				}
				else
				{
					indicator = "����";
				}
			}

			if(indicator == "�ޱ�ע" || indicator.length() == 0)
			{
				m_correct = false;
				sprintf(correctproc, "%s", "--");
				m_textcorrectcount->SetWindowTextA(correctproc);

				sprintf(correct, "%s", "--");
				m_textcorrect->SetWindowTextA(correct);

				sprintf(strOut, "%s %s %s\r\n", ImageName.c_str(), predict_label.c_str(), "δ��ע");
				nLength = m_editCtrl->SendMessage(WM_GETTEXTLENGTH);
				m_editCtrl->SetSel(nLength, nLength);
				m_editCtrl->ReplaceSel(strOut);
				//m_editCtrl->SetWindowTextA(m_editshow);
				m_editCtrl->LineScroll(m_editCtrl->GetLineCount());
			}
			else
			{
				//m_correct = true;
				sprintf(correctproc, "%d", picCountCorrect);
				m_textcorrectcount->SetWindowTextA(correctproc);

				sprintf(correct, "%0.2lf%%", (double)picCountCorrect/procCount*100);
				m_textcorrect->SetWindowTextA(correct);

				printf("%s %s %s\n", Src.c_str(), predict_label.c_str(), indicator.c_str());
				sprintf(strOut, "%s %s %s\r\n", ImageName.c_str(), predict_label.c_str(), indicator.c_str());

				//m_editshow += strOut;
				//SetWindowTextA(hwnd_edit, m_editshow);
				nLength = m_editCtrl->SendMessage(WM_GETTEXTLENGTH);
				m_editCtrl->SetSel(nLength, nLength);
				m_editCtrl->ReplaceSel(strOut);
				//m_editCtrl->SetWindowTextA(m_editshow);
				m_editCtrl->LineScroll(m_editCtrl->GetLineCount());
			}
		}
	}

	cvReleaseImage(&image);
	cvReleaseImage(&gray);
}

void CCarDisThread::ProgressBatch(string Src)
{
	m_nMin = 1;
	m_nMax = picCount;
	m_ProgCtrl->SetStep(1);
	m_ProgCtrl->SetPos(1);
	m_ProgCtrl->SetRange(m_nMin, m_nMax);
	int CurPos;
	CString progNum;
	CString PerTime;
	char countproc[128];
	m_editControlTime->GetWindowTextA(PerTime);

	if(PerTime.GetLength() == 0)
	{
		m_pertime = 0;
	}
	else
	{
		m_pertime = atoi(PerTime);
	}
	printf("%dms\n", m_pertime);

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = NULL;
	string str = Src + "\\*.*";
	hFind = FindFirstFile(str.c_str(), &FindFileData);
	if(hFind != INVALID_HANDLE_VALUE)
	{
		do
		{
			string filename = FindFileData.cFileName;
			string next = Src + "\\" + filename;
			if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if(filename[0] != '.')
				{
					ProgressBatch(next);
				}
			}
			else if(filename.find(".jpg") != -1 || filename.find(".bmp") != -1 || filename.find(".png") != -1)
			{
				procCount++;
				ProgressOne(next, filename);

				Sleep(m_pertime);
				sprintf(countproc, "%d", procCount);
				m_textalreadcount->SetWindowTextA(countproc);

				CurPos = m_ProgCtrl->GetPos();
				int showStatic = CurPos*100 / (m_nMax - 0);
				progNum.Format("%d", showStatic);
				progNum += "%";
				m_text->SetWindowTextA(progNum);
				CurPos += 1;
				m_ProgCtrl->SetPos(CurPos);

			}

		}while(FindNextFile(hFind,&FindFileData) != 0);
	}
	FindClose(hFind);
}

void CCarDisThread::Run(string dir)
{
	procCount = 0;
	picCount = 0;
	picCountCorrect = 0;

	if(access(dir.c_str(), 0) == -1)
	{
		char ptr[128] = "++++++++++++++++++++++++++++++++\r\n �ļ��в����ڣ�������ѡ��\r\n ++++++++++++++++++++++++++++++++\r\n";
		printf("file/dir not exist\n");
		//m_editshow += "++++++++++++++++++++++++++++++++\r\n";
		//m_editshow += ptr;
		//m_editshow += "++++++++++++++++++++++++++++++++\r\n";
		nLength = m_editCtrl->SendMessage(WM_GETTEXTLENGTH);
		m_editCtrl->SetSel(nLength, nLength);
		m_editCtrl->ReplaceSel(ptr);
		//m_editCtrl->SetWindowTextA(m_editshow);
		m_editCtrl->LineScroll(m_editCtrl->GetLineCount());

		m_editCtrl->EnableWindow(TRUE);
		m_open->EnableWindow(TRUE);
		m_proc->EnableWindow(TRUE);
		m_editInput->EnableWindow(TRUE);
		m_editControlTime->EnableWindow(TRUE);
		
		return;
	}

	if(dir.find(".jpg") != -1 || dir.find(".bmp") != -1 || dir.find(".png") != -1)
	{
		picCount = 1;
		printf("��ͼƬ��:%d\n", picCount);

		//imgSize = cvSize(320, 240);
		//param = NULL;
		//char *model = "etc\\vehicle,model";
		int cnt = 0;
		//bool ret = FrPStateInitialize(model, &param);

		if(m_ret)
		{
			printf("%s", dir.c_str());
			IplImage *imgSrc = cvLoadImage(dir.c_str());
			IplImage *image = cvCreateImage(imgSize, 8, 3);
			cvResize(imgSrc, image);
			IplImage *gray = cvCreateImage(imgSize, 8, 1);
			cvCvtColor(image, gray, CV_BGR2GRAY);

			int res = FrPStateDiscriminate(gray->imageData, param, imgSize.width, imgSize.height);
			printf("�б���:%d\n",res);

			FrPStateDestroy(&param);

			cvReleaseImage(&imgSrc);
			cvReleaseImage(&image);
			cvReleaseImage(&gray);
		}
	}
	else
	{
		CountPicBatch(dir);
		printf("��ͼƬ��:%d\n", picCount);
		char resultPtr[128];
		char time[128];
		char CountPic[128];
		char pertime[128];
		sprintf(CountPic, "%d", picCount);
		m_textfilecount->SetWindowTextA(CountPic);

		//imgSize = cvSize(320, 240);
		//param = NULL;
		//char *model = "etc\\vehicle.model";
		//bool ret = FrPStateInitialize(model, &param);

		if(m_ret)
		{
			CString ptr1 = "����ʶ��ʼ...\r\n";
			//CString ptr2 = "����ʶ�����...\r\n";
			ptr1 += "+++++++++++++++++++++++++++++++++\r\n";
			//char *ptr1 = "����ʶ��ʼ...\r\n";
			//char *ptr2 = "����ʶ�����...\r\n";
			//m_editshow += ptr1;
			//m_editshow += "+++++++++++++++++++++++++++++++\r\n";
			//SetWindowTextA(hwnd_edit, m_editshow);
			nLength = m_editCtrl->SendMessage(WM_GETTEXTLENGTH);
			m_editCtrl->SetSel(nLength, nLength);
			m_editCtrl->ReplaceSel(ptr1);
			//m_editCtrl->SetWindowTextA(m_editshow);
			m_editCtrl->LineScroll(m_editCtrl->GetLineCount());
			
			ProgressBatch(dir);

			CString ptr2 = "+++++++++++++++++++++++++++++++++\r\n";
			ptr2 += "����ʶ�����...\r\n";
			//m_editshow += "++++++++++++++++++++++++++++++++\r\n";
			//m_editshow += ptr2;
			//SetWindowTextA(hwnd_edit, m_editshow);
			//m_editCtrl->SetWindowTextA(m_editshow);
			nLength = m_editCtrl->SendMessage(WM_GETTEXTLENGTH);
			m_editCtrl->SetSel(nLength, nLength);
			m_editCtrl->ReplaceSel(ptr2);
			m_editCtrl->LineScroll(m_editCtrl->GetLineCount());

			if(picCount != 0)
			{
				sprintf(time, "#��ͼƬ��: %d ����ʱ: %dms\r\n",picCount, totalTime);
				//m_editshow += time;
				//m_editCtrl->SetWindowTextA(m_editshow);
			    nLength = m_editCtrl->SendMessage(WM_GETTEXTLENGTH);
				m_editCtrl->SetSel(nLength, nLength);
				m_editCtrl->ReplaceSel(time);
				m_editCtrl->LineScroll(m_editCtrl->GetLineCount());

				sprintf(time, "#ƽ��ÿ��ͼƬ��ʱ: %0.2lfms\r\n", (double)totalTime/picCount);
				//m_editshow += time;
				//m_editCtrl->SetWindowTextA(m_editshow);
				int nLength_4 = m_editCtrl->SendMessage(WM_GETTEXTLENGTH);
				m_editCtrl->SetSel(nLength, nLength);
				m_editCtrl->ReplaceSel(time);
				m_editCtrl->LineScroll(m_editCtrl->GetLineCount());

				sprintf(pertime, "#ÿ��ͼƬ������ʱ��: %dms\r\n", m_pertime);
				nLength = m_editCtrl->SendMessage(WM_GETTEXTLENGTH);
				m_editCtrl->SetSel(nLength, nLength);
				m_editCtrl->ReplaceSel(pertime);
				m_editCtrl->LineScroll(m_editCtrl->GetLineCount());

				if(m_correct)
				{
					printf("#ʶ��׼ȷ��:%d/%d=%lf\n", picCountCorrect, picCount, (double)picCountCorrect / picCount);
					sprintf(resultPtr, "#׼ȷ��:%d/%d=%.2lf%%\r\n", picCountCorrect, picCount, (double)picCountCorrect / picCount *100);
					//m_editshow += resultPtr;
					//m_editshow += "++++++++++++++++++++++++++++++++\r\n";
					//SetWindowTextA(hwnd_edit, m_editshow);
					//m_editCtrl->SetWindowTextA(m_editshow);
					nLength = m_editCtrl->SendMessage(WM_GETTEXTLENGTH);
					m_editCtrl->SetSel(nLength, nLength);
					m_editCtrl->ReplaceSel(resultPtr);
					m_editCtrl->LineScroll(m_editCtrl->GetLineCount());
				}
				else
				{
					sprintf(resultPtr, "#׼ȷ��:%s", "-----\r\n");
					nLength = m_editCtrl->SendMessage(WM_GETTEXTLENGTH);
					m_editCtrl->SetSel(nLength, nLength);
					m_editCtrl->ReplaceSel(resultPtr);
					m_editCtrl->LineScroll(m_editCtrl->GetLineCount());
				}
				FrPStateDestroy(&param);
			}
		}
		m_editCtrl->EnableWindow(TRUE);
		m_open->EnableWindow(TRUE);
		m_proc->EnableWindow(TRUE);
		m_editInput->EnableWindow(TRUE);
		m_editControlTime->EnableWindow(TRUE);
	}
}

DWORD CCarDisThread::ThreadMemberFunc()
{
	string filepath;
	filepath = m_pathSrc.GetBuffer(0);
	m_editCtrl->SetLimitText(-1);

	Run(filepath);

	return 0;
}