
// MFCApplication1Dlg.h: 头文件
//

#pragma once

#include "stdafx.h"
#include "HalconCpp.h"
#include "Motor.h"
#include "Spout.h"
#include "MyCamera.h"
#include "InfraredSensor.h"
#include "Encoder.h"
#include "HardParameterDlg.h"

#define WM_UPDATE_MESSAGE (WM_USER+200)

using namespace HalconCpp;

class Motor;

// CMFCApplication1Dlg 对话框
class CMFCApplication1Dlg : public CDialogEx
{
// 构造
public:
	// 界面对象
	CTime tm;
	CString m_time;
	CFont m_editFont;
	CFont m_editFont1;
	CFont m_editFont2;

	// 用于显示的信息
	int objNum = 0;					// 记录进队物品数量
	int OKNum = 0;					// 记录OK队列中物品总数
	int NGNum = 0;					// 记录NG队列中物品总数
	bool stateCheck = false;		// 检测状态0-暂停 1-启动
	bool stateEnd = false;			// 软件检测是否结束0-未结束 1-结束
	double passRate = 0.0;			// 合格率
	CString strPassRate;			// 合格率

	// Dialog
	HardParameterDlg m_HardParaDlg;
public:
	void showPic(HObject &img, int i);
	void unInit();
	CMFCApplication1Dlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	CBrush m_brush;
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	//	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonStart();
	afx_msg void OnBnClickedButtonOKFlow();
	afx_msg void OnBnClickedButtonNGFlow();
	afx_msg void OnBnClickedButtonPause();
	afx_msg void OnBnClickedButtonOpenOK();
	afx_msg void OnBnClickedButtonCloseOK();
	afx_msg void OnBnClickedButtonExit();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg LRESULT OnMyMsgHandler(WPARAM, LPARAM);

	CButton m_BtnStart;
	CButton m_BtnPause;
	CButton m_BtnExit;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CButton m_BtnCam;
	CButton m_BtnInfor;
	CButton m_BtnOpenOK;
	CButton m_BtnCloseOK;
	CButton m_BtnFlow1;
	CButton m_BtnFlow2;
	afx_msg void OnBnClickedButtonCam();
};
