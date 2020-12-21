#ifndef OBJ_H
#define OBJ_H

#include "CirQue.h"
#include "DHGrabExport.h"

typedef struct CircuitQueue CirQue;// 前向声明

typedef struct obj
{
	HObject *img[CAMNUM];	// 图片指针
	long position;			// 物品当前位置
	long infrEncode;		// 物品经过红外时编码器的值
	int res[CAMNUM];		// 各个相机照片获得结果：0-NG，1-UN，-1-OK
	int finalRes;			// 物品检测结果：0-NG，1-UN，-1-OK
	bool isCheckEnding;		// 记录是否检测完毕：0-未完毕，1-完毕
	bool camGot[CAMNUM];	// 记录该相机已经对该物品拍摄过：0-拍过1-未拍
}SingleObj;

SingleObj *CreateObj();
void CamProcess(CirQue* CQ, int i);
void SpoutOKProcess(CirQue* CQ, int i);
void SpoutNGProcess(CirQue* CQ, int i);

#endif // !OBJ_H
