#pragma once

#include "plxapi.h"
#define LINE_COUNTER         0                    //行计数器地址
#define LINE_COUNTER_INIT_VALUE       0xFFFFFFFF          //行计数器初值
#define LABELER_COUNTER_BASE 1          //打标计数器基址
#define MAX_LABELER_COUNTER_INDEX  10         //打标计数器最大编号
#define OUTPUT_COUNTER_BASE  100        //输出计数器基址
#define MAX_OUTPUT_COUNTER   12          //输出计数器个数
#define ALARM_COUNTER        101        //报警计数器
#define CHANGE_LAP_COUNTER_BASE   109	                        //换卷计数器基址
#define CHANGE_LAP_COUNTER_INIT_VALUE       0xFFFFFFFF          //换卷计数器初值
#define MAX_CHANGE_LAP_COUNTER 1								//换卷计数器最大编号

/*相机为外触发时，编码器会采集信号，此值设为0； 
  相机为内触发时，编码器行数不会增加，为了模拟编码器行数的增加，此值应大于0
  add by qq
*/
#define STEP				0    

#define MAX_LABELER          7          //最多打标机数
#define MAX_LABELER_COUNTER  10     //最多打标计数器数
const static int Labeler_Counter_Dealy_Base[MAX_LABELER]={1,11,21,31,41,51,61};       //1~6打标延时计数器基址
const static int Labeler_Counter_Duration_Base = 102;                              //1~6打标持续行数基址
class _declspec(dllexport)  CFPGA
{
private:
	//HANDLE m_hDevice;
	PLX_DEVICE_OBJECT m_hDevice;
	int m_LabelerCounterIndex[MAX_LABELER];          //当前使用的打标计数器编号
	int m_LineCounterValueOffset;		//开始检测时偏移的行数

	int LINSTEP;                        

public:
	CFPGA(void);

	~CFPGA(void);

	int open(void);

	int StartCounter(int channel,U32 initValue);  //直接启动计数器
	U32 ReadCounter(int channel);                 //直接读取计数器
	
	int StartLineCounter();     //启动行计数器
	U32 ReadLineCounter();					 //读行计数器
	U32 ReadLinFreq();                      //读取行频
	//int StartLabelerCounter(U32 initValu);	   	     //启动下一个打标计数器

	int StartLabelerCounter(int channel, U32 delay,U32 duration);//多路打标函数
	int StartAlarmCounter(int interval);    //启动报警输出计数器,以ms为单位

	int StartChangeLapCounter(int channel);     //启动换卷计数器,channel 从1开始
	U32 ReadChangeLapCounter(int channel);	    //读换卷计数器,channel 从1开始
	U32 ReadChangeLapCounterWithReset(int channel);	    //读换卷计数器,channel 从1开始，读取后清零
	
	//void SetLineCounterValueOffset(int checkedOffset,int imgheight,int grabCountRatio);//计算初始行数的偏移量
	void SetLineCounterValueOffset(int checkedOffset,int imgheight);          //计算初始行数的偏移量

};
