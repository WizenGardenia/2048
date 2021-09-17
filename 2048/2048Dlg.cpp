
// 2048Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "2048.h"
#include "2048Dlg.h"
#include "afxdialogex.h"
#include "MyRect.h"
#include "TipDlg.h"
#include "musicplayer.h"
#include "VolDlg.h"
#include "score.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//�����Ϊ LINELENGTH * LINELENGTH
#define LINELENGTH 4
#define RECTNUM (LINELENGTH*LINELENGTH)

struct MyPoint {
	int x;
	int y;
};

//ʵ�ʾ������飬�������ʾ��ÿ�����ζ���CRect���ͣ�����������
CRect *rect[LINELENGTH][LINELENGTH];

//�����Ƿ����������֣�Ϊtrue��ʱ��˵���ж������ͻ�����������
bool bHaveDoneSth;

//�˵�λ��
MyPoint point[LINELENGTH][LINELENGTH] = { 0 };

//���ζ������飬�൱���߼����֣�������ε���ʾֵ������
MyRect *myrect[LINELENGTH][LINELENGTH];

//��仭ˢ�����Կ��ƾ�����䲻ͬ����ɫ
CBrush *brush;

//����һ�������֣����һ��0-RECTNUM��������������������������ά����ĺ������������
//  A/LINELENGTH �Ǻ����꣬ A%LINELENGTH ��������, �����ɵ�λ����ֵ��ʱ����������
// ��ʼֵΪ2��4
void GenerateNewNum()
{
	srand(time(0));
	int A = rand() % RECTNUM;
	while (myrect[A / LINELENGTH][A%LINELENGTH]->uValue != 0)
	{
		A = rand() % RECTNUM;
	}
	//��������2��4�ĸ��ʱ�Ϊ2��1
	int B = rand() % 3;
	if (B != 2)
	{
		myrect[A / LINELENGTH][A%LINELENGTH]->uValue = 2;
	}
	else
	{
        myrect[A / LINELENGTH][A%LINELENGTH]->uValue = 4;
	}
	
}

//�ж���Ϸ����
bool GameOver()
{
	//�����ֵΪ0 �ľ��Σ�����Ϸ�϶����Լ���������ֱ�ӷ���false
	for (int i = 0; i < LINELENGTH; i++)
		for (int j = 0; j < LINELENGTH; j++)
		{
			if (myrect[i][j]->uValue == 0)
				return false;
		}
	// ��ÿһ�����ڵ����������������ͬ�ģ���ô��Ϸ���Լ���������false
	for (int i = 0; i < LINELENGTH; i++)
		for (int j = 0; j < LINELENGTH - 1; j++)
		{
			if (myrect[i][j]->uValue == myrect[i][j + 1]->uValue)
				return false;
		}

	// ��ÿһ�����ڵ����������������ͬ�ģ���ô��Ϸ���Լ���������false
	for (int j = 0; j < LINELENGTH; j++)
		for (int i = 0; i < LINELENGTH - 1; i++)
		{
			if (myrect[i][j]->uValue == myrect[i + 1][j]->uValue)
				return false;
		}
	return true;
}


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMy2048Dlg �Ի���



CMy2048Dlg::CMy2048Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MY2048_DIALOG, pParent)
	, m_score(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void CMy2048Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SCORE, m_score);
}

