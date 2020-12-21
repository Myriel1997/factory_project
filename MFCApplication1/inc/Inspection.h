// Inspection.h : main header file for the INSPECTION DLL
//

#if !defined(AFX_INSPECTION_H__41EDBFAA_F39A_40D8_92E9_37A08E0A731A__INCLUDED_)
#define AFX_INSPECTION_H__41EDBFAA_F39A_40D8_92E9_37A08E0A731A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

#include "dataType.h"
#include "HalconCpp.h"


using namespace HalconCpp;

/////////////////////////////////////////////////////////////////////////////
// CInspectionApp
// See Inspection.cpp for the implementation of this class
//

//class CInspectionApp : public CWinApp
//{
//public:
//	CInspectionApp();
//
//// Overrides
//	// ClassWizard generated virtual function overrides
//	//{{AFX_VIRTUAL(CInspectionApp)
//	//}}AFX_VIRTUAL
//
//	//{{AFX_MSG(CInspectionApp)
//		// NOTE - the ClassWizard will add and remove member functions here.
//		//    DO NOT EDIT what you see in these blocks of generated code !
//	//}}AFX_MSG
//	DECLARE_MESSAGE_MAP()
//};

#define DLL_EXT _declspec(dllexport) 

class DLL_EXT CCheckCenter1 
{
public:

	

	CCheckCenter1();//默认构造函数add by qq
    CCheckCenter1(int nIndex);
    virtual ~CCheckCenter1();
	
	bool Init(StructInitPara InitPara);
	int  Check(const char *imagedata, vector<ErrorRegion> **ErrorVector,int &ErrorCount, Assesment *imgAsses, int &imgCount);
	int  Check(const HalconCpp::HImage image, std::vector<ErrorRegion> **errorinfo, HImage& productimages);
	bool Setting_model(StructSetModelPara SetModelPara);
	bool Free();
	void insp_calib_hand(HTuple robotpoints_row,HTuple robotpoints_col,HTuple campoints_row,HTuple campoints_col,HTuple *calib_error);
	int ReStudy(int reStudy,int reStudyCameraInd );//zhang 采集模板时调用check的LoadModel（int reStudy,int reStudyCameraInd）
private:
	int  m_lCameraIndex;

	
	
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INSPECTION_H__41EDBFAA_F39A_40D8_92E9_37A08E0A731A__INCLUDED_)
