#include "stdafx.h"
#include "init.h"
#include "CirQue.h"
#include "CamCtrl.h"
#include "SpoutCtrl.h"
#include "MFCApplication1Dlg.h"

extern long encodeNum;
extern CirQue *queObj;				// ��Ʒ���У�δ��⣩
extern CirQue *queOK, *queNG;		// OK���к�NG����
extern HANDLE threadBlowOKEvent;
extern HANDLE threadBlowNGEvent;
extern int objPos;
extern CMFCApplication1Dlg *dlg;	// �����ָ��

SingleObj *CreateObj()
{
	SingleObj *obj = (SingleObj *)malloc(sizeof(SingleObj));
	for (int i = 0; i < CAMNUM; i++) {
		obj->img[i] = nullptr;			// ͼ��ָ���ʼ��
		obj->camGot[i] = false;			// δ����
		obj->res[i] = UN;				// Ĭ�Ͻ��ΪUN = 1
		obj->finalRes = UN;				// Ĭ�Ͻ��ΪUN
	}
	
	obj->position = 0;
	obj->infrEncode = 0;	
	obj->isCheckEnding = false;	// δ������
	

	return obj;
}

/****************** ����Ʒ���д���*****************/

// �Ƿ񴥷����
void CamProcess(CirQue* CQ, int i)
{
	// ������Ʒ��λ��
	CQ->grpObj[i]->position = encodeNum - queObj->grpObj[i]->infrEncode;
	if ((CQ->grpObj[i]->position > pulseToCam0)
		&& !queObj->grpObj[i]->camGot[0]) {
		objPos = i;// ��¼���ĸ���Ʒ���������
		OpenCam(0);// �������0
	}
	else if ((CQ->grpObj[i]->position > pulseToCam1)
		&& !queObj->grpObj[i]->camGot[1]) {
		objPos = i;
		OpenCam(1);// �������1
	}
	else if ((CQ->grpObj[i]->position > pulseToCam2)
		&& !queObj->grpObj[i]->camGot[2]) {
		objPos = i;
		OpenCam(2);// �������2
	}
	else if ((CQ->grpObj[i]->position > pulseToCam3)
		&& !queObj->grpObj[i]->camGot[3]) {
		objPos = i;
		OpenCam(3);// �������3
	}
}

// �Ƿ񴥷�����
void SpoutOKProcess(CirQue* CQ, int i)
{
	CQ->grpObj[i]->position = encodeNum - CQ->grpObj[i]->infrEncode;
	if (CQ->grpObj[i]->position > pulseToBlowOK) {
		// ����OK���
		dlg->OpenOKSpout();

		// ɾ���������
		Pop(CQ);
	}
}

void SpoutNGProcess(CirQue* CQ, int i)
{
	CQ->grpObj[i]->position = encodeNum - CQ->grpObj[i]->infrEncode;
	if (CQ->grpObj[i]->position > pulseToBlowNG) {
		// ����NG���
		dlg->OpenNGSpout();

		// ɾ���������
		Pop(CQ);
	}
}