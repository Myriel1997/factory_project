#if !defined(CHECKPARA)
#define CHECKPARA

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "vector"
//#include "StdAfx.h"
#  include "HalconCpp.h"

using namespace std;
using namespace HalconCpp;

typedef struct
{
	long ImgData;//ͼ��ָ��

	int ProductionIndex;	

}StructSetModelPara;
typedef struct
{
	int ImgWidth;

	int ImgHeight;	

	int ProductionIndex;	

}StructInitPara;


typedef struct
{
	HTuple n_result;      //�����
	int    n_checkTime;  //zhang 2019.08.14 ����checkʱ�䣬��inspectionͳ��

	HObject defect_region;				//

	int n_save_image1[2];//����ͼƬ��־
	

}ErrorRegion;		// ��������

typedef struct
{
	HObject image;
	int     imageNo;
}CameraImageAndNo;		// zhang 2019.08.19����ͼ���źͼ����
typedef struct{
	int Defection;   //ȱ�ݼ�Ȩ�ܶ�
	bool AlarmFlag;    //�Ƿ񱨾�
	int Width;      //ÿ����Ƭ�ĺ�ɫ����Ŀ�ȣ������ص����أ�
	char Comment[128];   //����˵��
	float Calc_Width;   //�����ͼ���ȣ����ף�
}Assesment;

typedef struct{
	long ErrArea;
	double  CenterGrayVal;
}ErrClassifier;
//add huanghl
typedef struct{
	CString errorType;
	CString errorTypeDesc;
	CString errorImage;
}ErrInfo;
#endif