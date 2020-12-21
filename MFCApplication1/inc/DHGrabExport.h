#pragma once

#include "CCDCtrl.h"


#include "HalconCpp.h";

#include <string.h>

using namespace HalconCpp;

class CCCDCtrl;

//using namespace Dahua::GenICam;
//using namespace Dahua::Infra;

enum GrabType
{
	SimDh=0,
	DH
};

class  _declspec(dllexport) DHGrabExport
{
public:
	DHGrabExport(int camidx,STREAM_PROC imgproc,GrabType gbtype);


	~DHGrabExport(void);


	bool openCamera();
	void closeCamera();
	bool startCap();
	bool startCap(int mode);
	void stopCap();

	int getExposure();

	int setExposure(int exposure);

	int getChunkCount();
	int setCounterReset();

	bool SoftTrigger();

	void setUserOutputValue( GenICam::CSystem &systemObj, GenICam::ICameraPtr& cameraSptr,bool bValue);

	void setUserOutputValue(bool bValue);

	void ListTestImages(std::string hv_dir,HObject&concatimg);

	//读取图像线程
	static UINT GrabThread( LPVOID  pCallbackData);
	//循环读取函数
	UINT DoGrabLoop();
public:
	CCCDCtrl* pCCDCtrl;
	int       m_isStartCap;
	int m_cameraidx;
    GrabType m_gbType;

	HObject m_simimg;
			    //HObject imgsel;

    int ReadCount_Image;
	bool m_ThreadContinueGrab;
	HANDLE m_heventThreadDone ;

	STREAM_PROC m_simproc;
	int current_ind;//当前头像的下标

	//存储图像
	std::queue<HObject> m_imgQueue;
	static UINT InvokeCallBack( LPVOID  pCallbackData);
};
