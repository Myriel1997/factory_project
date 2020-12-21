// BaslerCheck.h : BaslerCheck DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "dataType.h"
//
#include "HalconCpp.h"
using namespace Halcon;
// CBaslerCheckApp
// �йش���ʵ�ֵ���Ϣ������� BaslerCheck.cpp
//

class CBaslerCheckApp : public CWinApp
{
public:
	CBaslerCheckApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

#define DLL_EXT _declspec(dllexport) 

class DLL_EXT CBaslerCheckCenter 
{
public:



	CBaslerCheckCenter();//Ĭ�Ϲ��캯��add by qq
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