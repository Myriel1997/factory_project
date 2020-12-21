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
	long ImgData;//图像指针

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
	HTuple n_result;      //检测结果
	int    n_checkTime;  //zhang 2019.08.14 新增check时间，在inspection统计

	HObject defect_region;				//

	int n_save_image1[2];//保存图片标志
	

}ErrorRegion;		// 错误区域

typedef struct
{
	HObject image;
	int     imageNo;
}CameraImageAndNo;		// zhang 2019.08.19处理图像编号和检测结果
typedef struct{
	int Defection;   //缺陷加权密度
	bool AlarmFlag;    //是否报警
	int Width;      //每个相片的黑色区域的宽度（包含重叠像素）
	char Comment[128];   //报警说明
	float Calc_Width;   //计算的图像宽度（毫米）
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