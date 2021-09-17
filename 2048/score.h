#pragma once


// score 对话框

class score : public CDialogEx
{
	DECLARE_DYNAMIC(score)

public:
	score(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~score();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG2 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit3();
	int m_score1;
	int m_score2;
	int m_score3;
};
