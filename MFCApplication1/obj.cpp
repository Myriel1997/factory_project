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
		camGot[i] = false;			// δ����
		res[i] = UN;				// Ĭ�Ͻ��ΪUN = 1
		finalRes = UN;				// Ĭ�Ͻ��ΪUN
		isCheckEnding[i] = false;	// δ������
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
//		obj->camGot[i] = false;			// δ����
//		obj->res[i] = UN;				// Ĭ�Ͻ��ΪUN = 1
//		obj->finalRes = UN;				// Ĭ�Ͻ��ΪUN
//		obj->isCheckEnding[i] = false;	// δ������
//		obj->isChecking = false;
//	}
//	obj->position = 0;
//	obj->infrEncode = 0;	
//	
//
//	return obj;
//}

