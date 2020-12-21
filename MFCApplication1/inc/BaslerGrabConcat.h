#pragma once
#include <afxwin.h>
#include "BSCamCtr.h"//20151130L2
#include "BSGraberExport.h"
#include "HalconCpp.h"
using namespace Halcon;
#define DLL_EXT _declspec(dllexport) 

static void WINAPI BsCallBack1(Pylon::CGrabResultPtr  ptrGrabResult);

class DLL_EXT BaslerGrabConcat
{
public:
	BaslerGrabConcat(void);
 virtual ~BaslerGrabConcat()
 {};
	void SetupCamera (GrabberType Sim,bool Brust,double timeout);
	void init(int burstframe);
	void StatConcat();
    void GetBasCancatImg (HObject &ho_Image, HObject &ho_Image_b, HObject &ho_Region);
	void GetBasCancatImg_2(HObject &ho_Image, HObject &ho_Image_b, HObject &ho_Region);
	void Close();
//	static void WINAPI BsCallBack1(s_GBBASLERINFO*ptrGrabResult);
public:
	CBSGraber *m_PBSGrabber;
	  int m_burstframe;
	  int m_width;
	  int m_Heigh;
	  // Camera Node Map.
	  GenApi::INodeMap **m_pCameraNodeMap;

	  //static void WINAPI BsCallBack1(Pylon::CGrabResultPtr  ptrGrabResult);
	  

};
