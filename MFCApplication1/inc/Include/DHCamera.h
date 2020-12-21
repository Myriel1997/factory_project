#ifndef DHCAMERA_H
#define DHCAMERA_H

#include "Include/GenICam/System.h"
#include "Include/GenICam/Camera.h"
#include "Include/GenICam/GigE/GigEInterface.h"
#include "Include/GenICam/GigE/GigECamera.h"
#include "Include/GenICam/EventSubscribe.h"
#include "Include/Infra/Vector.h"
#include "Include/Infra/Thread.h"
#include "Include/Infra/Mutex.h"
#include "Include/Infra/Guard.h"
#include "vector"
#include <queue>
//#include "Include/datatype.h"
#include "Include/GenICam/StreamSource.h"
#include "HalconCpp.h"
using namespace HalconCpp;
using namespace Dahua;


//触发模式-开启
#define TRIGMODE_ON_STR			 "On"

//触发模式-关闭，即连续模式
#define TRIGMODE_OFF_STR		 "Off"

//自动曝光-关闭，此时可使用自定义曝光时间
#define EXPOSUREAUTO_OFF_STR     "Off"

//自动增益-关闭，此时可使用自定义增益
#define GAINAUTO_OFF_STR		 "Off"

//外触发下降沿有效
#define TRIGACT_FALLINGEDGE_STR  "FallingEdge"

//外触发上升沿有效
#define TRIGACT_RISINGEDGE_STR   "RisingEdge"

//触发源为软触发
#define TRIGSRC_SOFT_STR		 "Software"

//触发源为LINE触发
#define TRIGSRC_LINE1_STR		 "Line1"
#define TRIGSRC_LINE2_STR		 "Line2"
#define TRIGSRC_LINE3_STR		 "Line3"
#define TRIGSRC_LINE4_STR		 "Line4"
#define TRIGSRC_LINE5_STR		 "Line5"

typedef enum enumWORKMODE
{
	UNKNOW_MODE = -1,
	CONMODE		= 0,	//连续模式
	TRIGMODE	= 1		//触发模式
}WORKMODE;

// 触发源：软触发、外触发，触发工作模式下有效
typedef enum enumTRIGSRC
{
	UNKNOW_SRC		= -1,
	TRIG_SOFT		= 0,	//触发源：软触发
	TRIG_LINE1		= 1,	//触发源：LINE1触发
	TRIG_LINE2		= 2,	//触发源：LINE2触发
	TRIG_LINE3		= 3,	//触发源：LINE3触发
	TRIG_LINE4		= 4,	//触发源：LINE4触发
	TRIG_LINE5		= 5		//触发源：LINE5触发
}TRIGSOURCE;

// 相机初始化配置参数
typedef struct tagCamPara
{
	int DeviceID;		//设备编号
	int Width;			//图像宽度
	int Height;			//图像高度
	int Brightness;		//亮度
	int Shutter;		//曝光时间
	int Contrast;		//对比度
	int Gain;			//增益
	int Hue;			//色度
	int Sharpness;		//锐度
	int Saturation;		//饱和度
	int OffsetX;		//图像X偏移
	int	OffsetY;		//图像Y偏移

	WORKMODE	WorkMode;		//工作类型，0为连续模式，1为触发模式
	TRIGSOURCE  TrigSource;		//触发源（触发模式时有效）


	// struct tagCamParam构造函数
	tagCamPara(int devID)
	{
		DeviceID = devID;		//设备编号
		WorkMode = UNKNOW_MODE;	//工作类型,0为连续模式，1为触发模式
		TrigSource = UNKNOW_SRC;//软触发（工作在触发模式下时该设置才生效）
		Brightness = -1;		//亮度
		Shutter = -1;			//曝光时间
		Contrast = -1;			//对比度
		Gain = -1;				//增益
		Hue = -1;				//色度
		Sharpness = -1;			//锐度
		Saturation = -1;		//饱和度
		Width = -1;				//图像宽度
		Height = -1;			//图像高度
		OffsetX = -1;			//图像X偏移
		OffsetY = -1;			//图像Y偏移		
	}

	tagCamPara()
	{
		DeviceID = -1;			//设备编号
		WorkMode = UNKNOW_MODE;	//工作类型,0为连续模式，1为触发模式
		TrigSource = UNKNOW_SRC;//软触发（工作在触发模式下时该设置才生效）
		Brightness = -1;		//亮度
		Shutter = -1;			//曝光时间
		Contrast = -1;			//对比度
		Gain = -1;				//增益
		Hue = -1;				//色度
		Sharpness = -1;			//锐度
		Saturation = -1;		//饱和度
		Width = -1;				//图像宽度
		Height = -1;			//图像高度
		OffsetX = -1;			//图像X偏移
		OffsetY = -1;			//图像Y偏移
	}
}CamPara;

typedef struct
{
	HObject image;
	int     imageNo;
}CameraImageAndNo;		// zhang 2019.08.19处理图像编号和检测结果

