// BaslerCheck.h : BaslerCheck DLL 的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include "dataType.h"
//
#include "HalconCpp.h"
using namespace Halcon;
// CBaslerCheckApp
// 有关此类实现的信息，请参阅 BaslerCheck.cpp
//

class CBaslerCheckApp : public CWinApp
{
public:
	CBaslerCheckApp();

// 重写
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

#define DLL_EXT _declspec(dllexport) 

class DLL_EXT CBaslerCheckCenter 
{
public:



	CBaslerCheckCenter();//默认构造函数add by qq
	CBaslerCheckCenter(int nIndex);
	virtual ~CBaslerCheckCenter();

	bool Init(int nIndex);
	int  Check(Hobject Cancatimage, vector<ErrorRegion> **ErrorVector,int &ErrorCount, Assesment *imgAsses, int &imgCount);
	bool Setting_model(char *imagedata);
	bool Free();

private:
	int  m_lCameraIndex;
   
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

//#endif