
// ThreadDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "Thread.h"
#include "ThreadDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CThreadDlg 对话框



CThreadDlg::CThreadDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_THREAD_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_hThread = NULL; //初始化变量
	m_suspendCount = 0; //挂起计数器初始为0
	m_bFlag = true;
}

void CThreadDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS1, m_process);
	DDX_Control(pDX, IDC_EDIT1, m_text);
}

BEGIN_MESSAGE_MAP(CThreadDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CThreadDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CThreadDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CThreadDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CThreadDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CThreadDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CThreadDlg::OnBnClickedButton6)
END_MESSAGE_MAP()


// CThreadDlg 消息处理程序

BOOL CThreadDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CThreadDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CThreadDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CThreadDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CThreadDlg::OnBnClickedButton1()
{
	/*
		CreateProcess() 创建一个新的进程和一个主线程
	*/
	STARTUPINFO startupInfo = { sizeof(STARTUPINFO) };
	TCHAR cmdLine[] = _T("C:\\Windows\\System32\\notepad.exe D:\\网络_全\\进程线程\\Thread\\test.txt");
	CreateProcess(
		NULL,           //进程的名称        
		cmdLine,        //命令行参数
		NULL,           //进程的安全属性
		NULL,           //线程的安全属性
		FALSE,          //继承性
		NORMAL_PRIORITY_CLASS | CREATE_NEW_CONSOLE | CREATE_NEW_PROCESS_GROUP, //创建标志
		NULL,           //NULL表示使用父进程的环境块
		NULL,           //NULL表示使用父进程的开始目录
		&startupInfo,        //进程的信息   
		&PROCESS_INFORMATION
	);
}


void CThreadDlg::OnBnClickedButton2()
{
	/*
		TerminateProcess() 结束进程
	*/
	TerminateProcess(PROCESS_INFORMATION.hProcess, -1);
}

DWORD WINAPI ThreadProc(LPVOID lpParameter)
{
	printf("%s\n", "this is threadProc running...");
	return 0;
}

void CThreadDlg::OnBnClickedButton3()
{
	/*
		CreateThread()  创建线程
	*/
	CreateThread(
		NULL,			//线程的安全属性
		0,				//线程栈大小，0表示默认的1MB
		&ThreadProc,	//线程函数
		0,				//线程函数的参数
		0,				//创建标志 0表示立即执行	CREATE_SUSPENDED表示挂起状态
		NULL			//返回线程的id
	);
}

DWORD WINAPI ThreadProc2(LPVOID lpParameter)
{
	CThreadDlg* p_this = (CThreadDlg*)lpParameter;
	while (p_this->m_bFlag)
	{
		(p_this->m_process).StepIt();
		Sleep(500);
		//Sleep(0)表示让出本次时间片
	}
	return 0;
}

void CThreadDlg::ShowText()
{
	TCHAR szbuff[20] = {0};
	_itow_s(m_suspendCount, szbuff, sizeof(szbuff) / sizeof(WCHAR), 10);
	m_text.SetWindowText(szbuff);
}

void CThreadDlg::OnBnClickedButton4()
{
	//“GO”创建/挂起线程
	if (m_hThread == NULL)
	{
		m_hThread = CreateThread(NULL, 0, &ThreadProc2, this, 0, NULL);
		m_bFlag = true;
		m_suspendCount = 0;
	}
	else {
		//挂起计数器减一，挂起计数器减为0的时候，线程恢复
		ResumeThread(m_hThread);
		if(m_suspendCount>0)
			m_suspendCount--;
	}
	ShowText();
}

void CThreadDlg::OnBnClickedButton5()
{
	//暂停（挂起线程）
	SuspendThread(m_hThread);
	if(m_hThread)
		m_suspendCount++;
	ShowText(); //更新显示
}


void CThreadDlg::OnBnClickedButton6()
{
	//这里采用的结束线程的方法是让线程函数执行完毕自动结束线程。
	m_bFlag = false;
	//线程句柄清空
	if (m_hThread)
	{
		CloseHandle(m_hThread);
		m_hThread = NULL;
	}
	//挂起计数器清零
	m_suspendCount = 0;

	//进度条位置归零
	m_process.SetPos(0);
	ShowText();
}
