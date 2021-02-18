#ifndef OBJ_H
#define OBJ_H

#include "init.h"
#include "HObject.h"

class CirQue;// 前向声明

class SingleObj {
public:
	SingleObj();
	~SingleObj() {};
public:
	HObject *img[CAMNUM];	// 图片指针
	long position;			// 物品当前位置
	long infrEncode;		// 物品经过红外时编码器的值
	int res[CAMNUM];		// 各个相机照片获得结果：0-NG，1-UN，-1-OK
	int finalRes;			// 物品检测结果：0-NG，1-UN，-1-OK
	bool isCheckEnding[CAMNUM];		// 记录是否检测完毕：0-未完毕，1-完毕
	bool camGot[CAMNUM];	// 记录该相机已经对该物品拍摄过：0-拍过1-未拍
	bool isChecking;		// 是否该物品正在检查
private:

};


void ObjPopToQue(CirQue* CQ);
void PicProcess(CirQue* CQ, int i);
void CamProcess(CirQue* CQ, int i);
void SpoutOKProcess(CirQue* CQ);
void SpoutNGProcess(CirQue* CQ);

//typedef struct obj
//{
//	HObject *img[CAMNUM];	// 图片指针
//	long position;			// 物品当前位置
//	long infrEncode;		// 物品经过红外时编码器的值
//	int res[CAMNUM];		// 各个相机照片获得结果：0-NG，1-UN，-1-OK
//	int finalRes;			// 物品检测结果：0-NG，1-UN，-1-OK
//	bool isCheckEnding[CAMNUM];		// 记录是否检测完毕：0-未完毕，1-完毕
//	bool camGot[CAMNUM];	// 记录该相机已经对该物品拍摄过：0-拍过1-未拍
//	bool isChecking;		// 是否该物品正在检查
//}SingleObj;

//SingleObj *CreateObj();

#endif // !OBJ_H
