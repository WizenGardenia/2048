// WelcomeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "2048.h"
#include "WelcomeDlg.h"
#include "afxdialogex.h"
#include "2048Dlg.h"
#include "MyRect.h"
#include "TipDlg.h"
#include "VolDlg.h"


// WelcomeDlg 对话框

IMPLEMENT_DYNAMIC(WelcomeDlg, CDialogEx)

WelcomeDlg::WelcomeDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

WelcomeDlg::~WelcomeDlg()
{
}

void WelcomeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(WelcomeDlg, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &WelcomeDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &WelcomeDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, &WelcomeDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// WelcomeDlg 消息处理程序


void WelcomeDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void WelcomeDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CMy2048Dlg dlg;

	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此放置处理何时用
		//  “确定”来关闭对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用
		//  “取消”来关闭对话框的代码
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
		TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	}
	CDialogEx::OnOK();
}


void WelcomeDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: 在此添加控件通知处理程序代码
	INT_PTR nRes;             // 用于保存DoModal函数的返回值   

	CTipDlg tipDlg;           // 构造对话框类CTipDlg的实例   
	nRes = tipDlg.DoModal();  // 弹出对话框   
	if (IDCANCEL == nRes)     // 判断对话框退出后返回值是否为IDCANCEL，如果是则return，否则继续向下执行   
		return;
}
