
// 2048Dlg.cpp : 实现文件
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

//大矩形为 LINELENGTH * LINELENGTH
#define LINELENGTH 4
#define RECTNUM (LINELENGTH*LINELENGTH)

struct MyPoint {
	int x;
	int y;
};

//实际矩形数组，面板上显示的每个矩形都是CRect类型，声明在这里
CRect *rect[LINELENGTH][LINELENGTH];

//控制是否生成新数字，为true的时候说明有动作，就会生成新数字
bool bHaveDoneSth;

//端点位置
MyPoint point[LINELENGTH][LINELENGTH] = { 0 };

//矩形对象数组，相当于逻辑部分，保存矩形的显示值，坐标
MyRect *myrect[LINELENGTH][LINELENGTH];

//填充画刷，可以控制矩形填充不同的颜色
CBrush *brush;

//生成一个新数字，随机一个0-RECTNUM的整数，根据这个整数计算出二维数组的横坐标和竖坐标
//  A/LINELENGTH 是横坐标， A%LINELENGTH 是竖坐标, 当生成的位置有值的时候，重新生成
// 初始值为2或4
void GenerateNewNum()
{
	srand(time(0));
	int A = rand() % RECTNUM;
	while (myrect[A / LINELENGTH][A%LINELENGTH]->uValue != 0)
	{
		A = rand() % RECTNUM;
	}
	//设置生成2与4的概率比为2：1
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

//判断游戏结束
bool GameOver()
{
	//如果有值为0 的矩形，则游戏肯定可以继续，所以直接返回false
	for (int i = 0; i < LINELENGTH; i++)
		for (int j = 0; j < LINELENGTH; j++)
		{
			if (myrect[i][j]->uValue == 0)
				return false;
		}
	// 对每一行相邻的两个数，如果有相同的，那么游戏可以继续，返回false
	for (int i = 0; i < LINELENGTH; i++)
		for (int j = 0; j < LINELENGTH - 1; j++)
		{
			if (myrect[i][j]->uValue == myrect[i][j + 1]->uValue)
				return false;
		}

	// 对每一列相邻的两个数，如果有相同的，那么游戏可以继续，返回false
	for (int j = 0; j < LINELENGTH; j++)
		for (int i = 0; i < LINELENGTH - 1; i++)
		{
			if (myrect[i][j]->uValue == myrect[i + 1][j]->uValue)
				return false;
		}
	return true;
}


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CMy2048Dlg 对话框



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


// CMy2048Dlg 消息处理程序

BOOL CMy2048Dlg::OnInitDialog()
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	::SetWindowPos(this->m_hWnd, HWND_BOTTOM, 0, 0, 225 + LINELENGTH * 100, 198 + LINELENGTH * 100, SWP_NOZORDER);

	//初始化每个矩形的左上角点的坐标
	for (int i = 0; i < LINELENGTH; i++)
	{
		for (int j = 0; j < LINELENGTH; j++)
		{
			point[i][j].x = j * 100 + 10;
			point[i][j].y = i * 100 + 10;
		}
	}

	//初始化矩形和填充画刷
	for (int i = 0; i < LINELENGTH; i++)
	{
		for (int j = 0; j < LINELENGTH; j++)
		{
			myrect[i][j] = new MyRect(point[i][j].x, point[i][j].y, point[i][j].x + 90, point[i][j].y + 90);
			myrect[i][j]->uValue = 0;
		}
	}




	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMy2048Dlg::OnPaint()
{

	CFont font;
	font.CreateFont(25, 25, 0, 0, 700, false, false, false,
		CHINESEBIG5_CHARSET, OUT_CHARACTER_PRECIS,
		CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY,
		FF_MODERN, TEXT("宋体"));



	//客户区设备环境
	CClientDC dc(this);
	//新建画笔
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	//选中字体
	dc.SelectObject(pen);


	for (int i = 0; i < LINELENGTH; i++)
	{
		for (int j = 0; j < LINELENGTH; j++)
		{
			//画矩形
			dc.Rectangle(myrect[i][j]->x1, myrect[i][j]->y1, myrect[i][j]->x2, myrect[i][j]->y2);
			//填充矩形
			rect[i][j] = new CRect(myrect[i][j]->x1, myrect[i][j]->y1, myrect[i][j]->x2, myrect[i][j]->y2);
			//设置文字背景透明
		    dc.SetBkMode(TRANSPARENT);
			//选中字体
			dc.SelectObject(font);
			//写数字
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
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
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

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMy2048Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}









void CMy2048Dlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	//初始化矩形和填充画刷
	for (int i = 0; i < LINELENGTH; i++)
	{
		for (int j = 0; j < LINELENGTH; j++)
		{
			myrect[i][j] = new MyRect(point[i][j].x, point[i][j].y, point[i][j].x + 90, point[i][j].y + 90);
			myrect[i][j]->uValue = 0;
		}
	}
	//初始化数字
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
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CMy2048Dlg::OnBnClickedButtonHelp()
{
	// TODO: 在此添加控件通知处理程序代码
	INT_PTR nRes;             // 用于保存DoModal函数的返回值   

	CTipDlg tipDlg;           // 构造对话框类CTipDlg的实例   
	nRes = tipDlg.DoModal();  // 弹出对话框   
	if (IDCANCEL == nRes)     // 判断对话框退出后返回值是否为IDCANCEL，如果是则return，否则继续向下执行   
		return;
}



//根据键盘消息判断执行哪个步骤
BOOL CMy2048Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
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
			//设置Q键退出
			else if (pMsg->wParam == 'Q')
			{
				OnCancel();
				return FALSE;
			}
			//N键开始
			else if (pMsg->wParam == 'N')
			{
				OnBnClickedButton1();
				return FALSE;
			}
			//S键弹出排行榜
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
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nChar)
	{
	case VK_LEFT:
		//判断是否有动作，用来控制是否生成新数字
		bHaveDoneSth = false;
		for (int i = 0; i < LINELENGTH; i++)
		{

			//去掉空格
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

			//相加
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

			//去掉空格
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
			//去掉空格
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

			//相加
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

			//去掉空格
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
			//去掉空格
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

			//相加
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

			//去掉空格
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

			//去掉空格
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

			//相加
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

			//去掉空格
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
		AfxMessageBox("游戏结束！单击“新游戏”重新开始或单击“退出游戏”按钮退出");

		//将得分写入排行榜
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
	// TODO: 在此添加控件通知处理程序代码
}





void CMy2048Dlg::OnBnClickedfilechoice()
{
	// TODO: 在此添加控件通知处理程序代码
	char szFileFilter[] = "mp3文件(*.mp3)|*.mp3|"
		"wma文件(*.wma)|*.wma|"
		"wav文件(*.wav)|*.wav|"
		"所有文件(*.*)|*.*|";
	CFileDialog dlg(true, NULL, NULL, OFN_HIDEREADONLY, szFileFilter);
	if (dlg.DoModal() == IDOK)
	{
		CString strFilepath = dlg.GetPathName();
		CString strFilename = dlg.GetFileName();
		SetDlgItemText(IDC_filename, strFilename);
		Load(this->m_hWnd, strFilepath);
	}
	GetDlgItem(IDC_play)->EnableWindow(true); //文件读取成功时所有按钮变成可选
	GetDlgItem(IDC_pause)->EnableWindow(true);
	GetDlgItem(IDC_stop)->EnableWindow(true);
}


void CMy2048Dlg::OnBnClickedplay()
{
	// TODO: 在此添加控件通知处理程序代码
	play();
	SetDlgItemText(IDC_pause, "暂停");
}


void CMy2048Dlg::OnBnClickedpause()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strTemp;
	GetDlgItemText(IDC_pause, strTemp); //获取按钮的状态
	if (strTemp.Compare("暂停") == 0)
	{
		pause();
		SetDlgItemText(IDC_pause, "恢复");
	}

	if (strTemp.Compare("恢复") == 0)
	{
		resume();
		SetDlgItemText(IDC_pause, "暂停");
	}
}


void CMy2048Dlg::OnBnClickedstop()
{
	// TODO: 在此添加控件通知处理程序代码
	stop();
	SetDlgItemText(IDC_pause, "暂停");
	GetDlgItem(IDC_play)->EnableWindow(false); //当按下stop的时候,播放和暂停不可选
	GetDlgItem(IDC_pause)->EnableWindow(false);
}

//弹出音量调节对话框
void CMy2048Dlg::OnBnClickedvol()
{
	// TODO: 在此添加控件通知处理程序代码
	INT_PTR nRes;             // 用于保存DoModal函数的返回值   

	CVolDlg VolDlg;           // 构造对话框类CVolDlg的实例   
	nRes = VolDlg.DoModal();  // 弹出对话框   
	if (IDCANCEL == nRes)     // 判断对话框退出后返回值是否为IDCANCEL，如果是则return，否则继续向下执行   
		return;
}

//弹出排行榜对话框
void CMy2048Dlg::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	INT_PTR nRes;             // 用于保存DoModal函数的返回值   

	score scoreDlg;           // 构造对话框类score的实例
	scoreDlg.m_score1 = m_score_NO1;
	scoreDlg.m_score2 = m_score_NO2;
	scoreDlg.m_score3 = m_score_NO3;
	nRes = scoreDlg.DoModal();  // 弹出对话框   
	if (IDCANCEL == nRes)     // 判断对话框退出后返回值是否为IDCANCEL，如果是则return，否则继续向下执行   
		return;
}
