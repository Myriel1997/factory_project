#pragma once


// HardParameterDlg 对话框

class HardParameterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(HardParameterDlg)

public:
	HardParameterDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~HardParameterDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HardParameter };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
