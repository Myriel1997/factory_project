// CCDCtrl.h : header file
//

#if !defined(AFX_CCDCTRL_H__768B1DBD_17E4_4036_8FBA_2782794F7948__INCLUDED_)
#define AFX_CCDCTRL_H__768B1DBD_17E4_4036_8FBA_2782794F7948__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CCCTRL

#include "DHCamera.h"

#include "DHGrabExport.h"

#define  CAMERA_MAX_COUNT  4



#define  MAX_WIDTH  5120
#define  MAX_HEIGHT 8192



class  CCCDCtrl
{	
public:
	
	int nIndex;
	
	int CCD_ID;
	int CCD_OK; 
	
	BYTE mRGBBuf[MAX_WIDTH*MAX_HEIGHT];
	BYTE mRGBBuf2[MAX_WIDTH*MAX_HEIGHT];
	
	int Width;
	int Height;
	int ImageOK;
	int CCD_ADD;
	DHCamera m_camera;
	
	CCCDCtrl(STREAM_PROC imgproc);
	
	~CCCDCtrl();
	
	int SoftTrigger();
	
	int Init();
	
	int Exit();

	
	int StartCapture();
	int StartCapture(int mode);
	int StopCapture();

	int getExposure();
	int setExposure(int exposure);


	long m_triggerCnt;
	long m_recvPicCnt;



};


#endif // !defined(AFX_CCDCTRL_H__768B1DBD_17E4_4036_8FBA_2782794F7948__INCLUDED_)
