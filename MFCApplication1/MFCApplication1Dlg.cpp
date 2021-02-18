
// MFCApplication1Dlg.cpp: 实现文件
//
#include "stdafx.h"
#include <opencv2\opencv.hpp>
#include "Resource.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include <vector>
#include "CirQue.h"
#include "LTDMC.h"
#include "DHGrabExport.h"
#include "init.h"
#include "MyThread.h"
#include "Motor.h"
#include "LED.h"
#include <string.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CMFCApplication1Dlg *dlg1;				// 总类的指针
// 队列
CirQue *g_QueObj;						// 物品队列（未检测）
CirQue *g_QueOK;						// OK品队列
CirQue *g_QueNG;						// NG品队列
// 硬件
LED g_GreenLED, g_RedLED, g_YellowLED;	// 报警灯
MyCamera *(g_Camera[4]);				// 相机
Motor g_Motor;							// 电机
Spout g_OKSpout, g_NGSpout;				// 喷口
Encoder g_Encoder;						// 编码器
InfrSenr g_InfrSenr;					// 红外传感器

// 界面显示
HTuple m_htWindow[CAMNUM];				// 窗口句柄
std::vector<int> imageShowArea;			// 窗口容器
CList<CRect, CRect> listRect;			// 保存对话框中窗口矩形
int m_nWidth[CAMNUM];					// 图像宽度
int m_nHeight[CAMNUM];					// 图像高度

int moterSpeed = 0;						// 电机转速

