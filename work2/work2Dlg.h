
// work2Dlg.h: 头文件
//

#pragma once


// Cwork2Dlg 对话框
class Cwork2Dlg : public CDialogEx
{
// 构造
public:
	Cwork2Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_WORK2_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int m_dep;
	CString m_pre;
	CString m_in;
	CString m_post;
	void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
};
