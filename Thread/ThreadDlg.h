
// ThreadDlg.h: 头文件
//

#pragma once


// CThreadDlg 对话框
class CThreadDlg : public CDialogEx
{
// 构造
public:
	CThreadDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_THREAD_DIALOG };
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
	afx_msg void OnBnClickedButton1();			//创建进程
	afx_msg void OnBnClickedButton2();			//结束进程
	afx_msg void OnBnClickedButton3();			//创建线程
	afx_msg void OnBnClickedButton4();			//"GO"（创建/挂起线程）
	afx_msg void OnBnClickedButton5();			//暂停（挂起线程）
	afx_msg void OnBnClickedButton6();			//结束（结束线程）
	DECLARE_MESSAGE_MAP()
public:
	void ShowText();							//更新显示
	bool m_bFlag;
	PROCESS_INFORMATION PROCESS_INFORMATION;	//用来保存创建进程返回的进程信息
	CProgressCtrl m_process;					//进度条控件
	HANDLE m_hThread;							//用来保存进度条处创建的线程的句柄
	int m_suspendCount;							//模拟挂起计数器
	CEdit m_text;								//文本框控件
};