extern cv::Mat maskImg[4];					// 标准图像
extern int objPos;
bool resize_wind;
bool update_data = false;				// 数据更新flag

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
	if (update_data) {
		DDX_Text(pDX, IDC_EDIT6, objNum);
		DDX_Text(pDX, IDC_EDIT7, OKNum);
		DDX_Text(pDX, IDC_EDIT8, NGNum);
		DDX_Text(pDX, IDC_EDIT_ENCODE, g_Encoder.m_EncoderData);
		DDX_Text(pDX, IDC_EDIT10, strPassRate);
		DDX_Text(pDX, IDC_EDIT_SPEED, moterSpeed);
	}
	DDX_Control(pDX, IDC_BUTTON_START, m_BtnStart);
	DDX_Control(pDX, IDC_BUTTON_PAUSE, m_BtnPause);
	DDX_Control(pDX, IDC_BUTTON_EXIT, m_BtnExit);
	DDX_Control(pDX, IDC_BUTTON_CAM, m_BtnCam);
	DDX_Control(pDX, IDC_BUTTON_INFOR, m_BtnInfor);
	DDX_Control(pDX, IDC_BUTTON_OPENOK, m_BtnOpenOK);
	DDX_Control(pDX, IDC_BUTTON_CLOSEOK, m_BtnCloseOK);
	DDX_Control(pDX, IDC_BUTTON_OKFLOW, m_BtnFlow1);
	DDX_Control(pDX, IDC_BUTTON_NGFLOW, m_BtnFlow2);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, &CMFCApplication1Dlg::OnBnClickedButtonStart)
	ON_BN_CLICKED(IDC_BUTTON_OKFLOW, &CMFCApplication1Dlg::OnBnClickedButtonOKFlow)
	ON_BN_CLICKED(IDC_BUTTON_NGFLOW, &CMFCApplication1Dlg::OnBnClickedButtonNGFlow)
	ON_BN_CLICKED(IDC_BUTTON_PAUSE, &CMFCApplication1Dlg::OnBnClickedButtonPause)
	ON_BN_CLICKED(IDC_BUTTON_OPENOK, &CMFCApplication1Dlg::OnBnClickedButtonOpenOK)
	ON_BN_CLICKED(IDC_BUTTON_CLOSEOK, &CMFCApplication1Dlg::OnBnClickedButtonCloseOK)
	ON_MESSAGE(WM_UPDATE_MESSAGE, &CMFCApplication1Dlg::OnMyMsgHandler)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CMFCApplication1Dlg::OnBnClickedButtonExit)
	ON_WM_SIZE()
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_CAM, &CMFCApplication1Dlg::OnBnClickedButtonCam)
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
		pSysMenu->EnableMenuItem(SC_CLOSE, TRUE);//禁用关闭按钮
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
	// 背景刷子初始化
	//m_brush.CreateSolidBrush(RGB(255, 255, 255));
	// 按钮
	
	// 字体初始化
	m_editFont.CreatePointFont(150, _T("宋体"));
	GetDlgItem(IDC_EDIT_TIME)->SetFont(&m_editFont);
	GetDlgItem(IDC_STATIC_ENCODE)->SetFont(&m_editFont);
	GetDlgItem(IDC_STATIC_SPEED)->SetFont(&m_editFont);
	GetDlgItem(IDC_STATIC_PRODUCTNAME)->SetFont(&m_editFont);
	GetDlgItem(IDC_STATIC_PRODUCTNMODEL)->SetFont(&m_editFont);
	GetDlgItem(IDC_STATIC_PRODUCTBATCH)->SetFont(&m_editFont);
	GetDlgItem(IDC_STATIC_ALLNUM)->SetFont(&m_editFont);
	GetDlgItem(IDC_STATIC_OKNUM)->SetFont(&m_editFont);
	GetDlgItem(IDC_STATIC_NGNUM)->SetFont(&m_editFont);
	GetDlgItem(IDC_STATIC_PASSRATE)->SetFont(&m_editFont);
	GetDlgItem(IDC_STATIC_SIZEDEFET)->SetFont(&m_editFont);
	GetDlgItem(IDC_STATIC_DEFET)->SetFont(&m_editFont);
	GetDlgItem(IDC_STATIC_OTHERDEFET)->SetFont(&m_editFont);
	GetDlgItem(IDC_STATIC_IMAGEBODER)->SetFont(&m_editFont);
	GetDlgItem(IDC_STATIC_IMG1)->SetFont(&m_editFont);
	GetDlgItem(IDC_STATIC_IMG2)->SetFont(&m_editFont);
	GetDlgItem(IDC_STATIC_IMG3)->SetFont(&m_editFont);
	GetDlgItem(IDC_STATIC_IMG4)->SetFont(&m_editFont);
	GetDlgItem(IDC_STATIC_HARDBORDER)->SetFont(&m_editFont);
	GetDlgItem(IDC_STATIC_PRODUCTBORDER)->SetFont(&m_editFont);
	GetDlgItem(IDC_STATIC_RESULTBORDER)->SetFont(&m_editFont);
	GetDlgItem(IDC_STATIC_INFORBORDER)->SetFont(&m_editFont);
	GetDlgItem(IDC_STATIC_FEATUREBORDER)->SetFont(&m_editFont);

	m_editFont1.CreatePointFont(280, _T("黑体"));
	GetDlgItem(IDC_STATIC_ITEM)->SetFont(&m_editFont1);
	m_editFont2.CreatePointFont(150, _T("黑体"));
	GetDlgItem(IDC_STATIC_COMPANYNAME)->SetFont(&m_editFont2);
	
	//GetDlgItem(IDC_EDIT12)->SetFont(&m_editFont);
	//GetDlgItem(IDC_EDIT_SPEED)->SetFont(&m_editFont);

	// 图标初始化
	HBITMAP hBmp = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_START));
	m_BtnStart.SetBitmap(hBmp);
	hBmp = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_PAUSE));
	m_BtnPause.SetBitmap(hBmp);
	hBmp = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_STOP));
	m_BtnExit.SetBitmap(hBmp);
	hBmp = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_CAM));
	m_BtnCam.SetBitmap(hBmp);
	hBmp = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_INFOR));
	m_BtnInfor.SetBitmap(hBmp);
	hBmp = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_OPENOK));
	m_BtnOpenOK.SetBitmap(hBmp);
	hBmp = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_CLOSEOK));
	m_BtnCloseOK.SetBitmap(hBmp);
	hBmp = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_FLOW1));
	m_BtnFlow1.SetBitmap(hBmp);
	hBmp = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP_FLOW2));
	m_BtnFlow2.SetBitmap(hBmp);
	// 图像框初始化
	imageShowArea.push_back(IDC_Show1);
	imageShowArea.push_back(IDC_Show2);
	imageShowArea.push_back(IDC_Show3);
	imageShowArea.push_back(IDC_Show4);

	// 设备初始化
	g_Encoder.Start();
	g_Motor.SetSpeed(10000);
	g_Motor.Init();
	g_OKSpout.Init(0, 5, 50);
	g_NGSpout.Init(1, 6, 50);
	g_GreenLED.Init(10);
	g_YellowLED.Init(14);
	//g_RedLED.Init();
	for (int i = 0; i < CAMNUM;i++) {
		g_Camera[i] = new MyCamera(i, CallBackN, (GrabType)1);
	}
	g_QueObj = new CirQue(QUESIZE);
	g_QueOK = new CirQue(QUESIZE);
	g_QueNG = new CirQue(QUESIZE);
	
	//更新界面窗口
	CRect rectWnd;
	GetWindowRect(&rectWnd);
	listRect.AddTail(&rectWnd);
	CWnd *pWndChild = GetWindow(GW_CHILD);//GW_CHILD标识了CWnd的第一个子窗口。返回窗口指针
	while (pWndChild)
	{
		pWndChild->GetWindowRect(&rectWnd);
		listRect.AddTail(&rectWnd);
		pWndChild = pWndChild->GetNextWindow();
	}
	resize_wind = false;
	ShowWindow(SW_SHOWMAXIMIZED);// 窗口最大化
	SetWindowLong(m_hWnd, GWL_STYLE, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX);

	// 启动时间定时器
	tm = CTime::GetCurrentTime();
	m_time = tm.Format("%Y年%m月%d日%H:%M");
	SetTimer(1, 1000 * 60, NULL);
	SetDlgItemText(IDC_EDIT_TIME, m_time);
	// 指针赋值，否则报错
	dlg1 = this;
	// 线程初始化
	threadInit(this);
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


