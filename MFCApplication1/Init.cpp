#include "afxdialogex.h"
#include "LTDMC.h"
#include "init.h"
#include "DHGrabExport.h"
#include "FileInfo.h"

extern CirQue *queObj;
extern CirQue *queOK, *queNG;
DHGrabExport* g_pGrabber[CAMNUM] = { NULL,NULL,NULL,NULL };
HObject m_imgobj[CAMNUM];

int objPos = 0;

int _CardID = 0;
int m_axis = 0;
int dir = 1;

// �Ƿ�ֻ����HObject &img����ȡͼ��
void  __stdcall CallBackN(HObject&img, void* pUserData, HTuple* pNumber)
{
	int i = (int)(*(int *)pUserData);
	HTuple p, t, w, h;
	// ��ȡͼ��
	GetImagePointer1(img, &p, &t, &w, &h);//get_image_pointer1 (Image, Pointer, Type, Width, Height)
	CopyObj(img, &m_imgobj[i], 1, -1);

	// ��δ�����ж�Ӧ�����Ǽ�1
	queObj->grpObj[objPos]->camGot[i] = true;

	// ��ȡ������Ƭ���
	// queObj->grpObj[objPos]->res[i] = prosess();

	// ����ͼ��
	CFileInfo file;
	CString modelParaPathUP = file.GetModelPathUP(1);
	CString str_camindex;
	str_camindex.Format("%d", i);
	CString img_save_route = modelParaPathUP + "template/ModelCamera" + str_camindex + ".bmp";
	WriteImage(m_imgobj[i], "bmp", 0, (HTuple)img_save_route);

	
	// ��������3
	if (i == 3) {
		// ������ս����������Ƭ���������
		queObj->grpObj[objPos]->finalRes = OK;
			//queObj->grpObj[objPos]->res[0] & 
			//queObj->grpObj[objPos]->res[1] & 
			//queObj->grpObj[objPos]->res[2] & 
			//queObj->grpObj[objPos]->res[3];
		queObj->grpObj[objPos]->isCheckEnding = true;
		// ���ƶ�����Ϊ��ʱ����������free
		SingleObj *cpyObj = (SingleObj *)malloc(sizeof(SingleObj));
		*cpyObj = *(queObj->grpObj[objPos]);
		// ���ݼ��������Ʒ�����Ӧ����
		if (queObj->grpObj[objPos]->finalRes == OK)			// OK
			PushBack(queOK, cpyObj);
		else if (queObj->grpObj[objPos]->finalRes == NG)	// NG
			PushBack(queNG, cpyObj);
		// ��δ��������ɾ�������Ʒ�������UN����ֱ���޳���û�и��������������
		Pop(queObj);
	}
}

void motorInit()
{
	dmc_board_init();
	dmc_set_pulse_outmode(0, 0, 2);
	dmc_set_counter_inmode(0, 0, 3);
	dmc_sorting_close(0);	//�رշּ��� 

	dmc_set_sevon_enable(0,0,1);
	dmc_stop(0, 0, 1);
	dmc_set_profile(0, 0, 0, 10000, 0.1, 1, 0);
	dmc_set_s_profile(0, 0, 0, 0);
	dmc_set_position_unit(0, 0, 0);
	dmc_set_position(0, 0, 0);
	dmc_set_encoder(0, 0, 0);

}

void sortingInit()
{
	uint16 cameraCount = 4; //ʹ��8�����   
	int pCameraPos[4] = { 11000, 25000, 41000, 57000 };
	uint16 pCamIONo[4] = { 0,1,2,3 };
	uint32 cameraTime = 40;//�����������ʱ��Ϊ40*250us = 10ms   
	uint16 cameraTrigLevel = 0;//�͵�ƽ�������   
	uint16 blowCnt = 2;// = 7;//����װ�ù�7��   
	int blowPos[2] = { 79000, 110000 };
	uint16 blowIONo[2] = { 5,6 };

	int blowTime = 40;//����װ�ô�������ʱ��Ϊ4*250us = 1ms   
	uint16 blowTrigLevel = 0;//�͵�ƽ��������װ��   
	uint16 checkMode = 0;//���װ�ü�⵽���������ƿ�����͵�ƽ


	//�����������   
	int maxWidth = 2500;//��������2500������   
	int minWidth = 200;//�����С���200������  
	int minDistance = 50;//�����С���50������  
	DWORD minTimeIntervel = 10 * 1e3;//��Сʱ����Ϊ10ms 


	//��ȡ���״̬��Ϣ 
	uint32 pieceFind = 0;
	uint32 piecePassCam = 0;
	uint32 dist2next = 0;
	uint32 pieceWidth = 0;

	uint8 blowNo = 9; //�Ǹ������ڴ���,Ĭ�ϵ�һ�������ڴ���

	DWORD blowTimetemp = blowTime * 4;

	//���÷ּ����   
	int iret = dmc_sorting_set_init_config(_CardID, cameraCount, pCameraPos, pCamIONo, cameraTime, cameraTrigLevel, blowCnt, blowPos, blowIONo, blowTime, blowTrigLevel, m_axis, dir, checkMode);
	dmc_sorting_set_blow_enable(_CardID, 1, 1);
	dmc_sorting_set_blow_enable(_CardID, 2, 1);


	//����������� 
	DWORD wordmaxWidth = maxWidth;
	DWORD wordminWidth = minWidth;
	DWORD wordminDistance = minDistance;
	DWORD wordminTimeIntervel = minTimeIntervel * 1000;
	iret = dmc_sorting_set_piece_config(_CardID, maxWidth, minWidth, minDistance, wordminTimeIntervel);

	int continuengnumber = 0;
	//�����ּ���   
	iret = dmc_sorting_start(_CardID);

	DWORD blow2trinum = 0;
	DWORD blow2trinumbefore = 0;
	DWORD beforeCQ2 = 0;
	DWORD blow1trinum = 0;
	DWORD beforeCQ1 = 0;

	dmc_sorting_set_camera_trig_count(0, 1, 0);
	dmc_sorting_set_camera_trig_count(0, 2, 0);
	dmc_sorting_set_camera_trig_count(0, 3, 0);
	dmc_write_outbit(0, 14, 0);//�򿪻�ɫ��
}

void cameraInit()
{
	for (int i = 0;i < CAMNUM;i++)
	{
		g_pGrabber[i] = new DHGrabExport(i, CallBackN, (GrabType)1);// 1�������2���ص�������3���ɼ�������
		// �����
		g_pGrabber[i]->openCamera();
		// ��������ع�ʱ��
		g_pGrabber[i]->setExposure(40);
		// �����Ƭ�Ŀ�͸�
		// m_nWidth[i] = g_pGrabber[i]->pCCDCtrl->Width;
		// m_nHeight[i] = g_pGrabber[i]->pCCDCtrl->Height;
		// ��ʼ�ɼ���
		g_pGrabber[i]->startCap(1);//0 ����ģʽ 1 ����ģʽ
	}
	Sleep(1000);
}