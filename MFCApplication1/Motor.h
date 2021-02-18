#pragma once

class Motor {
public:
	
public:
	Motor();
	~Motor() {}
	void SetSpeed(int);
	int GetSpeed();
	void Init();
	void Start();
	void Stop();
	
private:
	int m_Speed;
};