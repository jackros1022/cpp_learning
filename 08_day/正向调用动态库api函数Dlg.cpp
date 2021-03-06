
// 正向调用动态库api函数Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "正向调用动态库api函数.h"
#include "正向调用动态库api函数Dlg.h"
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
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// C正向调用动态库api函数Dlg 对话框




C正向调用动态库api函数Dlg::C正向调用动态库api函数Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(C正向调用动态库api函数Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C正向调用动态库api函数Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(C正向调用动态库api函数Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &C正向调用动态库api函数Dlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// C正向调用动态库api函数Dlg 消息处理程序

BOOL C正向调用动态库api函数Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void C正向调用动态库api函数Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void C正向调用动态库api函数Dlg::OnPaint()
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
HCURSOR C正向调用动态库api函数Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//客户端初始化 获取handle上下

//声明一个函数指针类型
typedef int (*CltSocketInit)(void **handle /*out*/); 

//客户端发报文
typedef int (*CltSocketSend)(void *handle /*in*/, unsigned char *buf /*in*/,  int buflen /*in*/);


//客户端收报文
typedef int (*CltSocketRev)(void *handle /*in*/, unsigned char *buf /*in*/, int *buflen /*in out*/);

//客户端释放资源
typedef int (*CltSocketDestory)(void *handle/*in*/);

void C正向调用动态库api函数Dlg::OnBnClickedButton1()
{
	HINSTANCE hInstance;

	hInstance=::LoadLibrary("c:/socketclient.dll");
	if (hInstance == NULL)
	{
		AfxMessageBox("LoadLibrary() 失败");
		return ;
	}
	CltSocketInit cltSocketInit = (CltSocketInit)::GetProcAddress(hInstance,"cltSocketInit");
	if (cltSocketInit  == NULL)
	{
		return ;
	}

	CltSocketSend cltSocketSend = (CltSocketSend)::GetProcAddress(hInstance,"cltSocketSend");
	CltSocketRev cltSocketRev = (CltSocketRev)::GetProcAddress(hInstance,"cltSocketRev");
	CltSocketDestory cltSocketDestory = (CltSocketDestory)::GetProcAddress(hInstance,"cltSocketDestory");


	//执行动态库函数调用
	unsigned char buf[128];
	int buflen = 128;

	unsigned char outbuf[4096];
	int outbuflen = 4096;

	strcpy((char *)buf, "aaaaaaaaaafffffffffdddddd");
	buflen = 9;

	void *handle = NULL;
	int ret = 0;
	ret = cltSocketInit(&handle);
	ret = cltSocketSend(handle, buf, buflen);
	ret = cltSocketRev(handle, outbuf, &outbuflen);
	ret = cltSocketDestory(handle);

	if (memcmp(buf, outbuf, outbuflen) == 0)
	{
		AfxMessageBox("发送数据和接受的数据一样 ok");
	}
	else
	{
		AfxMessageBox("发送数据和接受的数据不一样");
	}
	



	AfxMessageBox("ssss");
}
