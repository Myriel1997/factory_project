#pragma once

class InfrSenr {
public:
	InfrSenr();
	~InfrSenr() {};
public:
	int GetInfraredSensorState();
private:
	int m_InfrSenrState;
};