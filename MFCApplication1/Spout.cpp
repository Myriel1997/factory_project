#include "Spout.h"
#include "LTDMC.h"

Spout::Spout()
{
}

void Spout::Init(int ID, WORD IO, unsigned int openTime)
{
	m_ID = ID;
	m_IO = IO;
	m_OpenTime = openTime;
	m_TimerProc = (LPTIMECALLBACK)TimerProc;
}

// 喷嘴开启
void Spout::Open()
{
	dmc_write_outbit(0, m_IO, 0);// 开启
	// 开启定时器定时关闭
	Timer = timeSetEvent(m_OpenTime, 1,
		(LPTIMECALLBACK)m_TimerProc, (DWORD_PTR)this, TIME_ONESHOT);
}

// NG喷口定时关闭
void CALLBACK Spout::TimerProc(UINT uDelay,
	UINT uResolution, LPTIMECALLBACK lpTimeProc,
	DWORD_PTR dwUser, UINT fuEvent)
{
	Spout *p = (Spout *)dwUser;
	// 关闭NG喷口
	dmc_write_outbit(0, p->m_IO, 1);// 关闭NG喷口
}

// 关闭定时器
void Spout::StopTimer()
{

}