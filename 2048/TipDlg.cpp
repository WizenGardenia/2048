// TipDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "2048.h"
#include "TipDlg.h"
#include "afxdialogex.h"


// CTipDlg 对话框

IMPLEMENT_DYNAMIC(CTipDlg, CDialogEx)

CTipDlg::CTipDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_HELP, pParent)
	, str_Tip(_T("按“新游戏”开始游戏，使用上下左右方向键合成数字，向合成更高的数字努力！中间无不同数字的两个数字可以进行合成"))
{

}

CTipDlg::~CTipDlg()
{
}

void CTipDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, str_Tip);
}


BEGIN_MESSAGE_MAP(CTipDlg, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT1, &CTipDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CTipDlg 消息处理程序


void CTipDlg::OnStnClickedStaticHelp()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CTipDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码

}
