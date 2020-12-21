// Inspection.h : main header file for the INSPECTION DLL
//



#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

//#include "resource.h"		// main symbols
#include "HalconCpp.h"
#include "dataType.h"
/////////////////////////////////////////////////////////////////////////////
// CInspectionApp
// See Inspection.cpp for the implementation of this class
//
using namespace Halcon;
class CBSCamCtrApp : public CWinApp
{
public:
	CBSCamCtrApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInspectionApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CInspectionApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#define DLL_EXT _declspec(dllexport) 

class DLL_EXT SCheckCenter 
{
public:

	

	SCheckCenter();//默认构造函数add by qq
    SCheckCenter(int nIndex);
    virtual ~SCheckCenter();
	
	//bool Init(int width,int height);
	//int  Check(const char *imagedata, vector<ErrorRegion> **ErrorVector,int &ErrorCount, Assesment *imgAsses, int &imgCount);
 //   bool Setting_model(char *imagedata);
	//bool Free();

	/*void Connect (int  hv_CamID, int   hv_LineCounts, int &hv_Status);
	void Start (int &hv_Status);
	void Close (int&hv_Status);*/
	//void GetBasCheckResult (HObject *ho_Image, vector<ErrorRegion> **ho_ErrorRegion, HObject *ho_ErrorImage, HTuple *hv_ErrorInfo);
	void GetBasCancatImg (HObject &ho_Image, HObject &ho_Image_b, HObject &ho_Region);
	
	void SetCheckStatus (int  hv_State);
    void init(int CamID);

	void CallBack (HObject ho_Image, int hv_Index);
	void Start (int hv_ConCatCount, int hv_ImageWidth, int hv_ImageHeight);
	void Close ();
	//void GetBasCheckResult (HObject *ho_Image, HObject *ho_ErrorRegion, HObject *ho_ErrorImage, 
	//	HTuple *hv_ErrorInfo);

	
private:
	int  m_lCameraIndex;
	float m_fHorRes;//横向分辨率
	float m_fVerRes;//纵向分辨率

	
	
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

