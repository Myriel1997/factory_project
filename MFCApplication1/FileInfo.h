#pragma once
#include "targetver.h"
#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ
#include <afxdisp.h>        // MFC �Զ�����
#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��
//#include "SkinPPWTL.h"

class CFileInfo
{
public:
	CFileInfo(void);
	~CFileInfo(void);

public:
	char		m_CurrentPath[_MAX_PATH];	// ���Ӧ�ó���·��
	CString m_strModelPath;			//Model�ļ���·��
	CString m_strSharePath;			//user.ini·��
	//CString m_ModelImagePath;	//ͼ��·������
	CString m_ModelRegionPath;	//����·������
	CString m_strModelIniPath;		//���������ļ�·������
	CString m_ModelComPath;		//����ͨ�������ļ�·������
	CString m_strCamPath;	//������������ļ�

private:
	int m_nCamIndex;

public:
	bool GetCurrentAppPath(char **path);//binĿ¼·��
	CString GetShareIniPath();//user.ini·��
	//void ModelFilePath(int camIndex); //Model���ļ�·��
	CString GetModelPath(int pro_index,int camIndex);
	CString GetModelPathUP(int pro_index);
	CString GetCamPath(int camIndex);
};
