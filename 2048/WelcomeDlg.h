#pragma once


// WelcomeDlg �Ի���

class WelcomeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(WelcomeDlg)

public:
	WelcomeDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~WelcomeDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton1();
};
