#include "LTDMC.h"
#include "CamCtrl.h"
#include "DHGrabExport.h"
#include "init.h"

#include <Windows.h>

void OpenCam(WORD IO)
{
	dmc_write_outbit(0, IO, 0);
	Sleep(1);					// ���sleep���ó�ʲô�ȽϺ�
	dmc_write_outbit(0, IO, 1);
}

