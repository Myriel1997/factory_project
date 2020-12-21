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


//����ģʽ-����
#define TRIGMODE_ON_STR			 "On"

//����ģʽ-�رգ�������ģʽ
#define TRIGMODE_OFF_STR		 "Off"

//�Զ��ع�-�رգ���ʱ��ʹ���Զ����ع�ʱ��
#define EXPOSUREAUTO_OFF_STR     "Off"

//�Զ�����-�رգ���ʱ��ʹ���Զ�������
#define GAINAUTO_OFF_STR		 "Off"

//�ⴥ���½�����Ч
#define TRIGACT_FALLINGEDGE_STR  "FallingEdge"

//�ⴥ����������Ч
#define TRIGACT_RISINGEDGE_STR   "RisingEdge"

//����ԴΪ����
#define TRIGSRC_SOFT_STR		 "Software"

//����ԴΪLINE����
#define TRIGSRC_LINE1_STR		 "Line1"
#define TRIGSRC_LINE2_STR		 "Line2"
#define TRIGSRC_LINE3_STR		 "Line3"
#define TRIGSRC_LINE4_STR		 "Line4"
#define TRIGSRC_LINE5_STR		 "Line5"

typedef enum enumWORKMODE
{
	UNKNOW_MODE = -1,
	CONMODE		= 0,	//����ģʽ
	TRIGMODE	= 1		//����ģʽ
}WORKMODE;

// ����Դ���������ⴥ������������ģʽ����Ч
typedef enum enumTRIGSRC
{
	UNKNOW_SRC		= -1,
	TRIG_SOFT		= 0,	//����Դ������
	TRIG_LINE1		= 1,	//����Դ��LINE1����
	TRIG_LINE2		= 2,	//����Դ��LINE2����
	TRIG_LINE3		= 3,	//����Դ��LINE3����
	TRIG_LINE4		= 4,	//����Դ��LINE4����
	TRIG_LINE5		= 5		//����Դ��LINE5����
}TRIGSOURCE;

// �����ʼ�����ò���
typedef struct tagCamPara
{
	int DeviceID;		//�豸���
	int Width;			//ͼ����
	int Height;			//ͼ��߶�
	int Brightness;		//����
	int Shutter;		//�ع�ʱ��
	int Contrast;		//�Աȶ�
	int Gain;			//����
	int Hue;			//ɫ��
	int Sharpness;		//���
	int Saturation;		//���Ͷ�
	int OffsetX;		//ͼ��Xƫ��
	int	OffsetY;		//ͼ��Yƫ��

	WORKMODE	WorkMode;		//�������ͣ�0Ϊ����ģʽ��1Ϊ����ģʽ
	TRIGSOURCE  TrigSource;		//����Դ������ģʽʱ��Ч��


	// struct tagCamParam���캯��
	tagCamPara(int devID)
	{
		DeviceID = devID;		//�豸���
		WorkMode = UNKNOW_MODE;	//��������,0Ϊ����ģʽ��1Ϊ����ģʽ
		TrigSource = UNKNOW_SRC;//�����������ڴ���ģʽ��ʱ�����ò���Ч��
		Brightness = -1;		//����
		Shutter = -1;			//�ع�ʱ��
		Contrast = -1;			//�Աȶ�
		Gain = -1;				//����
		Hue = -1;				//ɫ��
		Sharpness = -1;			//���
		Saturation = -1;		//���Ͷ�
		Width = -1;				//ͼ����
		Height = -1;			//ͼ��߶�
		OffsetX = -1;			//ͼ��Xƫ��
		OffsetY = -1;			//ͼ��Yƫ��		
	}

	tagCamPara()
	{
		DeviceID = -1;			//�豸���
		WorkMode = UNKNOW_MODE;	//��������,0Ϊ����ģʽ��1Ϊ����ģʽ
		TrigSource = UNKNOW_SRC;//�����������ڴ���ģʽ��ʱ�����ò���Ч��
		Brightness = -1;		//����
		Shutter = -1;			//�ع�ʱ��
		Contrast = -1;			//�Աȶ�
		Gain = -1;				//����
		Hue = -1;				//ɫ��
		Sharpness = -1;			//���
		Saturation = -1;		//���Ͷ�
		Width = -1;				//ͼ����
		Height = -1;			//ͼ��߶�
		OffsetX = -1;			//ͼ��Xƫ��
		OffsetY = -1;			//ͼ��Yƫ��
	}
}CamPara;

typedef struct
{
	HObject image;
	int     imageNo;
}CameraImageAndNo;		// zhang 2019.08.19����ͼ���źͼ����

typedef void (__stdcall *STREAM_PROC)(HObject&img, void* pUserData, HTuple* extra, HTuple* extra2);