BEGIN_MESSAGE_MAP(CMy2048Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
	ON_WM_KEYUP()
	ON_BN_CLICKED(IDC_BUTTON1, &CMy2048Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_CLOSE, &CMy2048Dlg::OnBnClickedButtonClose)
	ON_BN_CLICKED(IDC_BUTTON_HELP, &CMy2048Dlg::OnBnClickedButtonHelp)
	ON_WM_KEYUP()
	ON_BN_CLICKED(IDC_BUTTON_BEGIN, &CMy2048Dlg::OnBnClickedButtonBegin)
	ON_BN_CLICKED(IDC_filechoice, &CMy2048Dlg::OnBnClickedfilechoice)
	ON_BN_CLICKED(IDC_play, &CMy2048Dlg::OnBnClickedplay)
	ON_BN_CLICKED(IDC_pause, &CMy2048Dlg::OnBnClickedpause)
	ON_BN_CLICKED(IDC_stop, &CMy2048Dlg::OnBnClickedstop)
	ON_BN_CLICKED(IDC_vol, &CMy2048Dlg::OnBnClickedvol)
	ON_BN_CLICKED(IDC_BUTTON9, &CMy2048Dlg::OnBnClickedButton9)
END_MESSAGE_MAP()


// CMy2048Dlg ��Ϣ�������

BOOL CMy2048Dlg::OnInitDialog()
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	::SetWindowPos(this->m_hWnd, HWND_BOTTOM, 0, 0, 225 + LINELENGTH * 100, 198 + LINELENGTH * 100, SWP_NOZORDER);

	//��ʼ��ÿ�����ε����Ͻǵ������
	for (int i = 0; i < LINELENGTH; i++)
	{
		for (int j = 0; j < LINELENGTH; j++)
		{
			point[i][j].x = j * 100 + 10;
			point[i][j].y = i * 100 + 10;
		}
	}

	//��ʼ�����κ���仭ˢ
	for (int i = 0; i < LINELENGTH; i++)
	{
		for (int j = 0; j < LINELENGTH; j++)
		{
			myrect[i][j] = new MyRect(point[i][j].x, point[i][j].y, point[i][j].x + 90, point[i][j].y + 90);
			myrect[i][j]->uValue = 0;
		}
	}




	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMy2048Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMy2048Dlg::OnPaint()
{

	CFont font;
	font.CreateFont(25, 25, 0, 0, 700, false, false, false,
		CHINESEBIG5_CHARSET, OUT_CHARACTER_PRECIS,
		CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY,
		FF_MODERN, TEXT("����"));



	//�ͻ����豸����
	CClientDC dc(this);
	//�½�����
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	//ѡ������
	dc.SelectObject(pen);


	for (int i = 0; i < LINELENGTH; i++)
	{
		for (int j = 0; j < LINELENGTH; j++)
		{
			//������
			dc.Rectangle(myrect[i][j]->x1, myrect[i][j]->y1, myrect[i][j]->x2, myrect[i][j]->y2);
			//������
			rect[i][j] = new CRect(myrect[i][j]->x1, myrect[i][j]->y1, myrect[i][j]->x2, myrect[i][j]->y2);
			//�������ֱ���͸��
		    dc.SetBkMode(TRANSPARENT);
			//ѡ������
			dc.SelectObject(font);
			//д����
			if (myrect[i][j]->uValue == 0)
			{
				brush = new CBrush(RGB(0xFC, 0xFC, 0xFC));
				dc.FillRect(rect[i][j], brush);
				delete brush;
			}
			else if (myrect[i][j]->uValue != 0)
			{
				switch (myrect[i][j]->uValue)
				{
				case 2:brush = new CBrush(RGB(0xFF, 0xFF, 0xFF)); break;
				case 4:brush = new CBrush(RGB(0xFF, 0xE4, 0xC4)); break;
				case 8:brush = new CBrush(RGB(0xFF, 0xB6, 0xC1)); break;
				case 16:brush = new CBrush(RGB(0xFF, 0x83, 0xFA)); break;
				case 32:brush = new CBrush(RGB(0xFF, 0xC1, 0x25)); break;
				case 64:brush = new CBrush(RGB(0xFF, 0x6A, 0x6A)); break;
				case 128:brush = new CBrush(RGB(0xFF, 0x14, 0x93)); break;
				case 256:brush = new CBrush(RGB(0xCD, 0x66, 0x1D)); break;
				case 512:brush = new CBrush(RGB(0x94, 0x00, 0xD3)); break;
				case 1024:brush = new CBrush(RGB(0xFF, 0xFF, 0x00)); break;
				case 2048:brush = new CBrush(RGB(0xFF, 0x00, 0x00)); break;
				default:brush = new CBrush(RGB(0xFF, 0x00, 0x00)); break;
				}
				dc.FillRect(rect[i][j], brush);
				delete brush;

				char num[10] = { '0' };
				itoa(myrect[i][j]->uValue, num, 10);
				dc.DrawText(num, -1, rect[i][j], DT_VCENTER | DT_CENTER | DT_SINGLELINE);
			}
		}
	}
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
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMy2048Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}









void CMy2048Dlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//��ʼ�����κ���仭ˢ
	for (int i = 0; i < LINELENGTH; i++)
	{
		for (int j = 0; j < LINELENGTH; j++)
		{
			myrect[i][j] = new MyRect(point[i][j].x, point[i][j].y, point[i][j].x + 90, point[i][j].y + 90);
			myrect[i][j]->uValue = 0;
		}
	}
	//��ʼ������
	srand(time(0));
	int A = rand() % RECTNUM;
	int B = rand() % RECTNUM;
	while (B == A)
	{
		B = rand() % RECTNUM;
	}
	myrect[A / LINELENGTH][A % LINELENGTH]->uValue = 2;
	myrect[B / LINELENGTH][B % LINELENGTH]->uValue = 2;
	OnPaint();
	m_score = 0;
	UpdateData(FALSE);

}



