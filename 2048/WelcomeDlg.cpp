// WelcomeDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "2048.h"
#include "WelcomeDlg.h"
#include "afxdialogex.h"
#include "2048Dlg.h"
#include "MyRect.h"
#include "TipDlg.h"
#include "VolDlg.h"


// WelcomeDlg �Ի���

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


// WelcomeDlg ��Ϣ�������


void WelcomeDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void WelcomeDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CMy2048Dlg dlg;

	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}
	CDialogEx::OnOK();
}


void WelcomeDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	INT_PTR nRes;             // ���ڱ���DoModal�����ķ���ֵ   

	CTipDlg tipDlg;           // ����Ի�����CTipDlg��ʵ��   
	nRes = tipDlg.DoModal();  // �����Ի���   
	if (IDCANCEL == nRes)     // �ж϶Ի����˳��󷵻�ֵ�Ƿ�ΪIDCANCEL���������return�������������ִ��   
		return;
}
