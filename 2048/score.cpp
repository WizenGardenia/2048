// score.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "2048.h"
#include "score.h"
#include "afxdialogex.h"


// score �Ի���

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


// score ��Ϣ�������


void score::OnEnChangeEdit3()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
