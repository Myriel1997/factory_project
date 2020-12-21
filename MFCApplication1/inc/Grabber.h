/************************************************************************/
/* Copyright (c) 2006, �й���㼯�ű���ͼ���Ӿ������ֹ�˾�з�����     
/* All rights reserved.													
/*																		
/* �ļ����ƣ� Grabber.h												
/* �ļ���ʶ�� �����ù���ƻ���
/* ժҪ�� �ɼ�����������ࣩ
/*
/* ��ǰ�汾�� 1.0
/* ���ߣ� ��׿��,������
/* ������ڣ� 2006��08��03��
/************************************************************************/

#if !defined(Grabber_h_)
#define Grabber_h_


const int GBMaxFileNameLen = 255;
const int GBMaxTextLen = 255;

typedef struct _GbSignalInfoStruct//�ص���Ϣ�ṹ
{
	void* Context;							//���ӵ�лص������Ķ����thisָ��
	int nGrabberSN;							//�ɼ����
	int nErrorCode;							//������룺0������
	int nFrameCount;						//�Ѳɼ���֡����
	char strDescription[GBMaxFileNameLen];	//������Ϣ
	
}s_GBSIGNALINFO;//�ص���Ϣ�ṹ

//�ص�����ָ������
typedef void (__stdcall *PGBCALLBACK)(const s_GBSIGNALINFO* SignalInfo);

typedef struct _GbInitStruct//�ɼ�����ʼ���ṹ
{
	
	int nGrabberSN;							//�ɼ����
	char strDeviceName[GBMaxFileNameLen];	//�ɼ��豸����
	char strGrabberFile[GBMaxFileNameLen];	//���ڳ�ʼ�����ļ�
	PGBCALLBACK CallBackFunc;				//�ص�����ָ��
	void* Context;							//��š����ó�ʼ�������Ķ��󡱵�thisָ��
	HWND hWndParent;

}s_GBINITSTRUCT;//�ɼ�����ʼ���ṹ

typedef struct _GbErrorInfoStruct//������Ϣ�ṹ
{
   	int nErrorCode;							//������루0:������
	char strErrorDescription[GBMaxTextLen];	//��������
	char strErrorRemark[GBMaxTextLen];		//������Ϣ
}s_GBERRORINFO; //������Ϣ�ṹ

enum GBParamID	//��������
{
	GBImageWidth = 0,		//ͼ���� (��λ:�ֽ�)
	GBImageHeight,			//ͼ��߶� (��λ:�ֽ�)
	GBImagePixelSize,		//ͼ�����ش�С (��λ:�ֽ�)
	GBImageBufferSize,		//ͼ�񻺳�����С (��λ:�ֽ�)
	GBImageBufferAddr		//ͼ�񻺳�����ַ
};

//������붨��
const int GBOK	= 0;		//û�д���

//�ɼ���
class CGrabber
{
//����
public:
	CGrabber()
	{
	}
	virtual ~CGrabber()
	{
	}
	
	/////////////////////////////////////////�߸�ͨ�ýӿں���
	//��ʼ��
	virtual int Init(const s_GBINITSTRUCT* pInitParam) = 0;

	//�ر�
	virtual int Close() = 0;

	//��ʼ�ɼ�
	virtual int StartGrab() = 0;

	//ֹͣ�ɼ�
	virtual int StopGrab() = 0;
	
	//���ò���
	virtual int SetParamInt(GBParamID Param, int nInputVal) = 0;
	
	//�õ�����
	virtual int GetParamInt(GBParamID Param, int &nOutputVal) = 0;
	
	//���ò����Ի���
	virtual void CallParamDialog(int *pCurrentImageHeight = NULL) = 0;

	//�õ�������Ϣ
	virtual void GetLastErrorInfo(s_GBERRORINFO *pErrorInfo) = 0 ;
	
};

#endif // !define(Grabber_h_)