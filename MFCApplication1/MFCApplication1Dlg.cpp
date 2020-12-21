
// MFCApplication1Dlg.cpp: 实现文件
//
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#include "init.h"
#include "LTDMC.h"
#include "SpoutCtrl.h"
#include "CamCtrl.h"
#include "obj.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


long encodeNum = 0;			// 当前编码器数值
CMFCApplication1Dlg *dlg;	// 总类的指针
CirQue *queObj;				// 物品队列（未检测）
CirQue *queOK, *queNG;		// OK队列和NG队列

CString str;				// 作字符输出用，无意义

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


// CMFCApplication1Dlg 对话框



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication1Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication1Dlg::OnBnClickedButton2)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication1Dlg::OnBnClickedButton3)
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCApplication1Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDOK, &CMFCApplication1Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMFCApplication1Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON5, &CMFCApplication1Dlg::OnBnClickedButton5)
END_MESSAGE_MAP()

// CMFCApplication1Dlg 消息处理程序

BOOL CMFCApplication1Dlg::OnInitDialog()
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
	imageShowArea.push_back(IDC_STATIC);
	queObj = CreateCirQue(QUESIZE);			// 创建物品队列
	queOK = CreateCirQue(QUESIZE);			// 创建OK品队列
	queNG = CreateCirQue(QUESIZE);			// 创建NG品队列

	// 创建两个线程，提供给喷口使用
	/*CWinThread *pThreadBlowOK, *pThreadBlowNG;
	LPVOID  ptArg;
	ptArg = (LPVOID)this;
	pThreadBlowOK = AfxBeginThread(threadBlowOK, ptArg, THREAD_PRIORITY_TIME_CRITICAL, 0, 0, NULL);
	pThreadBlowOK = AfxBeginThread(threadBlowNG, ptArg, THREAD_PRIORITY_TIME_CRITICAL, 0, 0, NULL);*/

	// 设备初始化
	motorInit();
	cameraInit();
	sortingInit();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMFCApplication1Dlg::OnPaint()
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
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnBnClickedButton1()
{
	// 开启定时器
	SetTimer(1, 40, NULL);	// 创建1这个定时器，间隔为100ms
	// 关闭OK阀门
	// dmc_write_outbit(0, 7, 0);
	// 电机启动
	dmc_vmove(0, 0, 1);
	// 进料启动
	dmc_write_outbit(0, 4, 0);
}


void CMFCApplication1Dlg::OnBnClickedButton2()
{
	OpenOKSpout();
	// TODO: 在此添加控件通知处理程序代码
}

void CMFCApplication1Dlg::OnBnClickedButton3()
{
	OpenNGSpout();
	// TODO: 在此添加控件通知处理程序代码
}

void CMFCApplication1Dlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	dmc_write_outbit(0, 4, 0);// 进料关闭
	dmc_sorting_close(0); //关闭分拣功能 
	dmc_set_dec_stop_time(0, 0, 1);
	dmc_stop(0, 0, 0);
	dmc_write_outbit(0, 14, 0);//黄灯开
	dmc_write_outbit(0, 10, 1);//绿灯关

}

void CMFCApplication1Dlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	dmc_write_outbit(0, 4, 0);// 进料关闭
	dmc_sorting_close(0); //关闭分拣功能 
	dmc_set_dec_stop_time(0, 0, 1);
	dmc_stop(0, 0, 0);
	dmc_write_outbit(0, 14, 0);//黄灯开
	dmc_write_outbit(0, 10, 1);//绿灯关

	CDialogEx::OnOK();
}


void CMFCApplication1Dlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	dmc_write_outbit(0, 4, 0);// 进料关闭
	dmc_sorting_close(0); //关闭分拣功能 
	dmc_set_dec_stop_time(0, 0, 1);
	dmc_stop(0, 0, 0);
	dmc_write_outbit(0, 14, 0);//黄灯开
	dmc_write_outbit(0, 10, 1);//绿灯关

	CDialogEx::OnCancel();
}

void CMFCApplication1Dlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码

}


// 关闭OK阀门
void CMFCApplication1Dlg::OnBnClickedButton5()
{
	// TODO: 在此添加控件通知处理程序代码
	// 打开OK阀门
	dmc_write_outbit(0, 7, 0);
}

// OK喷嘴开启
void CMFCApplication1Dlg::OpenOKSpout()
{
	dmc_write_outbit(0, 5, 0);// 开启
	SetTimer(2, 40, NULL);
}
// NG喷嘴开启
void CMFCApplication1Dlg::OpenNGSpout()
{
	dmc_write_outbit(0, 6, 0);// 开启
	SetTimer(3, 40, NULL);
}



void CMFCApplication1Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nIDEvent)
	{
		case 1:
			KillTimer(1);
			// 获取编码器数值
			encodeNum = dmc_get_encoder(0, 0);
			// 当前有一个物料通过红外传感器
			if (dmc_read_inbit(0, 14)) {
				// 将这个物料加入未处理队列
				SingleObj *obj = CreateObj();	// 创建一个物品结构体
				obj->infrEncode = encodeNum;	// 记录它在红外传感器处编码器值，用以计算差值
				PushBack(queObj, obj);			// 加入队列
			}

			// 遍历未检测队列是否有物品抵达某个相机位置
			TraQue(queObj, CamProcess);

			// 遍历OK队列是否有物品达到OK喷口
			TraQue(queOK, SpoutOKProcess);
			// 遍历NG队列是否有物品达到NG喷口
			TraQue(queNG, SpoutNGProcess);
			
			// 界面显示队列长度
			str.Format("%ld", queObj->lengthQue);
			GetDlgItem(IDC_EDIT2)->SetWindowTextA(str);
			str.Format("%ld", queOK->lengthQue);
			GetDlgItem(IDC_EDIT3)->SetWindowTextA(str);
			str.Format("%ld", queNG->lengthQue);
			GetDlgItem(IDC_EDIT4)->SetWindowTextA(str);

			// 再次开启
			SetTimer(1, 50, NULL);
			break;
		case 2:
			dmc_write_outbit(0, 5, 1);// 关闭OK喷口
			KillTimer(2);
			break;
		case 3:
			dmc_write_outbit(0, 6, 1);// 关闭NG喷口
			KillTimer(3);
			break;
	}

	CDialogEx::OnTimer(nIDEvent);
}

