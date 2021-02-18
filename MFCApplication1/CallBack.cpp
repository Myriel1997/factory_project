#include "CirQue.h"
#include "MFCApplication1Dlg.h"
#include "HObject.h"
#include "LTDMC.h"
#include "ImgDetection.h"
#include "FileInfo.h"

CCriticalSection  g_criticalSect;

extern int res[4];
extern int OKNum;
extern int NGNum;
extern CirQue *g_QueObj;
extern CirQue *g_QueOK, *g_QueNG;
extern CMFCApplication1Dlg *dlg1;	// 总类的指针
HObject cpyImg[50][CAMNUM];

bool CamEnd = true;
int objPos = 0;					// 记录哪个物品触发相机

/****************** 相机回调函数*****************/
void  __stdcall CallBackN(HObject &img, void* pUserData, HTuple* pNumber)
{
	int i = (int)(*(int *)pUserData);

	HTuple p, t, w, h;
	// 获取图像
	GetImagePointer1(img, &p, &t, &w, &h);//get_image_pointer1 (Image, Pointer, Type, Width, Height)

	// 互斥锁上锁
	g_criticalSect.Lock();
	// 在队列对应物品结构体中加入图像
	CopyObj(img,&(cpyImg[objPos][i]),1,-1);
	g_QueObj->grpObj[objPos]->img[i] = &(cpyImg[objPos][i]);
	// 将未检测队列对应相机标记记1，表示对应相机已进行拍照
	g_QueObj->grpObj[objPos]->camGot[i] = true;
	// 互斥锁下锁
	g_criticalSect.Unlock();

	//// 保存图像
	///*CFileInfo file;
	//CString modelParaPathUP = file.GetModelPathUP(1);
	//CString str_camindex;
	//str_camindex.Format("%d", i);
	//CString img_save_route = modelParaPathUP + "template/ModelCamera" + str_camindex + ".bmp";
	//WriteImage(img, "bmp", 0, (HTuple)img_save_route);*/
	return ;
}
