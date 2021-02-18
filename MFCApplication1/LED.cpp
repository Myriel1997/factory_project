#include "LTDMC.h"
#include "LED.h"

LED::LED()
{
}

LED::~LED()
{
	Close();
}

void LED::Init(WORD IO)
{
	SetIO(IO);
	Close();
}

void LED::Open()
{
	dmc_write_outbit(0, m_IO, 0);
	m_State = 0;
}

void LED::Close()
{
	dmc_write_outbit(0, m_IO, 1);
	m_State = 1;
}

void LED::SetIO(WORD IO)
{
	m_IO = IO;
}

WORD LED::GetIO()
{
	return m_IO;
}

int LED::ReadState()
{
	return m_State;
}

void LED::Toggle()
{
	if (m_State == 0)
		Close();
	else
		Open();
}

//void LED::Warning()
//{
//
//}