class DHCamera
{
public:
	DHCamera();
	virtual		~DHCamera();

	/************************************************************************/
	/* �����ʼ��                                               
	/* �������������ʼ���������
	/************************************************************************/
	bool		OpenCamera(CamPara& Para);
	bool		OpenCamera(int deviceID); 	
	bool		CloseCamera();		
	
	/************************************************************************/
	/* ���ID��״̬                                               
	/* ���IDΨһ��ʶһ̨���,initʱ����
	/* ״̬�������ӡ�δ����
	/************************************************************************/
	int         GetDeviceID();
	bool		IsConnected();									// �Ƿ������������



	/************************************************************************/
	/* �����������á����Զ�ȡ                                                              
	/* ֹͣ�������Ͽ���������ӣ��ͷ���Դ
	/************************************************************************/
	bool		SetWidth(int Value);							// ����ͼ����
	bool		SetHeight(int Value);							// ����ͼ��߶�
	bool		SetOffsetX(int Value);							// ����xƫ��
	bool		SetOffsetY(int Value);							// ����Yƫ��
	bool		SetGain(int Value);								// ��������
	bool		SetBrightness(int Value);						// ��������
	bool		SetShutter(double Value);							// �����ع�ʱ��
	bool		SetContrast(int Value);							// ���öԱȶ�
	bool		SetXRevise(bool ReviseOrNot = false);			// ����X�����Ƿ�ת
	bool		SetYRevise(bool ReviseOrNot = false);			// ����Y�����Ƿ�ת
	bool		SetWorkMode(WORKMODE Mode);						// ���ù���ģʽ���������߷Ǵ���   
	bool	    SetTriggerSource(TRIGSOURCE TrigSrc);			// ���ô���Դ

	int			GetWidth();										// ��ȡͼ����
	int			GetHeight();									// ��ȡͼ��߶�
	int			GetOffsetX();									// ��ȡXƫ��
	int			GetOffsetY();									// ��ȡYƫ��
	int			GetGain();										// ��ȡ����
	int			GetBrightness();								// ��ȡ����
	int			GetShutter();									// ��ȡ�ع�ʱ��
	int			GetContrast();									// ��ȡ�Աȶ�
	WORKMODE	GetWorkMode();									// ��ȡ����ģʽ���������߷Ǵ��� 
	TRIGSOURCE  GetTriggerSource();								// ��ȡ����Դ
	bool		GetXRevise();									// ��ȡX�����Ƿ�ת
	bool		GetYRevise();									// ��ȡY�����Ƿ�ת
	bool		GetPixelFormat(Infra::CString& pixFormat);

	bool		SetCamPropertys(CamPara& Para);					// �������� 
	bool		GetCamPropertys(CamPara& Para);					// ������ȡ 

	/************************************************************************/
	/* ��������                                                              
	/* ָʾ�����ʼ/ֹͣ�ɼ�ͼ��
	/************************************************************************/
	bool		StartCapture();									// ��ʼ����                              
	bool		StopCapture();		                            // ֹͣ����
	bool		TriggerSoft();									// ������ÿ����һ������ɼ�һ��ͼƬ������ģʽ����Ч
	


	/************************************************************************/	/* ��ȡ����ɼ�����ԭʼͼ������
	/* �û�������SetStreamHook������Ч����ָ�룬�����ڻص�ģʽ�£�WaitPicture��ȡ����ͼ��,����false
	/************************************************************************/

	bool		SetStreamHook(STREAM_PROC proc, void*);					  // ���ûص�������ÿ�ɼ���һ��ͼƬ�ص�����������һ��


private:

	int  EnumCameras();
	
	void DeviceLinkNotify(const GenICam::SConnectArg& conArg);	// ����֪ͨ�ص�����

	void TryResumeConn();										// ���߻ָ�����
	
	bool IpAutoConfig();										// IP�Զ����ã�ͬ�������Σ�
	
	void onGetFrame(const GenICam::CFrame& frame);
	//�洢ͼ��
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

	int             m_waitingTime;					//����
	bool			m_bRunning;

	GenICam::IAcquisitionControlPtr m_aquisitionCtrlPtr;



	public:

	
	std::string                 m_camKey;           // ���Ψһ��ʶ
	GenICam::IStreamSourcePtr	m_streamPtr;		// ����������ָ��
	Infra::CMutex				m_buffMutex;        // buff ����������
	STREAM_PROC                 m_pStreamProc;
	void*                       m_pUserPtr;
GenICam::ICameraPtr			m_cameraSptr;		// �����������ָ��
	static std::vector<GenICam::ICameraPtr> g_DHCameraList;

};

#endif