void CMy2048Dlg::OnBnClickedButtonClose()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void CMy2048Dlg::OnBnClickedButtonHelp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	INT_PTR nRes;             // ���ڱ���DoModal�����ķ���ֵ   

	CTipDlg tipDlg;           // ����Ի�����CTipDlg��ʵ��   
	nRes = tipDlg.DoModal();  // �����Ի���   
	if (IDCANCEL == nRes)     // �ж϶Ի����˳��󷵻�ֵ�Ƿ�ΪIDCANCEL���������return�������������ִ��   
		return;
}



//���ݼ�����Ϣ�ж�ִ���ĸ�����
BOOL CMy2048Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_KEYUP)
	{
		switch (pMsg->message)
		{
		case WM_KEYUP:
		{
			if (pMsg->wParam == VK_UP)
			{
				OnKeyUp(VK_UP, NULL, NULL);
				return FALSE;
			}
			else if (pMsg->wParam == VK_DOWN)
			{
				OnKeyUp(VK_DOWN, NULL, NULL);
				return FALSE;
			}
			else if (pMsg->wParam == VK_LEFT)
			{
				OnKeyUp(VK_LEFT, NULL, NULL);
				return FALSE;
			}
			else if (pMsg->wParam == VK_RIGHT)
			{
				OnKeyUp(VK_RIGHT, NULL, NULL);
				return FALSE;
			}
			//����Q���˳�
			else if (pMsg->wParam == 'Q')
			{
				OnCancel();
				return FALSE;
			}
			//N����ʼ
			else if (pMsg->wParam == 'N')
			{
				OnBnClickedButton1();
				return FALSE;
			}
			//S���������а�
			else if (pMsg->wParam == 'S')
			{
				OnBnClickedButton9();
				return FALSE;
			}

		}
		break;
		}
	}
	return FALSE;

}




