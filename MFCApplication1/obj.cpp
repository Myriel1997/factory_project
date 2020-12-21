#include "stdafx.h"
#include "init.h"
#include "CirQue.h"
#include "CamCtrl.h"
#include "SpoutCtrl.h"
#include "MFCApplication1Dlg.h"

extern long encodeNum;
extern CirQue *queObj;				// 物品队列（未检测）
extern CirQue *queOK, *queNG;		// OK队列和NG队列
extern HANDLE threadBlowOKEvent;
extern HANDLE threadBlowNGEvent;
extern int objPos;
extern CMFCApplication1Dlg *dlg;	// 总类的指针

SingleObj *CreateObj()
{
	SingleObj *obj = (SingleObj *)malloc(sizeof(SingleObj));
	for (int i = 0; i < CAMNUM; i++) {
		obj->img[i] = nullptr;			// 图像指针初始化
		obj->camGot[i] = false;			// 未经过
		obj->res[i] = UN;				// 默认结果为UN = 1
		obj->finalRes = UN;				// 默认结果为UN
	}
	
	obj->position = 0;
	obj->infrEncode = 0;	
	obj->isCheckEnding = false;	// 未检测完毕
	

	return obj;
}

/****************** 对物品进行处理*****************/

// 是否触发相机
void CamProcess(CirQue* CQ, int i)
{
	// 更新物品的位置
	CQ->grpObj[i]->position = encodeNum - queObj->grpObj[i]->infrEncode;
	if ((CQ->grpObj[i]->position > pulseToCam0)
		&& !queObj->grpObj[i]->camGot[0]) {
		objPos = i;// 记录是哪个物品触发该相机
		OpenCam(0);// 触发相机0
	}
	else if ((CQ->grpObj[i]->position > pulseToCam1)
		&& !queObj->grpObj[i]->camGot[1]) {
		objPos = i;
		OpenCam(1);// 触发相机1
	}
	else if ((CQ->grpObj[i]->position > pulseToCam2)
		&& !queObj->grpObj[i]->camGot[2]) {
		objPos = i;
		OpenCam(2);// 触发相机2
	}
	else if ((CQ->grpObj[i]->position > pulseToCam3)
		&& !queObj->grpObj[i]->camGot[3]) {
		objPos = i;
		OpenCam(3);// 触发相机3
	}
}

// 是否触发喷嘴
void SpoutOKProcess(CirQue* CQ, int i)
{
	CQ->grpObj[i]->position = encodeNum - CQ->grpObj[i]->infrEncode;
	if (CQ->grpObj[i]->position > pulseToBlowOK) {
		// 触发OK喷口
		dlg->OpenOKSpout();

		// 删除这个物料
		Pop(CQ);
	}
}

void SpoutNGProcess(CirQue* CQ, int i)
{
	CQ->grpObj[i]->position = encodeNum - CQ->grpObj[i]->infrEncode;
	if (CQ->grpObj[i]->position > pulseToBlowNG) {
		// 触发NG喷口
		dlg->OpenNGSpout();

		// 删除这个物料
		Pop(CQ);
	}
}