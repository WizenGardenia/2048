// VolDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "2048.h"
#include "VolDlg.h"
#include "afxdialogex.h"
#include "musicplayer.h"


// CVolDlg 对话框

IMPLEMENT_DYNAMIC(CVolDlg, CDialogEx)

CVolDlg::CVolDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_VOL_DIALOG, pParent)
	, m_int(0)
{

}

CVolDlg::~CVolDlg()
{
}

void CVolDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER1, m_slider);
	DDX_Text(pDX, IDC_volume, m_int);
}


BEGIN_MESSAGE_MAP(CVolDlg, CDialogEx)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CVolDlg::OnNMCustomdrawSlider1)
	ON_EN_CHANGE(IDC_volume, &CVolDlg::OnEnChangevolume)
	ON_BN_CLICKED(IDCANCEL, &CVolDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CVolDlg 消息处理程序


void CVolDlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(true);
	m_int = m_slider.GetPos() / 10;
	setVolume(m_slider.GetPos());
	UpdateData(false);
	*pResult = 0;
}


void CVolDlg::OnEnChangevolume()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CVolDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	setVolume(m_slider.GetPos());
	CDialogEx::OnCancel();
}