void CMFCApplication1Dlg::OnBnClickedButtonStart()
{
	// 读取照片
	maskImg[0] = cv::imread("model0.bmp", 0);
	maskImg[1] = cv::imread("model1.bmp", 0);
	maskImg[2] = cv::imread("model2.bmp", 0);
	maskImg[3] = cv::imread("model3.bmp", 0);
	// 电机转动后再开启更新数据
	update_data = true;
	// 检测状态->开启
	stateCheck = true;
	// 电机启动
	g_Motor.Start();
	moterSpeed=10000;
	// 灯光
	g_GreenLED.Open();
	g_YellowLED.Close();
}

void CMFCApplication1Dlg::OnBnClickedButtonOKFlow()
{
	g_OKSpout.Open();
	// TODO: 在此添加控件通知处理程序代码
}

void CMFCApplication1Dlg::OnBnClickedButtonNGFlow()
{
	g_NGSpout.Open();
	// TODO: 在此添加控件通知处理程序代码
}

void CMFCApplication1Dlg::OnBnClickedButtonPause()
{
	// TODO: 在此添加控件通知处理程序代码
	stateCheck = false;
	// 硬件关闭
	g_Encoder.Stop();
	g_Motor.Stop();
	moterSpeed=0;
	g_YellowLED.Open();
	g_GreenLED.Close();
}
// 退出系统
void CMFCApplication1Dlg::OnBnClickedButtonExit()
{
	// TODO: 在此添加控件通知处理程序代码
	unInit();
	CDialogEx::OnCancel();
}

void CMFCApplication1Dlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 在此处添加消息处理程序代码
	int nCount = listRect.GetCount();
	if (nCount > 0)
	{
		for (int i = 0;i < CAMNUM;i++)
		{
			if (m_htWindow[i].Length() > 0)
			{
				HalconCpp::CloseWindow(m_htWindow[i]);
			}
		}
		CRect rtWindow;
		HWND hImgWnd;
		//显示图像的区域
		for (int i = 0; i < CAMNUM; i++)
		{
			hImgWnd = GetDlgItem(imageShowArea.at(i))->m_hWnd;
			GetDlgItem(imageShowArea.at(i))->GetClientRect(&rtWindow);

			OpenWindow(rtWindow.left, rtWindow.top, rtWindow.Width(), rtWindow.Height(), (Hlong)hImgWnd, "visible", "", &m_htWindow[i]);
			SetDraw(m_htWindow[i], "margin");
			SetLineWidth(m_htWindow[i], 3);
			SetColor(m_htWindow[i], "green");

			SetPart(m_htWindow[i], 0, 0, m_nHeight[i], m_nWidth[i]);

		}
	}
}

// 开启OK阀门
void CMFCApplication1Dlg::OnBnClickedButtonOpenOK()
{
	// TODO: 在此添加控件通知处理程序代码
	// 打开OK阀门
	dmc_write_outbit(0, 7, 1);
}
// 关闭OK阀门
void CMFCApplication1Dlg::OnBnClickedButtonCloseOK()
{
	// TODO: 在此添加控件通知处理程序代码
	// 关闭OK阀门
	dmc_write_outbit(0, 7, 0);
}
// 显示图片
void CMFCApplication1Dlg::showPic(HObject &img, int i)
{
	ClearWindow(m_htWindow[i]);
	DispObj(img, m_htWindow[i]);
}
// 关闭硬件
void CMFCApplication1Dlg::unInit()
{
	// 关闭线程
	stateEnd = true;
	Sleep(100);
	// 指针释放
	delete g_QueObj;
	delete g_QueOK;
	delete g_QueNG;
	for (int i = 0; i < CAMNUM; i++) {
		g_Camera[i]->stopCap();
		g_Camera[i]->closeCamera();
		delete g_Camera[i];
	}
	// 硬件关闭
	g_Motor.Stop();
	g_Encoder.Stop();
	// 灯光
	g_GreenLED.Close();
	g_YellowLED.Close();
	g_RedLED.Close();
}
// 界面显示信息
LRESULT CMFCApplication1Dlg::OnMyMsgHandler(WPARAM w, LPARAM l)
{
	this->UpdateData(FALSE);
	return 0;
}

HBRUSH CMFCApplication1Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (nCtlColor == CTLCOLOR_EDIT) {
		pDC->SetBkColor(RGB(240, 240, 240));
		//pDC->SetBkMode(TRANSPARENT);//设置背景透明
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	//return (HBRUSH)m_brush.GetSafeHandle();
	return hbr;
}


void CMFCApplication1Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch(nIDEvent)
	{
		case 1:
			// 更新时间
			tm = CTime::GetCurrentTime();
			m_time = tm.Format("%Y年%m月%d日%H:%M");
			SetDlgItemText(IDC_EDIT_TIME, m_time);
			break;
	}
		
	CDialogEx::OnTimer(nIDEvent);
}


void CMFCApplication1Dlg::OnBnClickedButtonCam()
{
	// TODO: 在此添加控件通知处理程序代码
	if (stateCheck) {
		AfxMessageBox("请先暂停调试！！！");
		return;
	}
	m_HardParaDlg.DoModal();
}
