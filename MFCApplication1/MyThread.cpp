#include "stdafx.h"
#include "CirQue.h"
#include "MFCApplication1Dlg.h"
#include "ImgDetection.h"
#include "obj.h"
#include "MyThread.h"
#include <mmsystem.h>

#pragma comment(lib, "winmm")

int pulseToCam[4] = { pulseToCam0, pulseToCam1, pulseToCam2, pulseToCam3 };
int pulseToFlow[2] = { pulseToBlowOK, pulseToBlowNG };

extern CirQue *g_QueObj;
extern CirQue *g_QueOK, *g_QueNG;
extern Spout g_OKSpout, g_NGSpout;				// ���
extern MyCamera *g_Camera[4];
extern InfrSenr g_InfrSenr;
extern Encoder g_Encoder;
extern CCriticalSection  g_criticalSect;
extern CMFCApplication1Dlg *dlg1;	// �����ָ��
extern int objPos;

/****************** ����Ʒ���д���*****************/

// �����������ж��Ƿ���Ҫ����ͼƬ����Ҫ�ʹ���
// ���룺CQ:δ������ˣ�i����Ʒ�������±�
void PicProcess(CirQue* CQ, int i)
{
	imgBack *imgRes;
	// j��������i����Ʒ�ĸ����
	for (int j = 0; j < CAMNUM; j++) {
		// ��Ʒi��j����Ƭδ��� + ��Ƭ��ȡ�� + ��Ƭ��Ϊ��
		if (!g_QueObj->grpObj[i]->isCheckEnding[j] && CQ->grpObj[i]->camGot[j]
			&& g_QueObj->grpObj[i]->img[j] != nullptr) {
			// ͼ����
			CQ->grpObj[i]->isChecking = true;
			imgRes = imageProcessing(*(CQ->grpObj[i]->img[j]), j);
			CQ->grpObj[i]->res[j] = imgRes->resultType;
			// dispRes[j] = imgRes->resultType;
			// �ͷ�ָ��
			free(imgRes);
			CQ->grpObj[i]->isChecking = false;
			// �����һ����NG����ô֮���ĵĶ���������ֱ�ӽ����ս����ֵNG
			/*if (CQ->grpObj[i]->res[j] == NG) {
				for (int z = j; z < CAMNUM; z++) {
					CQ->grpObj[i]->isCheckEnding[z] = true;
				}
				CQ->grpObj[i]->finalRes = NG;
			}*/
		}
	}
}

// �Ƿ񴥷����
// i����Ʒ��j�����
void CamProcess(CirQue* CQ, int i)
{
	// ������Ʒ��λ��
	CQ->grpObj[i]->position = g_Encoder.m_EncoderData - g_QueObj->grpObj[i]->infrEncode;
	// �����ĸ����
	for (int j = 0; j < CAMNUM; j++) {
		// �ж��Ƿ񴥷����
		if (!g_QueObj->grpObj[i]->camGot[j]
			&& (CQ->grpObj[i]->position > pulseToCam[j])) {
			g_criticalSect.Lock();		// ����������
			objPos = i;					// ��¼���ĸ���Ʒ���������
			g_Camera[j]->Triggle();		// �������j
			g_criticalSect.Unlock();	// ����������
			break;						// һ����Ʒһ��ֻ����һ�����
		}
	}
}

// �Ƿ񴥷�����
void SpoutProcess(CirQue* CQ, Spout &spout)
{
	if (!CQ->isEmpty()) {
		CQ->GetFront()->position = g_Encoder.m_EncoderData - CQ->GetFront()->infrEncode;
		if (CQ->GetFront()->position > pulseToFlow[spout.m_ID]) {
			// ����NG���
			spout.Open();
			// ɾ���������
			CQ->Pop();
		}
	}
}

