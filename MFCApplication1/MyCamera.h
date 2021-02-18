#pragma once
#include "DHGrabExport.h"

class MyCamera :public DHGrabExport
{
public:
	MyCamera(int camidx, STREAM_PROC imgproc, GrabType gbtype);
	~MyCamera() {};
public:
	void Start();
	void Triggle();
	void Stop();
private:
	WORD m_IO;
};