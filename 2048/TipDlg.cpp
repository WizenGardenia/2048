// TipDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "2048.h"
#include "TipDlg.h"
#include "afxdialogex.h"


// CTipDlg �Ի���

IMPLEMENT_DYNAMIC(CTipDlg, CDialogEx)

CTipDlg::CTipDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_HELP, pParent)
	, str_Tip(_T("��������Ϸ����ʼ��Ϸ��ʹ���������ҷ�����ϳ����֣���ϳɸ��ߵ�����Ŭ�����м��޲�ͬ���ֵ��������ֿ��Խ��кϳ�"))
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


// CTipDlg ��Ϣ�������


void CTipDlg::OnStnClickedStaticHelp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CTipDlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������

}
