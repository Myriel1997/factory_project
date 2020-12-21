// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


// Dispatch interfaces referenced by this interface
class CTeePoint2D;
class CPen1;
class CPointer;
class CValueList;
class CCircleLabels;
class CBrush1;
class CGradient;

/////////////////////////////////////////////////////////////////////////////
// CPolarBarSeries wrapper class

class CPolarBarSeries : public COleDispatchDriver
{
public:
	CPolarBarSeries() {}		// Calls COleDispatchDriver default constructor
	CPolarBarSeries(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CPolarBarSeries(const CPolarBarSeries& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetXRadius();
	void SetXRadius(long nNewValue);
	long GetYRadius();
	void SetYRadius(long nNewValue);
	long GetXCenter();
	long GetYCenter();
	long GetCircleWidth();
	long GetCircleHeight();
	unsigned long GetCircleBackColor();
	void SetCircleBackColor(unsigned long newValue);
	BOOL GetCircled();
	void SetCircled(BOOL bNewValue);
	long GetRotationAngle();
	void SetRotationAngle(long nNewValue);
	CTeePoint2D AngleToPoint(double Angle, double AXRadius, double AYRadius);
	double PointToAngle(long XCoord, long YCoord);
	double PointToRadius(long XCoord, long YCoord);
	double GetAngleIncrement();
	void SetAngleIncrement(double newValue);
	BOOL GetCloseCircle();
	void SetCloseCircle(BOOL bNewValue);
	CPen1 GetPen();
	CPointer GetPointer();
	double GetRadiusIncrement();
	void SetRadiusIncrement(double newValue);
	CValueList GetAngleValues();
	CValueList GetRadiusValues();
	void DrawRing(double Value, long Z);
	CPen1 GetCirclePen();
	CCircleLabels GetCircleLabels();
	CBrush1 GetBrush();
	void LoadBackImage(LPCTSTR FileName);
	void ClearBackImage();
	BOOL GetClockWiseLabels();
	void SetClockWiseLabels(BOOL bNewValue);
	BOOL GetCircleLabelsInside();
	void SetCircleLabelsInside(BOOL bNewValue);
	long GetTransparency();
	void SetTransparency(long nNewValue);
	CGradient GetCircleGradient();
	void DrawZone(double Min, double Max, long Z);
	long GetLabelsMargin();
	void SetLabelsMargin(long nNewValue);
	long GetTreatNulls();
	void SetTreatNulls(long nNewValue);
};
