#pragma once


// score �Ի���

class score : public CDialogEx
{
	DECLARE_DYNAMIC(score)

public:
	score(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~score();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit3();
	int m_score1;
	int m_score2;
	int m_score3;
};
