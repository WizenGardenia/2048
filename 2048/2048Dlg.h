
// 2048Dlg.h : ͷ�ļ�
//

#pragma once


// CMy2048Dlg �Ի���
class CMy2048Dlg : public CDialogEx
{
// ����
public:
	CMy2048Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY2048_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	
	// �÷�
	float m_score;
	afx_msg void OnBnClickedButtonClose();
	afx_msg void OnBnClickedButtonHelp();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnBnClickedButtonBegin();
	afx_msg void OnBnClickedfilechoice();
	afx_msg void OnBnClickedplay();
	afx_msg void OnBnClickedpause();
	afx_msg void OnBnClickedstop();
	afx_msg void OnBnClickedvol();
	afx_msg void OnBnClickedButton9();
	int m_score_NO1, m_score_NO2, m_score_NO3 = 0;
};



