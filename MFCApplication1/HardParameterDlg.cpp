// HardParameterDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MFCApplication1.h"
#include "HardParameterDlg.h"
#include "afxdialogex.h"


// HardParameterDlg 对话框

IMPLEMENT_DYNAMIC(HardParameterDlg, CDialogEx)

HardParameterDlg::HardParameterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HardParameter, pParent)
{

}

HardParameterDlg::~HardParameterDlg()
{
}

void HardParameterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(HardParameterDlg, CDialogEx)
END_MESSAGE_MAP()


// HardParameterDlg 消息处理程序
