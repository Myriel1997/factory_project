

#if !defined(GrabberExport_h_)
#define GrabberExport_h_

#include "Grabber.h"

//////////////////////////////////////////////////////////////////////////
//DALSA专用参数
enum Grabber
{
	SG = 0,   //模拟采集卡
	DS,       //DALSA X64采集卡
	AVT       //AVT 1394相机
};

enum DSParamID	
{
	DSLineExternalTriggerOnOff = 0,  //外部触发方式
	DSLineInternalTriggerOnOff,      //内部触发方式
	DSLineInternalTriggerFreq,       //内部触发频率值
    DSLineInternalTriggerFreqmin,    //内部触发最小频率值
    DSLineInternalTriggerFreqmax,    //内部触发最大频率值
	DSLineShaftEncoderTrigerOnOff,   //编码器触发方式
	DSLineCropHeight,                //图像高度
	DSLineCropWidth,                 //图像宽度
	DSLineMaxCropHeight,			 //最大图像高度
    DSFrameExternalTriggerOnOff,     //帧触发使能
	DSFrameExternalTriggerDetection, //帧触发极性
	DSFrameExternalTriggerLevel      //帧触发信号形式
};

//DALSA专用参数值
enum DSParamVal
{
	DSLineTriggerOn = 0,
	DSLineTriggerOff
};
class CDALSACamDH;
class CSimulationCard;
//
//////////////////////////////////////////////////////////////////////////

//采集类
class _declspec(dllexport) CDHGrabber : public CGrabber
{
//操作
public:
	CDHGrabber(Grabber ID);
	virtual ~CDHGrabber();
	
	//初始化
	int Init(const s_GBINITSTRUCT* pInitParam);

	//关闭
	int Close();

	//开始采集
	int StartGrab();

	//停止采集
	int StopGrab();
	
	//设置参数
	int SetParamInt(GBParamID Param, int nInputVal);
	
	//得到参数
	int GetParamInt(GBParamID Param, int &nOutputVal);

	//调用参数对话框
	void CallParamDialog(int *pCurrentImageHeight = NULL);

	//得到出错信息
	void GetLastErrorInfo(s_GBERRORINFO *pErrorInfo);

	//////////////////////////////////////////////////////////////////////////
	// DALSA专有接口	
	int DSSetParamPro(DSParamID Param, int nInputVal);	
	int DSGetParamPro(DSParamID Param, int &nOutputVal);

	int DSSetParamPro(DSParamID Param, DSParamVal nInputVal);	
	int DSGetParamPro(DSParamID Param, DSParamVal& nOutputVal);

	int DSSetTriggerParam(DSParamVal ParamValInput);

	//设置采集窗口区域
// 	int DSGetAOI(RECT &rtAOI);
// 
// 	//设置采集窗口区域
// 	int DSSetAOI(RECT rtAOI);

	//单贞采集
	int SnapShot();
	//
	//////////////////////////////////////////////////////////////////////////
//属性
protected:
	CDALSACamDH *m_pGrabber;
	CSimulationCard *m_pSim;
	Grabber GlobalID;
};

#endif// !defined(GrabberExport_h_)
