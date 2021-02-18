#pragma once

class LED {
public:
	LED();
	~LED();
	void Init(WORD IO);
	void Open();
	void Close();
	void Toggle();
	int ReadState();
	void SetIO(WORD IO);
	WORD GetIO();
private:
	int m_State;
	WORD m_IO;
};