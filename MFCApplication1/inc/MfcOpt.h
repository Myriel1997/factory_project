
#include <string>

#include "GrabberExport.h"
using namespace std;
/// ȱʡ�Ĳ��������ļ�����
#define PROFILE_INI "config\\user.ini"	
/////////////////////////////////////////////////////////////////////////////
// CProfiler view

typedef struct _tagImageProfile
{
	int nCamNum;				///<�������. 
	int nCountCardMode;			///<������ģʽ.add by qq
	int nImageWidth;			///<ͼ����. 
	int nImageHeight;			///<ͼ��߶�. 
	int nMinErrorImageWidth;	///<ȱ��ͼ����С���. 
	int nMinErrorImageHeight;	///<ȱ��ͼ����С�߶�. 
	float fHorizonResolution;	///<ˮƽ�ռ�ֱ���.��ʵ��Ϊ�������ֱ��ʣ� 
	float fVerticalResolution;	///<��ֱ�ռ�ֱ���. 
	int nMaxErrNumPerImage;		///<ÿͼ���ȱ����������. 
	int nOverlapBetweenImage;	///<��������ص�������. 
}ImageProfile;					///< ͼ�����ò���. 

struct ErrRect
{

	long    left;
	long    top;
	long    right;
	long    bottom;
};

struct ErrorRegionProfile
{
	int  nRegionType; //�����������
	int  Errortype;  // ��������
	ErrRect rect;		 // ������������������
	int x;          //ȱ��ˮƽ��������
	int y;          //ȱ�ݴ�ֱ��������
	int  nLevel;	 // ����̶�
	float  ErrorArea;  // �������
	float Diameter;

};

class _declspec(dllexport) CMfcOpt
{
public:
	CMfcOpt();           ///< ���캯����ͬʱ����ȱʡ�����ļ���. 
	virtual ~CMfcOpt();

	// Attributes
public:

	// Operations
public:
	/// ���������ļ����ļ���. 
	void SetFilename(string filename);

	/// ��ȡĳ�������ַ���. 
	string GetProfileString(string appName,string keyName);

	/// ��ȡĳ�����Ͳ���. 
	int GetProfileInt(string appName,string keyName, int defaultVal);

	ImageProfile GetImageProfile();

	///��ȡ�ɼ������ͺͳ�ʼ������. 
	void GetGrabInitParam(int nGrabberIndex, Grabber& grabberType, s_GBINITSTRUCT& initStruct);

protected:

	string m_iniFilename;



};