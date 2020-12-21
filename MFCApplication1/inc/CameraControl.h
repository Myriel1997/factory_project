// CameraControl.h : CameraControl DLL 的主头文件
// E2V相机控制程序

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号


// CCameraControlApp
// 有关此类实现的信息，请参阅 CameraControl.cpp
//

class CCameraControlApp : public CWinApp
{
public:
	CCameraControlApp();

// 重写
public:
	//virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

#define DLL_EXT _declspec(dllexport)

class DLL_EXT CCameraControl
{
public:
	int m_lCameraIndex;
	BOOL m_isDlgOpen;
public:
	CCameraControl();
	CCameraControl(int Index);
	virtual ~CCameraControl();
    
	void Init(int width, int height);
	void RefreshImg(const char *imagedata, int m_bWidth, int m_bHeight);  //与实时显示同步
	void SetCamParaDlg(const char *imagedata, int m_bWidth, int m_bHeight);
	BOOL InitCamCommand(CString PortNum);
	void CloseCamCommand();
	//Basic Commands
	BOOL SendCamCommand(CString CamCommand);
	//Advance Functions
	int  OneKeyExposure();
	BOOL OneKeyFFC();
	
};
