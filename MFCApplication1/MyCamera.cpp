#include "MyCamera.h"
#include "LTDMC.h"

void  __stdcall CallBackN(HObject&img, void* pUserData, HTuple* pNumber);

MyCamera::MyCamera(int camidx, STREAM_PROC imgproc, GrabType gbtype):DHGrabExport(camidx, CallBackN, gbtype)
{
	m_IO = camidx;
}

void MyCamera::Start()
{
	openCamera();
	setExposure(40);
	startCap(1);
}

void MyCamera::Triggle()
{
	dmc_write_outbit(0, m_IO, 0);	// 低电平触发回调函数
	Sleep(2);
	dmc_write_outbit(0, m_IO, 1);
}

void MyCamera::Stop()
{
	stopCap();
	closeCamera();
}
