#pragma once
#include <pylon/PylonIncludes.h>
#ifdef PYLON_WIN_BUILD
#    include <pylon/PylonGUI.h>
#endif


#include <pylon/usb/BaslerUsbInstantCamera.h>
typedef Pylon::CBaslerUsbInstantCamera Camera_t;
using namespace Basler_UsbCameraParams;

#include "HalconCpp.h";
using namespace Halcon;

// Namespace for using pylon objects.
using namespace Pylon;

#include <pylon/usb/BaslerUsbInstantCamera.h>
typedef Pylon::CBaslerUsbInstantCamera Camera_t;
using namespace Basler_UsbCameraParams;


using namespace GenApi;

// Number of images to be grabbed.


typedef void (WINAPI *BSCheck)(Hobject &hImgInput);

//const int GBMaxFileNameLen = 255;

typedef struct _GbBselerInfoStruct//回调信息结构
{
	int  Camidx;																	
    char strDescription[255];	
	Hobject imgobj;
	int ErrorCode;
	int w;
	int h;
	int FrameCount;
	int LineCount;

}s_GBBASLERINFO;//回调信息结构

typedef void (WINAPI *BSCALLBACK)(s_GBBASLERINFO*ptrGrabResult);

//DALSA专用参数
enum GrabberType
{
	BSG = 0,   //模拟采集卡
	SimBSG,
	BASLER
};

class  _declspec(dllexport) CBSGraber
{
public:
	CBSGraber(void);
	virtual~CBSGraber(void);
	BOOL Init(BSCALLBACK callback,int FrameCount,GrabberType gbtype,bool BurstOn,double timeout);
	void Close();
	void StartGrab();
	void StopGrab();
	void SetTrigger(bool ison);
	void ReadFramStartString();
    void EnableExternalTrigger();
	void DisableExternalTrigger(int camidx);
	void ExecuteTrigger();
	void SetAllTriggerOff(int camidx);
	void ListTestImages(HTuple hv_dir,Hobject&concatimg);
    int GetSimImgW()
	{
		return  imgw;
	}
	int GetSimImgH()
	{
		return imgh;
	}
	int64_t GetTotalBufferCount(int camidx);
	GenApi::INodeMap **GetCameraNodeMap()
	{
		return m_pCameraNodeMap;
	}
    BSCALLBACK m_CallBackFun;
	//enum{N=6};
private:
Pylon::PylonAutoInitTerm autoInitTerm;

 CInstantCameraArray m_cameras;

 //读取图像线程
 static UINT GrabThread( LPVOID  pCallbackData);
 //循环读取函数
 UINT DoGrabLoop();
public:
	int m_FrameCount;
	int m_CameraCount;
    GenApi::INodeMap *m_pCameraNodeMap[6];
	GrabberType m_grabType;
	//Hobject ho_ImageTest[2];

	Hobject ho_ImageTest1;
	Hobject ho_ImageTest2;
	int testpicnum;
    bool m_burston;
	double m_timeout;
	gcstring Framestartmode;


	bool m_ThreadContinueGrab;
    HANDLE m_heventThreadDone ;
    int ReadCount_Image;

	int imgw;
	int imgh;

    s_GBBASLERINFO sginfo;

};
