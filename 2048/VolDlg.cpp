// VolDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "2048.h"
#include "VolDlg.h"
#include "afxdialogex.h"
#include "musicplayer.h"


// CVolDlg �Ի���

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


// CVolDlg ��Ϣ�������


void CVolDlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(true);
	m_int = m_slider.GetPos() / 10;
	setVolume(m_slider.GetPos());
	UpdateData(false);
	*pResult = 0;
}


void CVolDlg::OnEnChangevolume()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CVolDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	setVolume(m_slider.GetPos());
	CDialogEx::OnCancel();
}
