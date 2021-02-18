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
extern CMFCApplication1Dlg *dlg1;	// �����ָ��
HObject cpyImg[50][CAMNUM];

bool CamEnd = true;
int objPos = 0;					// ��¼�ĸ���Ʒ�������

/****************** ����ص�����*****************/
void  __stdcall CallBackN(HObject &img, void* pUserData, HTuple* pNumber)
{
	int i = (int)(*(int *)pUserData);

	HTuple p, t, w, h;
	// ��ȡͼ��
	GetImagePointer1(img, &p, &t, &w, &h);//get_image_pointer1 (Image, Pointer, Type, Width, Height)

	// ����������
	g_criticalSect.Lock();
	// �ڶ��ж�Ӧ��Ʒ�ṹ���м���ͼ��
	CopyObj(img,&(cpyImg[objPos][i]),1,-1);
	g_QueObj->grpObj[objPos]->img[i] = &(cpyImg[objPos][i]);
	// ��δ�����ж�Ӧ�����Ǽ�1����ʾ��Ӧ����ѽ�������
	g_QueObj->grpObj[objPos]->camGot[i] = true;
	// ����������
	g_criticalSect.Unlock();

	//// ����ͼ��
	///*CFileInfo file;
	//CString modelParaPathUP = file.GetModelPathUP(1);
	//CString str_camindex;
	//str_camindex.Format("%d", i);
	//CString img_save_route = modelParaPathUP + "template/ModelCamera" + str_camindex + ".bmp";
	//WriteImage(img, "bmp", 0, (HTuple)img_save_route);*/
	return ;
}
