#pragma once
#include "afxcmn.h"


// CVolDlg 对话框

class CVolDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CVolDlg)

public:
	CVolDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CVolDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_VOL_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	CSliderCtrl m_slider;
	int m_int;
	afx_msg void OnEnChangevolume();
	afx_msg void OnBnClickedCancel();
	
};

DWORD setVolume(DWORD vol);