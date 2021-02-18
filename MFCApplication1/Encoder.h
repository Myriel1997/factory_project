#pragma once
class Encoder
{
public:
	long m_EncoderData;
public:
	Encoder();
	~Encoder();
public:
	long GetEncoderData();
	void Start();
	void Stop();
private:
};