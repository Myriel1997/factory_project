#ifndef INIT_H
#define INIT_H


#include "MFCApplication1Dlg.h"
#include "HObject.h"

#define CAMNUM 4
#define QUESIZE 50
#define OK		-1
#define UN		1
#define	NG		0

#define pulseToBlowOK	84500
#define pulseToBlowNG	113000
#define pulseToCam0		16500
#define pulseToCam1		29900
#define pulseToCam2		44000
#define pulseToCam3		61800

#define pulseToClassify	76000

#define timeToKill		400
#define timeFlow		50

#define	stateStart		1
#define statePause		0

void  __stdcall CallBackN(HObject& img, void* pUserData, HTuple* pNumber);

#endif // !INIT_H