void CMy2048Dlg::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nChar)
	{
	case VK_LEFT:
		//�ж��Ƿ��ж��������������Ƿ�����������
		bHaveDoneSth = false;
		for (int i = 0; i < LINELENGTH; i++)
		{

			//ȥ���ո�
			for (int j = 0; j < LINELENGTH; j++)
			{
				//
				if (myrect[i][j]->uValue != 0)
				{
					for (int k = 0; k < j; k++)
					{
						if (myrect[i][k]->uValue == 0)
						{
							bHaveDoneSth = true;
							myrect[i][k]->uValue = myrect[i][j]->uValue;
							myrect[i][j]->uValue = 0;
							break;
						}
					}
				}
			}

			//���
			for (int j = 0; j < LINELENGTH - 1; j++)
			{
				if (myrect[i][j]->uValue != 0)
				{
					if (myrect[i][j + 1]->uValue == myrect[i][j]->uValue)
					{
						bHaveDoneSth = true;
						myrect[i][j]->uValue += myrect[i][j + 1]->uValue;
						m_score = m_score + (myrect[i][j]->uValue);
						UpdateData(FALSE);
						myrect[i][j + 1]->uValue = 0;
					}
				}
			}

			//ȥ���ո�
			for (int j = 0; j < LINELENGTH; j++)
			{
				if (myrect[i][j]->uValue != 0)
				{
					for (int k = 0; k < j; k++)
					{
						if (myrect[i][k]->uValue == 0)
						{
							bHaveDoneSth = true;
							myrect[i][k]->uValue = myrect[i][j]->uValue;
							myrect[i][j]->uValue = 0;
							break;
						}
					}
				}
			}
		}
		break;
	case VK_UP:
		bHaveDoneSth = false;
		for (int j = 0; j < LINELENGTH; j++)
		{
			//ȥ���ո�
			for (int i = 0; i < LINELENGTH; i++)
			{
				//
				if (myrect[i][j]->uValue != 0)
				{
					for (int k = 0; k < i; k++)
					{
						if (myrect[k][j]->uValue == 0)
						{
							bHaveDoneSth = true;
							myrect[k][j]->uValue = myrect[i][j]->uValue;
							myrect[i][j]->uValue = 0;
							break;
						}
					}
				}
			}

			//���
			for (int i = 0; i < LINELENGTH - 1; i++)
			{
				if (myrect[i][j]->uValue != 0)
				{
					if (myrect[i + 1][j]->uValue == myrect[i][j]->uValue)
					{
						bHaveDoneSth = true;
						myrect[i][j]->uValue += myrect[i + 1][j]->uValue;
						m_score = m_score + (myrect[i][j]->uValue);
						UpdateData(FALSE);
						myrect[i + 1][j]->uValue = 0;
					}
				}
			}

			//ȥ���ո�
			for (int i = 0; i < LINELENGTH; i++)
			{
				//
				if (myrect[i][j]->uValue != 0)
				{
					for (int k = 0; k < i; k++)
					{
						if (myrect[k][j]->uValue == 0)
						{
							bHaveDoneSth = true;
							myrect[k][j]->uValue = myrect[i][j]->uValue;
							myrect[i][j]->uValue = 0;
							break;
						}
					}
				}
			}
		}

		break;
	case VK_RIGHT:
		bHaveDoneSth = false;
		for (int i = 0; i < LINELENGTH; i++)
		{
			//ȥ���ո�
			for (int j = LINELENGTH - 1; j >= 0; j--)
			{
				//
				if (myrect[i][j]->uValue != 0)
				{
					for (int k = LINELENGTH - 1; k >= j; k--)
					{
						if (myrect[i][k]->uValue == 0)
						{
							bHaveDoneSth = true;
							myrect[i][k]->uValue = myrect[i][j]->uValue;
							myrect[i][j]->uValue = 0;
							break;
						}
					}
				}
			}

			//���
			for (int j = LINELENGTH - 1; j > 0; j--)
			{
				if (myrect[i][j]->uValue != 0)
				{
					if (myrect[i][j - 1]->uValue == myrect[i][j]->uValue)
					{
						bHaveDoneSth = true;
						myrect[i][j]->uValue += myrect[i][j - 1]->uValue;
						m_score = m_score + (myrect[i][j]->uValue);
						UpdateData(FALSE);
						myrect[i][j - 1]->uValue = 0;
					}
				}
			}

			//ȥ���ո�
			for (int j = LINELENGTH - 1; j >= 0; j--)
			{
				//
				if (myrect[i][j]->uValue != 0)
				{
					for (int k = LINELENGTH - 1; k >= j; k--)
					{
						if (myrect[i][k]->uValue == 0)
						{
							bHaveDoneSth = true;
							myrect[i][k]->uValue = myrect[i][j]->uValue;
							myrect[i][j]->uValue = 0;
							break;
						}
					}
				}
			}
		}

		break;
	case VK_DOWN:
		bHaveDoneSth = false;
		for (int j = LINELENGTH - 1; j >= 0; j--)
		{

			//ȥ���ո�
			for (int i = LINELENGTH - 1; i >= 0; i--)
			{
				//
				if (myrect[i][j]->uValue != 0)
				{
					for (int k = LINELENGTH - 1; k >= i; k--)
					{
						if (myrect[k][j]->uValue == 0)
						{
							bHaveDoneSth = true;
							myrect[k][j]->uValue = myrect[i][j]->uValue;
							myrect[i][j]->uValue = 0;
							break;
						}
					}
				}
			}

			//���
			for (int i = LINELENGTH - 1; i > 0; i--)
			{
				if (myrect[i][j]->uValue != 0)
				{
					if (myrect[i - 1][j]->uValue == myrect[i][j]->uValue)
					{
						bHaveDoneSth = true;
						myrect[i][j]->uValue += myrect[i - 1][j]->uValue;
						m_score = m_score + (myrect[i][j]->uValue);
						UpdateData(FALSE);
						myrect[i - 1][j]->uValue = 0;
					}
				}
			}

			//ȥ���ո�
			for (int i = LINELENGTH - 1; i >= 0; i--)
			{
				//
				if (myrect[i][j]->uValue != 0)
				{
					for (int k = LINELENGTH - 1; k >= i; k--)
					{
						if (myrect[k][j]->uValue == 0)
						{
							bHaveDoneSth = true;
							myrect[k][j]->uValue = myrect[i][j]->uValue;
							myrect[i][j]->uValue = 0;
							break;
						}
					}
				}
			}
		}

		break;
	default:
		break;
	}

	if (bHaveDoneSth)
	{
		GenerateNewNum();
	}

	Invalidate(FALSE);
	if (GameOver())
	{
		AfxMessageBox("��Ϸ����������������Ϸ�����¿�ʼ�򵥻����˳���Ϸ����ť�˳�");

		//���÷�д�����а�
		if (m_score >= m_score_NO1)
		{
			m_score_NO3 = m_score_NO2;
			m_score_NO2 = m_score_NO1;
			m_score_NO1 = m_score;
		}
		else if (m_score >= m_score_NO2)
		{
			m_score_NO3 = m_score_NO2;
			m_score_NO2 = m_score;
		}
		else if (m_score >= m_score_NO3)
		{
			m_score_NO3 = m_score;
		}
	};
	CDialogEx::OnKeyUp(nChar, nRepCnt, nFlags);
}


