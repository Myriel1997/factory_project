#ifndef SPOUTCTRL_H
#define SPOUTCTRL_H

#include "stdafx.h"
#include <MMSystem.h>

#pragma comment(lib,"winmm")

class Spout {
public:
	int m_ID;
public:
	Spout();
	~Spout() {};
	void Init(int ID, WORD IO, unsigned int openTime);
	void Open();
	static void CALLBACK TimerProc(
		UINT uDelay, UINT uResolution,
		LPTIMECALLBACK lpTimeProc, DWORD_PTR dwUser, UINT fuEvent);
	void StopTimer();
private:
	WORD m_IO;
	unsigned int m_OpenTime;
	LPTIMECALLBACK m_TimerProc;
	MMRESULT Timer;
};

#endif // !SPOUTCTRL_H

