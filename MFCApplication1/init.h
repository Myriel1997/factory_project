#ifndef INIT_H
#define INIT_H

#define CAMNUM 4
#define QUESIZE 50
#define OK		-1
#define UN		1
#define	NG		0

#include "DHGrabExport.h"
#include "CirQue.h"
#include "obj.h"

#define pulseToBlowOK	79000
#define pulseToBlowNG	110000
#define pulseToCam0		11000
#define pulseToCam1		25000
#define pulseToCam2		41000
#define pulseToCam3		57000

void motorInit();
void sortingInit();
void cameraInit();
void  __stdcall CallBackN(HObject&img, void* pUserData, HTuple* pNumber);

#endif // !INIT_H

