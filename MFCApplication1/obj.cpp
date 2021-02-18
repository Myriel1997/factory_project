#include "stdafx.h"
#include "CirQue.h"
#include "init.h"
#include "MFCApplication1Dlg.h"
#include "ImgDetection.h"
#include "obj.h"

SingleObj::SingleObj()
{
	for (int i = 0; i < CAMNUM; i++) {
		img[i] = nullptr;
		camGot[i] = false;			// 未经过
		res[i] = UN;				// 默认结果为UN = 1
		finalRes = UN;				// 默认结果为UN
		isCheckEnding[i] = false;	// 未检测完毕
		isChecking = false;
	}
	position = 0;
	infrEncode = 0;
}

//SingleObj *CreateObj()
//{
//	SingleObj *obj = (SingleObj *)malloc(sizeof(SingleObj));
//	for (int i = 0; i < CAMNUM; i++) {
//		obj->img[i] = nullptr;
//		obj->camGot[i] = false;			// 未经过
//		obj->res[i] = UN;				// 默认结果为UN = 1
//		obj->finalRes = UN;				// 默认结果为UN
//		obj->isCheckEnding[i] = false;	// 未检测完毕
//		obj->isChecking = false;
//	}
//	obj->position = 0;
//	obj->infrEncode = 0;	
//	
//
//	return obj;
//}

