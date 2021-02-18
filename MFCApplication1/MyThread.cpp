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
extern Spout g_OKSpout, g_NGSpout;				// 喷口
extern MyCamera *g_Camera[4];
extern InfrSenr g_InfrSenr;
extern Encoder g_Encoder;
extern CCriticalSection  g_criticalSect;
extern CMFCApplication1Dlg *dlg1;	// 总类的指针
extern int objPos;

/****************** 对物品进行处理*****************/

// 函数：遍历判断是否需要处理图片，需要就处理
// 输入：CQ:未处理对了，i：物品的数组下标
void PicProcess(CirQue* CQ, int i)
{
	imgBack *imgRes;
	// j：遍历第i个物品四个相机
	for (int j = 0; j < CAMNUM; j++) {
		// 物品i第j个照片未检测 + 照片已取得 + 照片不为空
		if (!g_QueObj->grpObj[i]->isCheckEnding[j] && CQ->grpObj[i]->camGot[j]
			&& g_QueObj->grpObj[i]->img[j] != nullptr) {
			// 图像处理
			CQ->grpObj[i]->isChecking = true;
			imgRes = imageProcessing(*(CQ->grpObj[i]->img[j]), j);
			CQ->grpObj[i]->res[j] = imgRes->resultType;
			// dispRes[j] = imgRes->resultType;
			// 释放指针
			free(imgRes);
			CQ->grpObj[i]->isChecking = false;
			// 如果有一个是NG，那么之后拍的都不处理，并直接将最终结果赋值NG
			/*if (CQ->grpObj[i]->res[j] == NG) {
				for (int z = j; z < CAMNUM; z++) {
					CQ->grpObj[i]->isCheckEnding[z] = true;
				}
				CQ->grpObj[i]->finalRes = NG;
			}*/
		}
	}
}

// 是否触发相机
// i：物品，j：相机
void CamProcess(CirQue* CQ, int i)
{
	// 更新物品的位置
	CQ->grpObj[i]->position = g_Encoder.m_EncoderData - g_QueObj->grpObj[i]->infrEncode;
	// 遍历四个相机
	for (int j = 0; j < CAMNUM; j++) {
		// 判断是否触发相机
		if (!g_QueObj->grpObj[i]->camGot[j]
			&& (CQ->grpObj[i]->position > pulseToCam[j])) {
			g_criticalSect.Lock();		// 互斥锁上锁
			objPos = i;					// 记录是哪个物品触发该相机
			g_Camera[j]->Triggle();		// 触发相机j
			g_criticalSect.Unlock();	// 互斥锁下锁
			break;						// 一个物品一次只触发一次相机
		}
	}
}

// 是否触发喷嘴
void SpoutProcess(CirQue* CQ, Spout &spout)
{
	if (!CQ->isEmpty()) {
		CQ->GetFront()->position = g_Encoder.m_EncoderData - CQ->GetFront()->infrEncode;
		if (CQ->GetFront()->position > pulseToFlow[spout.m_ID]) {
			// 触发NG喷口
			spout.Open();
			// 删除这个物料
			CQ->Pop();
		}
	}
}

// 检查是否图片已经处理完需要入队
void ObjPopToQue(CirQue* CQ)
{
	if (!CQ->isEmpty()) {
		CQ->GetFront()->position = g_Encoder.m_EncoderData - CQ->GetFront()->infrEncode;
		// 当物品到达相机3和OK中间时，要进行分选
		if (CQ->GetFront()->position > pulseToClassify) {
			// 复制对象，作为临时变量，避免free
			SingleObj *cpyObj = (SingleObj *)malloc(sizeof(SingleObj));
			*cpyObj = *(CQ->GetFront());

			// 如果最终的检测结果不是NG，那么结果就是是四张照片检测结果相与
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
			// 将物品从未检测队列中弹出
			CQ->Pop();
			// 计算合格率
			dlg1->passRate = (double)dlg1->OKNum / (double)dlg1->objNum * 100;
			dlg1->strPassRate.Format(_T("%.2f%%"), dlg1->passRate);
		}
	}
}

/****************** 线程函数 *****************/

// 线程初始化
void threadInit(CMFCApplication1Dlg* classPoint)
{
	// 线程变量
	CWinThread *pThreadObject;
	LPVOID  ptThreadArg;
	ptThreadArg = (LPVOID)classPoint;

	// 线程初始化
	AfxBeginThread(threadQueue, ptThreadArg, THREAD_PRIORITY_TIME_CRITICAL, 0, 0, NULL);
	Sleep(100);
	AfxBeginThread(threadImageProcessing, ptThreadArg, THREAD_PRIORITY_TIME_CRITICAL, 0, 0, NULL);
	Sleep(100);
}

// 队列线程
UINT threadQueue(LPVOID ptThreadArg)
{
	CMFCApplication1Dlg* classPoint = (CMFCApplication1Dlg*)ptThreadArg;
	while (1) {
		if (classPoint->stateCheck) {
			static int infrStateCurr = 0;							// 红外传感器当前状态
			static int infrStateLast = 0;							// 红外传感器之前状态;
			// 检测物品是否到来
			g_Encoder.GetEncoderData();								// 获取编码器数据
			infrStateCurr = g_InfrSenr.GetInfraredSensorState();	// 读取红外数值
			if (!infrStateLast) {
				// 上升沿
				if (infrStateCurr) {
					SingleObj *obj = new SingleObj();				// 创建一个物品结构体
					obj->infrEncode = g_Encoder.m_EncoderData;		// 记录它在红外传感器处编码器值，用以计算差值
					g_QueObj->PushBack(obj);						// 加入队列
					classPoint->objNum++;							// 记录多少个物品被入队
				}
			}
			infrStateLast = infrStateCurr;

			// 检测队列是否需要拍照
			g_QueObj->TraQue(CamProcess);

			// 检测队列是否需要喷气
			SpoutProcess(g_QueOK, g_OKSpout);					// 检查OK队列头是否有物品达到OK喷口
			SpoutProcess(g_QueNG, g_NGSpout);					// 检查NG队列头是否有物品达到NG喷口
			
			// 界面显示数据
			classPoint->SendMessage(WM_UPDATE_MESSAGE, 0, 0);
		}
		if (dlg1->stateEnd) {
			return 0;
		}
	}
	return 0;
}

// 图片处理线程
UINT threadImageProcessing(LPVOID ptThreadArg)
{
	CMFCApplication1Dlg* classPoint = (CMFCApplication1Dlg*)ptThreadArg;
	while (1)  {
		if (classPoint->stateCheck){
			g_Encoder.GetEncoderData();			// 获取编码器数据
			// 遍历未处理队列，查看是否存在图片没有被处理的
			// 发现未处理的，就去处理图片
			g_QueObj->TraQue(PicProcess);
			ObjPopToQue(g_QueObj);
		}
		if (dlg1->stateEnd) {
			return 0;
		}
	}
	
	return 0;
}

