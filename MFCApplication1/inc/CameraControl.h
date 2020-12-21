// CameraControl.h : CameraControl DLL ����ͷ�ļ�
// E2V������Ƴ���

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CCameraControlApp
// �йش���ʵ�ֵ���Ϣ������� CameraControl.cpp
//

class CCameraControlApp : public CWinApp
{
public:
	CCameraControlApp();

// ��д
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
	void RefreshImg(const char *imagedata, int m_bWidth, int m_bHeight);  //��ʵʱ��ʾͬ��
	void SetCamParaDlg(const char *imagedata, int m_bWidth, int m_bHeight);
	BOOL InitCamCommand(CString PortNum);
	void CloseCamCommand();
	//Basic Commands
	BOOL SendCamCommand(CString CamCommand);
	//Advance Functions
	int  OneKeyExposure();
	BOOL OneKeyFFC();
	
};
