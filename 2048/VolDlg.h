#pragma once
#include "afxcmn.h"


// CVolDlg �Ի���

class CVolDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CVolDlg)

public:
	CVolDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CVolDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VOL_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_slider;
	int m_int;
	afx_msg void OnEnChangevolume();
	afx_msg void OnBnClickedCancel();
	
};

DWORD setVolume(DWORD vol);