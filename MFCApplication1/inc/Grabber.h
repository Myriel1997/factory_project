/************************************************************************/
/* Copyright (c) 2006, 中国大恒集团北京图像视觉技术分公司研发二部     
/* All rights reserved.													
/*																		
/* 文件名称： Grabber.h												
/* 文件标识： 见配置管理计划书
/* 摘要： 采集卡（抽象基类）
/*
/* 当前版本： 1.0
/* 作者： 江卓佳,尹方宏
/* 完成日期： 2006年08月03日
/************************************************************************/

#if !defined(Grabber_h_)
#define Grabber_h_


const int GBMaxFileNameLen = 255;
const int GBMaxTextLen = 255;

typedef struct _GbSignalInfoStruct//回调信息结构
{
	void* Context;							//存放拥有回调函数的对象的this指针
	int nGrabberSN;							//采集序号
	int nErrorCode;							//错误代码：0：正常
	int nFrameCount;						//已采集的帧记数
	char strDescription[GBMaxFileNameLen];	//描述信息
	
}s_GBSIGNALINFO;//回调信息结构

//回调函数指针声明
typedef void (__stdcall *PGBCALLBACK)(const s_GBSIGNALINFO* SignalInfo);

typedef struct _GbInitStruct//采集卡初始化结构
{
	
	int nGrabberSN;							//采集序号
	char strDeviceName[GBMaxFileNameLen];	//采集设备名称
	char strGrabberFile[GBMaxFileNameLen];	//用于初始化的文件
	PGBCALLBACK CallBackFunc;				//回调函数指针
	void* Context;							//存放“调用初始化函数的对象”的this指针
	HWND hWndParent;

}s_GBINITSTRUCT;//采集卡初始化结构

typedef struct _GbErrorInfoStruct//错误信息结构
{
   	int nErrorCode;							//错误代码（0:正常）
	char strErrorDescription[GBMaxTextLen];	//错误描述
	char strErrorRemark[GBMaxTextLen];		//附加信息
}s_GBERRORINFO; //错误信息结构

enum GBParamID	//公共参数
{
	GBImageWidth = 0,		//图像宽度 (单位:字节)
	GBImageHeight,			//图像高度 (单位:字节)
	GBImagePixelSize,		//图像象素大小 (单位:字节)
	GBImageBufferSize,		//图像缓冲区大小 (单位:字节)
	GBImageBufferAddr		//图像缓冲区地址
};

//错误代码定义
const int GBOK	= 0;		//没有错误

//采集卡
class CGrabber
{
//操作
public:
	CGrabber()
	{
	}
	virtual ~CGrabber()
	{
	}
	
	/////////////////////////////////////////七个通用接口函数
	//初始化
	virtual int Init(const s_GBINITSTRUCT* pInitParam) = 0;

	//关闭
	virtual int Close() = 0;

	//开始采集
	virtual int StartGrab() = 0;

	//停止采集
	virtual int StopGrab() = 0;
	
	//设置参数
	virtual int SetParamInt(GBParamID Param, int nInputVal) = 0;
	
	//得到参数
	virtual int GetParamInt(GBParamID Param, int &nOutputVal) = 0;
	
	//调用参数对话框
	virtual void CallParamDialog(int *pCurrentImageHeight = NULL) = 0;

	//得到出错信息
	virtual void GetLastErrorInfo(s_GBERRORINFO *pErrorInfo) = 0 ;
	
};

#endif // !define(Grabber_h_)