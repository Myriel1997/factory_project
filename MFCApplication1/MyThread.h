#ifndef MY_THREAD_H
#define MY_THREAD_H

#include "MFCApplication1Dlg.h"

void threadInit(CMFCApplication1Dlg* classPoint);
UINT threadQueue(LPVOID ptThreadArg);
UINT threadImageProcessing(LPVOID ptThreadArg);

#endif // !MY_THREAD_H
