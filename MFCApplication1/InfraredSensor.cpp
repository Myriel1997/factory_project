#include "LTDMC.h"
#include "InfraredSensor.h"

InfrSenr::InfrSenr()
{
	m_InfrSenrState = 0;
}

int InfrSenr::GetInfraredSensorState()
{
	m_InfrSenrState = dmc_read_inbit(0, 14);
	return m_InfrSenrState;
}