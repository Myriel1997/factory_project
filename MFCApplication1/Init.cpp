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

// 是否只能用HObject &img来获取图像
void  __stdcall CallBackN(HObject&img, void* pUserData, HTuple* pNumber)
{
	int i = (int)(*(int *)pUserData);
	HTuple p, t, w, h;
	// 获取图像
	GetImagePointer1(img, &p, &t, &w, &h);//get_image_pointer1 (Image, Pointer, Type, Width, Height)
	CopyObj(img, &m_imgobj[i], 1, -1);

	// 将未检测队列对应相机标记记1
	queObj->grpObj[objPos]->camGot[i] = true;

	// 获取单张照片结果
	// queObj->grpObj[objPos]->res[i] = prosess();

	// 保存图像
	CFileInfo file;
	CString modelParaPathUP = file.GetModelPathUP(1);
	CString str_camindex;
	str_camindex.Format("%d", i);
	CString img_save_route = modelParaPathUP + "template/ModelCamera" + str_camindex + ".bmp";
	WriteImage(m_imgobj[i], "bmp", 0, (HTuple)img_save_route);

	
	// 如果是相机3
	if (i == 3) {
		// 检测最终结果是四张照片检测结果相与
		queObj->grpObj[objPos]->finalRes = OK;
			//queObj->grpObj[objPos]->res[0] & 
			//queObj->grpObj[objPos]->res[1] & 
			//queObj->grpObj[objPos]->res[2] & 
			//queObj->grpObj[objPos]->res[3];
		queObj->grpObj[objPos]->isCheckEnding = true;
		// 复制对象，作为临时变量，避免free
		SingleObj *cpyObj = (SingleObj *)malloc(sizeof(SingleObj));
		*cpyObj = *(queObj->grpObj[objPos]);
		// 根据检测结果将物品加入对应队列
		if (queObj->grpObj[objPos]->finalRes == OK)			// OK
			PushBack(queOK, cpyObj);
		else if (queObj->grpObj[objPos]->finalRes == NG)	// NG
			PushBack(queNG, cpyObj);
		// 在未检测队列中删除这个物品，如果是UN，就直接剔除，没有给到两个分类队列
		Pop(queObj);
	}
}

void motorInit()
{
	dmc_board_init();
	dmc_set_pulse_outmode(0, 0, 2);
	dmc_set_counter_inmode(0, 0, 3);
	dmc_sorting_close(0);	//关闭分拣功能 

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
	uint16 cameraCount = 4; //使用8个相机   
	int pCameraPos[4] = { 11000, 25000, 41000, 57000 };
	uint16 pCamIONo[4] = { 0,1,2,3 };
	uint32 cameraTime = 40;//相机触发持续时间为40*250us = 10ms   
	uint16 cameraTrigLevel = 0;//低电平触发相机   
	uint16 blowCnt = 2;// = 7;//吹气装置共7个   
	int blowPos[2] = { 79000, 110000 };
	uint16 blowIONo[2] = { 5,6 };

	int blowTime = 40;//吹气装置触发持续时间为4*250us = 1ms   
	uint16 blowTrigLevel = 0;//低电平触发吹气装置   
	uint16 checkMode = 0;//检测装置检测到物件后向控制卡输入低电平


	//设置物件参数   
	int maxWidth = 2500;//物件最大宽度2500个脉冲   
	int minWidth = 200;//物件最小宽度200个脉冲  
	int minDistance = 50;//物件最小间距50个脉冲  
	DWORD minTimeIntervel = 10 * 1e3;//最小时间间隔为10ms 


	//获取物件状态信息 
	uint32 pieceFind = 0;
	uint32 piecePassCam = 0;
	uint32 dist2next = 0;
	uint32 pieceWidth = 0;

	uint8 blowNo = 9; //那个吹气口吹气,默认第一个吹气口吹气

	DWORD blowTimetemp = blowTime * 4;

	//设置分拣参数   
	int iret = dmc_sorting_set_init_config(_CardID, cameraCount, pCameraPos, pCamIONo, cameraTime, cameraTrigLevel, blowCnt, blowPos, blowIONo, blowTime, blowTrigLevel, m_axis, dir, checkMode);
	dmc_sorting_set_blow_enable(_CardID, 1, 1);
	dmc_sorting_set_blow_enable(_CardID, 2, 1);


	//设置物件参数 
	DWORD wordmaxWidth = maxWidth;
	DWORD wordminWidth = minWidth;
	DWORD wordminDistance = minDistance;
	DWORD wordminTimeIntervel = minTimeIntervel * 1000;
	iret = dmc_sorting_set_piece_config(_CardID, maxWidth, minWidth, minDistance, wordminTimeIntervel);

	int continuengnumber = 0;
	//开启分拣功能   
	iret = dmc_sorting_start(_CardID);

	DWORD blow2trinum = 0;
	DWORD blow2trinumbefore = 0;
	DWORD beforeCQ2 = 0;
	DWORD blow1trinum = 0;
	DWORD beforeCQ1 = 0;

	dmc_sorting_set_camera_trig_count(0, 1, 0);
	dmc_sorting_set_camera_trig_count(0, 2, 0);
	dmc_sorting_set_camera_trig_count(0, 3, 0);
	dmc_write_outbit(0, 14, 0);//打开黄色灯
}

void cameraInit()
{
	for (int i = 0;i < CAMNUM;i++)
	{
		g_pGrabber[i] = new DHGrabExport(i, CallBackN, (GrabType)1);// 1、相机；2、回调函数；3、采集卡类型
		// 打开相机
		g_pGrabber[i]->openCamera();
		// 设置相机曝光时间
		g_pGrabber[i]->setExposure(40);
		// 获得照片的宽和高
		// m_nWidth[i] = g_pGrabber[i]->pCCDCtrl->Width;
		// m_nHeight[i] = g_pGrabber[i]->pCCDCtrl->Height;
		// 开始采集流
		g_pGrabber[i]->startCap(1);//0 连续模式 1 触发模式
	}
	Sleep(1000);
}