typedef void (__stdcall *STREAM_PROC)(HObject&img, void* pUserData, HTuple* extra, HTuple* extra2);


class DHCamera
{
public:
	DHCamera();
	virtual		~DHCamera();

	/************************************************************************/
	/* 相机初始化                                               
	/* 连接相机，并初始化相机配置
	/************************************************************************/
	bool		OpenCamera(CamPara& Para);
	bool		OpenCamera(int deviceID); 	
	bool		CloseCamera();		
	
	/************************************************************************/
	/* 相机ID及状态                                               
	/* 相机ID唯一标识一台相机,init时传入
	/* 状态：已连接、未连接
	/************************************************************************/
	int         GetDeviceID();
	bool		IsConnected();									// 是否已连接上相机



	/************************************************************************/
	/* 常用属性设置、属性读取                                                              
	/* 停止拉流、断开与相机连接，释放资源
	/************************************************************************/
	bool		SetWidth(int Value);							// 设置图像宽度
	bool		SetHeight(int Value);							// 设置图像高度
	bool		SetOffsetX(int Value);							// 设置x偏移
	bool		SetOffsetY(int Value);							// 设置Y偏移
	bool		SetGain(int Value);								// 设置增益
	bool		SetBrightness(int Value);						// 设置亮度
	bool		SetShutter(double Value);							// 设置曝光时间
	bool		SetContrast(int Value);							// 设置对比度
	bool		SetXRevise(bool ReviseOrNot = false);			// 设置X方向是否翻转
	bool		SetYRevise(bool ReviseOrNot = false);			// 设置Y方向是否翻转
	bool		SetWorkMode(WORKMODE Mode);						// 设置工作模式，触发或者非触发   
	bool	    SetTriggerSource(TRIGSOURCE TrigSrc);			// 设置触发源

	int			GetWidth();										// 获取图像宽度
	int			GetHeight();									// 获取图像高度
	int			GetOffsetX();									// 获取X偏移
	int			GetOffsetY();									// 获取Y偏移
	int			GetGain();										// 获取增益
	int			GetBrightness();								// 获取亮度
	int			GetShutter();									// 获取曝光时间
	int			GetContrast();									// 获取对比度
	WORKMODE	GetWorkMode();									// 获取工作模式，触发或者非触发 
	TRIGSOURCE  GetTriggerSource();								// 获取触发源
	bool		GetXRevise();									// 获取X方向是否翻转
	bool		GetYRevise();									// 获取Y方向是否翻转
	bool		GetPixelFormat(Infra::CString& pixFormat);

	bool		SetCamPropertys(CamPara& Para);					// 批量设置 
	bool		GetCamPropertys(CamPara& Para);					// 批量获取 

	/************************************************************************/
	/* 拉流控制                                                              
	/* 指示相机开始/停止采集图像
	/************************************************************************/
	bool		StartCapture();									// 开始捕获                              
	bool		StopCapture();		                            // 停止捕获
	bool		TriggerSoft();									// 软触发，每调用一次相机采集一张图片，软触发模式下有效
	


	/************************************************************************/	/* 获取相机采集到的原始图像数据
	/* 用户调用了SetStreamHook传入有效函数指针，则工作在回调模式下，WaitPicture获取不到图像,返回false
	/************************************************************************/

	bool		SetStreamHook(STREAM_PROC proc, void*);					  // 设置回调函数，每采集到一张图片回调函数被调用一次


private:

	int  EnumCameras();
	
	void DeviceLinkNotify(const GenICam::SConnectArg& conArg);	// 断线通知回调函数

	void TryResumeConn();										// 断线恢复尝试
	
	bool IpAutoConfig();										// IP自动配置（同网卡网段）
	
	void onGetFrame(const GenICam::CFrame& frame);
	//存储图像
	//std::queue<HObject> m_imgQueue;
	std::queue<CameraImageAndNo> m_imgQueue;//zhang 2019.08.20
	CameraImageAndNo CN;
	GenICam::StreamStatisticsInfo streamStatsInfo;
	bool m_dealThreadFlag;
	static UINT InvokeCallBack( LPVOID  pCallbackData);
private:

	CamPara			m_camPara;
	WORKMODE		m_workModeCur; 

	bool			m_bCapturingFlg;
	bool			m_bConnectFlg;

	HANDLE          m_trigFinish;
	uint32_t        m_buffSize;
	unsigned char * m_pBuff;

	int             m_waitingTime;					//毫秒
	bool			m_bRunning;

	GenICam::IAcquisitionControlPtr m_aquisitionCtrlPtr;



	public:

	
	std::string                 m_camKey;           // 相机唯一标识
	GenICam::IStreamSourcePtr	m_streamPtr;		// 流对象智能指针
	Infra::CMutex				m_buffMutex;        // buff 锁保护控制
	STREAM_PROC                 m_pStreamProc;
	void*                       m_pUserPtr;
GenICam::ICameraPtr			m_cameraSptr;		// 相机对象智能指针
	static std::vector<GenICam::ICameraPtr> g_DHCameraList;

};

#endif
