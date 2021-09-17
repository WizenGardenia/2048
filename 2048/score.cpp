// score.cpp : 实现文件
//

#include "stdafx.h"
#include "2048.h"
#include "score.h"
#include "afxdialogex.h"


// score 对话框

IMPLEMENT_DYNAMIC(score, CDialogEx)

score::score(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG2, pParent)
	, m_score1(0)
	, m_score2(0)
	, m_score3(0)
{

}

score::~score()
{
}

void score::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SCORE1, m_score1);
	DDX_Text(pDX, IDC_SCORE2, m_score2);
	DDX_Text(pDX, IDC_SCORE3, m_score3);
}


BEGIN_MESSAGE_MAP(score, CDialogEx)
	ON_EN_CHANGE(IDC_EDIT3, &score::OnEnChangeEdit3)
END_MESSAGE_MAP()


// score 消息处理程序


void score::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
