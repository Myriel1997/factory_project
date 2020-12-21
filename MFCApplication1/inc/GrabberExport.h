

#if !defined(GrabberExport_h_)
#define GrabberExport_h_

#include "Grabber.h"

//////////////////////////////////////////////////////////////////////////
//DALSAר�ò���
enum Grabber
{
	SG = 0,   //ģ��ɼ���
	DS,       //DALSA X64�ɼ���
	AVT       //AVT 1394���
};

enum DSParamID	
{
	DSLineExternalTriggerOnOff = 0,  //�ⲿ������ʽ
	DSLineInternalTriggerOnOff,      //�ڲ�������ʽ
	DSLineInternalTriggerFreq,       //�ڲ�����Ƶ��ֵ
    DSLineInternalTriggerFreqmin,    //�ڲ�������СƵ��ֵ
    DSLineInternalTriggerFreqmax,    //�ڲ��������Ƶ��ֵ
	DSLineShaftEncoderTrigerOnOff,   //������������ʽ
	DSLineCropHeight,                //ͼ��߶�
	DSLineCropWidth,                 //ͼ����
	DSLineMaxCropHeight,			 //���ͼ��߶�
    DSFrameExternalTriggerOnOff,     //֡����ʹ��
	DSFrameExternalTriggerDetection, //֡��������
	DSFrameExternalTriggerLevel      //֡�����ź���ʽ
};

//DALSAר�ò���ֵ
enum DSParamVal
{
	DSLineTriggerOn = 0,
	DSLineTriggerOff
};
class CDALSACamDH;
class CSimulationCard;
//
//////////////////////////////////////////////////////////////////////////

//�ɼ���
class _declspec(dllexport) CDHGrabber : public CGrabber
{
//����
public:
	CDHGrabber(Grabber ID);
	virtual ~CDHGrabber();
	
	//��ʼ��
	int Init(const s_GBINITSTRUCT* pInitParam);

	//�ر�
	int Close();

	//��ʼ�ɼ�
	int StartGrab();

	//ֹͣ�ɼ�
	int StopGrab();
	
	//���ò���
	int SetParamInt(GBParamID Param, int nInputVal);
	
	//�õ�����
	int GetParamInt(GBParamID Param, int &nOutputVal);

	//���ò����Ի���
	void CallParamDialog(int *pCurrentImageHeight = NULL);

	//�õ�������Ϣ
	void GetLastErrorInfo(s_GBERRORINFO *pErrorInfo);

	//////////////////////////////////////////////////////////////////////////
	// DALSAר�нӿ�	
	int DSSetParamPro(DSParamID Param, int nInputVal);	
	int DSGetParamPro(DSParamID Param, int &nOutputVal);

	int DSSetParamPro(DSParamID Param, DSParamVal nInputVal);	
	int DSGetParamPro(DSParamID Param, DSParamVal& nOutputVal);

	int DSSetTriggerParam(DSParamVal ParamValInput);

	//���òɼ���������
// 	int DSGetAOI(RECT &rtAOI);
// 
// 	//���òɼ���������
// 	int DSSetAOI(RECT rtAOI);

	//����ɼ�
	int SnapShot();
	//
	//////////////////////////////////////////////////////////////////////////
//����
protected:
	CDALSACamDH *m_pGrabber;
	CSimulationCard *m_pSim;
	Grabber GlobalID;
};

#endif// !defined(GrabberExport_h_)