void CMy2048Dlg::OnBnClickedButtonBegin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}





void CMy2048Dlg::OnBnClickedfilechoice()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	char szFileFilter[] = "mp3�ļ�(*.mp3)|*.mp3|"
		"wma�ļ�(*.wma)|*.wma|"
		"wav�ļ�(*.wav)|*.wav|"
		"�����ļ�(*.*)|*.*|";
	CFileDialog dlg(true, NULL, NULL, OFN_HIDEREADONLY, szFileFilter);
	if (dlg.DoModal() == IDOK)
	{
		CString strFilepath = dlg.GetPathName();
		CString strFilename = dlg.GetFileName();
		SetDlgItemText(IDC_filename, strFilename);
		Load(this->m_hWnd, strFilepath);
	}
	GetDlgItem(IDC_play)->EnableWindow(true); //�ļ���ȡ�ɹ�ʱ���а�ť��ɿ�ѡ
	GetDlgItem(IDC_pause)->EnableWindow(true);
	GetDlgItem(IDC_stop)->EnableWindow(true);
}


void CMy2048Dlg::OnBnClickedplay()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	play();
	SetDlgItemText(IDC_pause, "��ͣ");
}


void CMy2048Dlg::OnBnClickedpause()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strTemp;
	GetDlgItemText(IDC_pause, strTemp); //��ȡ��ť��״̬
	if (strTemp.Compare("��ͣ") == 0)
	{
		pause();
		SetDlgItemText(IDC_pause, "�ָ�");
	}

	if (strTemp.Compare("�ָ�") == 0)
	{
		resume();
		SetDlgItemText(IDC_pause, "��ͣ");
	}
}


void CMy2048Dlg::OnBnClickedstop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	stop();
	SetDlgItemText(IDC_pause, "��ͣ");
	GetDlgItem(IDC_play)->EnableWindow(false); //������stop��ʱ��,���ź���ͣ����ѡ
	GetDlgItem(IDC_pause)->EnableWindow(false);
}

//�����������ڶԻ���
void CMy2048Dlg::OnBnClickedvol()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	INT_PTR nRes;             // ���ڱ���DoModal�����ķ���ֵ   

	CVolDlg VolDlg;           // ����Ի�����CVolDlg��ʵ��   
	nRes = VolDlg.DoModal();  // �����Ի���   
	if (IDCANCEL == nRes)     // �ж϶Ի����˳��󷵻�ֵ�Ƿ�ΪIDCANCEL���������return�������������ִ��   
		return;
}

//�������а�Ի���
void CMy2048Dlg::OnBnClickedButton9()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	INT_PTR nRes;             // ���ڱ���DoModal�����ķ���ֵ   

	score scoreDlg;           // ����Ի�����score��ʵ��
	scoreDlg.m_score1 = m_score_NO1;
	scoreDlg.m_score2 = m_score_NO2;
	scoreDlg.m_score3 = m_score_NO3;
	nRes = scoreDlg.DoModal();  // �����Ի���   
	if (IDCANCEL == nRes)     // �ж϶Ի����˳��󷵻�ֵ�Ƿ�ΪIDCANCEL���������return�������������ִ��   
		return;
}