// ����Ƿ�ͼƬ�Ѿ���������Ҫ���
void ObjPopToQue(CirQue* CQ)
{
	if (!CQ->isEmpty()) {
		CQ->GetFront()->position = g_Encoder.m_EncoderData - CQ->GetFront()->infrEncode;
		// ����Ʒ�������3��OK�м�ʱ��Ҫ���з�ѡ
		if (CQ->GetFront()->position > pulseToClassify) {
			// ���ƶ�����Ϊ��ʱ����������free
			SingleObj *cpyObj = (SingleObj *)malloc(sizeof(SingleObj));
			*cpyObj = *(CQ->GetFront());

			// ������յļ��������NG����ô���������������Ƭ���������
			//if (g_QueObj->grpObj[CQ->front]->finalRes != NG) {
			CQ->GetFront()->finalRes =
				CQ->GetFront()->res[0] &
				CQ->GetFront()->res[1] &
				CQ->GetFront()->res[2] &
				CQ->GetFront()->res[3];
			//}

			if (CQ->GetFront()->finalRes == OK) {// OK
				g_QueOK->PushBack(cpyObj);
				dlg1->OKNum++;
			}
			else if (CQ->GetFront()->finalRes == NG) {// NG
				g_QueNG->PushBack(cpyObj);
				dlg1->NGNum++;
			}
			// ����Ʒ��δ�������е���
			CQ->Pop();
			// ����ϸ���
			dlg1->passRate = (double)dlg1->OKNum / (double)dlg1->objNum * 100;
			dlg1->strPassRate.Format(_T("%.2f%%"), dlg1->passRate);
		}
	}
}

/****************** �̺߳��� *****************/

// �̳߳�ʼ��
void threadInit(CMFCApplication1Dlg* classPoint)
{
	// �̱߳���
	CWinThread *pThreadObject;
	LPVOID  ptThreadArg;
	ptThreadArg = (LPVOID)classPoint;

	// �̳߳�ʼ��
	AfxBeginThread(threadQueue, ptThreadArg, THREAD_PRIORITY_TIME_CRITICAL, 0, 0, NULL);
	Sleep(100);
	AfxBeginThread(threadImageProcessing, ptThreadArg, THREAD_PRIORITY_TIME_CRITICAL, 0, 0, NULL);
	Sleep(100);
}

// �����߳�
UINT threadQueue(LPVOID ptThreadArg)
{
	CMFCApplication1Dlg* classPoint = (CMFCApplication1Dlg*)ptThreadArg;
	while (1) {
		if (classPoint->stateCheck) {
			static int infrStateCurr = 0;							// ���⴫������ǰ״̬
			static int infrStateLast = 0;							// ���⴫����֮ǰ״̬;
			// �����Ʒ�Ƿ���
			g_Encoder.GetEncoderData();								// ��ȡ����������
			infrStateCurr = g_InfrSenr.GetInfraredSensorState();	// ��ȡ������ֵ
			if (!infrStateLast) {
				// ������
				if (infrStateCurr) {
					SingleObj *obj = new SingleObj();				// ����һ����Ʒ�ṹ��
					obj->infrEncode = g_Encoder.m_EncoderData;		// ��¼���ں��⴫������������ֵ�����Լ����ֵ
					g_QueObj->PushBack(obj);						// �������
					classPoint->objNum++;							// ��¼���ٸ���Ʒ�����
				}
			}
			infrStateLast = infrStateCurr;

			// �������Ƿ���Ҫ����
			g_QueObj->TraQue(CamProcess);

			// �������Ƿ���Ҫ����
			SpoutProcess(g_QueOK, g_OKSpout);					// ���OK����ͷ�Ƿ�����Ʒ�ﵽOK���
			SpoutProcess(g_QueNG, g_NGSpout);					// ���NG����ͷ�Ƿ�����Ʒ�ﵽNG���
			
			// ������ʾ����
			classPoint->SendMessage(WM_UPDATE_MESSAGE, 0, 0);
		}
		if (dlg1->stateEnd) {
			return 0;
		}
	}
	return 0;
}

// ͼƬ�����߳�
UINT threadImageProcessing(LPVOID ptThreadArg)
{
	CMFCApplication1Dlg* classPoint = (CMFCApplication1Dlg*)ptThreadArg;
	while (1)  {
		if (classPoint->stateCheck){
			g_Encoder.GetEncoderData();			// ��ȡ����������
			// ����δ������У��鿴�Ƿ����ͼƬû�б������
			// ����δ����ģ���ȥ����ͼƬ
			g_QueObj->TraQue(PicProcess);
			ObjPopToQue(g_QueObj);
		}
		if (dlg1->stateEnd) {
			return 0;
		}
	}
	
	return 0;
}

