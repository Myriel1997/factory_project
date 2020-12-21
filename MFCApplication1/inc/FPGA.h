#pragma once

#include "plxapi.h"
#define LINE_COUNTER         0                    //�м�������ַ
#define LINE_COUNTER_INIT_VALUE       0xFFFFFFFF          //�м�������ֵ
#define LABELER_COUNTER_BASE 1          //����������ַ
#define MAX_LABELER_COUNTER_INDEX  10         //�������������
#define OUTPUT_COUNTER_BASE  100        //�����������ַ
#define MAX_OUTPUT_COUNTER   12          //�������������
#define ALARM_COUNTER        101        //����������
#define CHANGE_LAP_COUNTER_BASE   109	                        //�����������ַ
#define CHANGE_LAP_COUNTER_INIT_VALUE       0xFFFFFFFF          //�����������ֵ
#define MAX_CHANGE_LAP_COUNTER 1								//��������������

/*���Ϊ�ⴥ��ʱ����������ɼ��źţ���ֵ��Ϊ0�� 
  ���Ϊ�ڴ���ʱ�������������������ӣ�Ϊ��ģ����������������ӣ���ֵӦ����0
  add by qq
*/
#define STEP				0    

#define MAX_LABELER          7          //��������
#define MAX_LABELER_COUNTER  10     //������������
const static int Labeler_Counter_Dealy_Base[MAX_LABELER]={1,11,21,31,41,51,61};       //1~6�����ʱ��������ַ
const static int Labeler_Counter_Duration_Base = 102;                              //1~6������������ַ
class _declspec(dllexport)  CFPGA
{
private:
	//HANDLE m_hDevice;
	PLX_DEVICE_OBJECT m_hDevice;
	int m_LabelerCounterIndex[MAX_LABELER];          //��ǰʹ�õĴ����������
	int m_LineCounterValueOffset;		//��ʼ���ʱƫ�Ƶ�����

	int LINSTEP;                        

public:
	CFPGA(void);

	~CFPGA(void);

	int open(void);

	int StartCounter(int channel,U32 initValue);  //ֱ������������
	U32 ReadCounter(int channel);                 //ֱ�Ӷ�ȡ������
	
	int StartLineCounter();     //�����м�����
	U32 ReadLineCounter();					 //���м�����
	U32 ReadLinFreq();                      //��ȡ��Ƶ
	//int StartLabelerCounter(U32 initValu);	   	     //������һ����������

	int StartLabelerCounter(int channel, U32 delay,U32 duration);//��·��꺯��
	int StartAlarmCounter(int interval);    //�����������������,��msΪ��λ

	int StartChangeLapCounter(int channel);     //�������������,channel ��1��ʼ
	U32 ReadChangeLapCounter(int channel);	    //�����������,channel ��1��ʼ
	U32 ReadChangeLapCounterWithReset(int channel);	    //�����������,channel ��1��ʼ����ȡ������
	
	//void SetLineCounterValueOffset(int checkedOffset,int imgheight,int grabCountRatio);//�����ʼ������ƫ����
	void SetLineCounterValueOffset(int checkedOffset,int imgheight);          //�����ʼ������ƫ����

};
