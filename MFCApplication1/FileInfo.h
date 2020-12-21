#pragma once
#include "targetver.h"
#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展
#include <afxdisp.h>        // MFC 自动化类
#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持
//#include "SkinPPWTL.h"

class CFileInfo
{
public:
	CFileInfo(void);
	~CFileInfo(void);

public:
	char		m_CurrentPath[_MAX_PATH];	// 获得应用程序路径
	CString m_strModelPath;			//Model文件夹路径
	CString m_strSharePath;			//user.ini路径
	//CString m_ModelImagePath;	//图像路径名称
	CString m_ModelRegionPath;	//区域路径名称
	CString m_strModelIniPath;		//参数配置文件路径名称
	CString m_ModelComPath;		//串口通信配置文件路径名称
	CString m_strCamPath;	//相机参数配置文件

private:
	int m_nCamIndex;

public:
	bool GetCurrentAppPath(char **path);//bin目录路径
	CString GetShareIniPath();//user.ini路径
	//void ModelFilePath(int camIndex); //Model下文件路径
	CString GetModelPath(int pro_index,int camIndex);
	CString GetModelPathUP(int pro_index);
	CString GetCamPath(int camIndex);
};
