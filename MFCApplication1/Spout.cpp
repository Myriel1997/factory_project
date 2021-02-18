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

// ���쿪��
void Spout::Open()
{
	dmc_write_outbit(0, m_IO, 0);// ����
	// ������ʱ����ʱ�ر�
	Timer = timeSetEvent(m_OpenTime, 1,
		(LPTIMECALLBACK)m_TimerProc, (DWORD_PTR)this, TIME_ONESHOT);
}

// NG��ڶ�ʱ�ر�
void CALLBACK Spout::TimerProc(UINT uDelay,
	UINT uResolution, LPTIMECALLBACK lpTimeProc,
	DWORD_PTR dwUser, UINT fuEvent)
{
	Spout *p = (Spout *)dwUser;
	// �ر�NG���
	dmc_write_outbit(0, p->m_IO, 1);// �ر�NG���
}

// �رն�ʱ��
void Spout::StopTimer()
{

}