// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


#include "stdafx.h"
#include "polarbarseries.h"

// Dispatch interfaces referenced by this interface
#include "teepoint2d.h"
#include "pen.h"
#include "pointer.h"
#include "valuelist.h"
#include "circlelabels.h"
#include "brush.h"
#include "gradient.h"


/////////////////////////////////////////////////////////////////////////////
// CPolarBarSeries properties

/////////////////////////////////////////////////////////////////////////////
// CPolarBarSeries operations

long CPolarBarSeries::GetXRadius()
{
	long result;
	InvokeHelper(0x1, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CPolarBarSeries::SetXRadius(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CPolarBarSeries::GetYRadius()
{
	long result;
	InvokeHelper(0x2, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CPolarBarSeries::SetYRadius(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x2, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CPolarBarSeries::GetXCenter()
{
	long result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CPolarBarSeries::GetYCenter()
{
	long result;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CPolarBarSeries::GetCircleWidth()
{
	long result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

long CPolarBarSeries::GetCircleHeight()
{
	long result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

unsigned long CPolarBarSeries::GetCircleBackColor()
{
	unsigned long result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CPolarBarSeries::SetCircleBackColor(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL CPolarBarSeries::GetCircled()
{
	BOOL result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CPolarBarSeries::SetCircled(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long CPolarBarSeries::GetRotationAngle()
{
	long result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CPolarBarSeries::SetRotationAngle(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CTeePoint2D CPolarBarSeries::AngleToPoint(double Angle, double AXRadius, double AYRadius)
{
	LPDISPATCH pDispatch;
	static BYTE parms[] =
		VTS_R8 VTS_R8 VTS_R8;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_DISPATCH, (void*)&pDispatch, parms,
		Angle, AXRadius, AYRadius);
	return CTeePoint2D(pDispatch);
}

double CPolarBarSeries::PointToAngle(long XCoord, long YCoord)
{
	double result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0xc, DISPATCH_METHOD, VT_R8, (void*)&result, parms,
		XCoord, YCoord);
	return result;
}

double CPolarBarSeries::PointToRadius(long XCoord, long YCoord)
{
	double result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x191, DISPATCH_METHOD, VT_R8, (void*)&result, parms,
		XCoord, YCoord);
	return result;
}

double CPolarBarSeries::GetAngleIncrement()
{
	double result;
	InvokeHelper(0x1e, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void CPolarBarSeries::SetAngleIncrement(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x1e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

BOOL CPolarBarSeries::GetCloseCircle()
{
	BOOL result;
	InvokeHelper(0x1f, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CPolarBarSeries::SetCloseCircle(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

CPen1 CPolarBarSeries::GetPen()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0x20, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CPen1(pDispatch);
}

CPointer CPolarBarSeries::GetPointer()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0x21, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CPointer(pDispatch);
}

double CPolarBarSeries::GetRadiusIncrement()
{
	double result;
	InvokeHelper(0x22, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void CPolarBarSeries::SetRadiusIncrement(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x22, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

CValueList CPolarBarSeries::GetAngleValues()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0x23, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CValueList(pDispatch);
}

CValueList CPolarBarSeries::GetRadiusValues()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0x24, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CValueList(pDispatch);
}

void CPolarBarSeries::DrawRing(double Value, long Z)
{
	static BYTE parms[] =
		VTS_R8 VTS_I4;
	InvokeHelper(0x26, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Value, Z);
}

CPen1 CPolarBarSeries::GetCirclePen()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0x27, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CPen1(pDispatch);
}

CCircleLabels CPolarBarSeries::GetCircleLabels()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0x28, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CCircleLabels(pDispatch);
}

CBrush1 CPolarBarSeries::GetBrush()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0x3, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CBrush1(pDispatch);
}

void CPolarBarSeries::LoadBackImage(LPCTSTR FileName)
{
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 FileName);
}

void CPolarBarSeries::ClearBackImage()
{
	InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL CPolarBarSeries::GetClockWiseLabels()
{
	BOOL result;
	InvokeHelper(0x9b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CPolarBarSeries::SetClockWiseLabels(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x9b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CPolarBarSeries::GetCircleLabelsInside()
{
	BOOL result;
	InvokeHelper(0x9c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CPolarBarSeries::SetCircleLabelsInside(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x9c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long CPolarBarSeries::GetTransparency()
{
	long result;
	InvokeHelper(0x73, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CPolarBarSeries::SetTransparency(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x73, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CGradient CPolarBarSeries::GetCircleGradient()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0x12d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CGradient(pDispatch);
}

void CPolarBarSeries::DrawZone(double Min, double Max, long Z)
{
	static BYTE parms[] =
		VTS_R8 VTS_R8 VTS_I4;
	InvokeHelper(0x12e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Min, Max, Z);
}

long CPolarBarSeries::GetLabelsMargin()
{
	long result;
	InvokeHelper(0x12f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CPolarBarSeries::SetLabelsMargin(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x12f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CPolarBarSeries::GetTreatNulls()
{
	long result;
	InvokeHelper(0x130, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CPolarBarSeries::SetTreatNulls(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x130, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}
