
#include <string>

#include "GrabberExport.h"
using namespace std;
/// 缺省的参数配置文件名。
#define PROFILE_INI "config\\user.ini"	
/////////////////////////////////////////////////////////////////////////////
// CProfiler view

typedef struct _tagImageProfile
{
	int nCamNum;				///<相机数量. 
	int nCountCardMode;			///<计数卡模式.add by qq
	int nImageWidth;			///<图像宽度. 
	int nImageHeight;			///<图像高度. 
	int nMinErrorImageWidth;	///<缺陷图像最小宽度. 
	int nMinErrorImageHeight;	///<缺陷图像最小高度. 
	float fHorizonResolution;	///<水平空间分辨率.（实际为编码器分辨率） 
	float fVerticalResolution;	///<垂直空间分辨率. 
	int nMaxErrNumPerImage;		///<每图最大缺陷数量上限. 
	int nOverlapBetweenImage;	///<两相机的重叠像素数. 
}ImageProfile;					///< 图像配置参数. 

struct ErrRect
{

	long    left;
	long    top;
	long    right;
	long    bottom;
};

struct ErrorRegionProfile
{
	int  nRegionType; //检测区域类型
	int  Errortype;  // 错误类型
	ErrRect rect;		 // 错误区域外界矩形坐标
	int x;          //缺陷水平方向坐标
	int y;          //缺陷垂直方向坐标
	int  nLevel;	 // 错误程度
	float  ErrorArea;  // 错误面积
	float Diameter;

};

class _declspec(dllexport) CMfcOpt
{
public:
	CMfcOpt();           ///< 构造函数，同时设置缺省配置文件名. 
	virtual ~CMfcOpt();

	// Attributes
public:

	// Operations
public:
	/// 设置配置文件的文件名. 
	void SetFilename(string filename);

	/// 读取某个参数字符串. 
	string GetProfileString(string appName,string keyName);

	/// 读取某个整型参数. 
	int GetProfileInt(string appName,string keyName, int defaultVal);

	ImageProfile GetImageProfile();

	///获取采集卡类型和初始化参数. 
	void GetGrabInitParam(int nGrabberIndex, Grabber& grabberType, s_GBINITSTRUCT& initStruct);

protected:

	string m_iniFilename;



};