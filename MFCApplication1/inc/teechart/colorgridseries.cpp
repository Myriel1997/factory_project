// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


#include "stdafx.h"
#include "colorgridseries.h"

// Dispatch interfaces referenced by this interface
#include "valuelist.h"
#include "brush.h"
#include "pen.h"
#include "charthiddenpen.h"


/////////////////////////////////////////////////////////////////////////////
// CColorGridSeries properties

/////////////////////////////////////////////////////////////////////////////
// CColorGridSeries operations

long CColorGridSeries::AddXYZ(double AX, double AY, double AZ, LPCTSTR AXLabel, unsigned long Value)
{
	long result;
	static BYTE parms[] =
		VTS_R8 VTS_R8 VTS_R8 VTS_BSTR VTS_I4;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		AX, AY, AZ, AXLabel, Value);
	return result;
}

double CColorGridSeries::MaxZValue()
{
	double result;
	InvokeHelper(0x1, DISPATCH_METHOD, VT_R8, (void*)&result, NULL);
	return result;
}

double CColorGridSeries::MinZValue()
{
	double result;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_R8, (void*)&result, NULL);
	return result;
}

long CColorGridSeries::GetTimesZOrder()
{
	long result;
	InvokeHelper(0x9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CColorGridSeries::SetTimesZOrder(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CValueList CColorGridSeries::GetZValues()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0xd, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CValueList(pDispatch);
}

double CColorGridSeries::GetZValue(long Index)
{
	double result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x5, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, parms,
		Index);
	return result;
}

void CColorGridSeries::SetZValue(long Index, double newValue)
{
	static BYTE parms[] =
		VTS_I4 VTS_R8;
	InvokeHelper(0x5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 Index, newValue);
}

CBrush1 CColorGridSeries::GetBrush()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0x83, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CBrush1(pDispatch);
}

CPen1 CColorGridSeries::GetPen()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0x86, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CPen1(pDispatch);
}

void CColorGridSeries::AddArrayXYZ(const VARIANT& XArray, const VARIANT& YArray, const VARIANT& ZArray)
{
	static BYTE parms[] =
		VTS_VARIANT VTS_VARIANT VTS_VARIANT;
	InvokeHelper(0x87, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &XArray, &YArray, &ZArray);
}

void CColorGridSeries::AddArrayGrid(long NumX, long NumZ, const VARIANT& XZArray)
{
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_VARIANT;
	InvokeHelper(0xc9, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 NumX, NumZ, &XZArray);
}

long CColorGridSeries::CalcZPos(long ValueIndex)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xca, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		ValueIndex);
	return result;
}

long CColorGridSeries::AddPalette(double Value, unsigned long Color)
{
	long result;
	static BYTE parms[] =
		VTS_R8 VTS_I4;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		Value, Color);
	return result;
}

unsigned long CColorGridSeries::GetStartColor()
{
	unsigned long result;
	InvokeHelper(0xa, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CColorGridSeries::SetStartColor(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

unsigned long CColorGridSeries::GetEndColor()
{
	unsigned long result;
	InvokeHelper(0x4, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CColorGridSeries::SetEndColor(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x4, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

long CColorGridSeries::GetPaletteSteps()
{
	long result;
	InvokeHelper(0x8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CColorGridSeries::SetPaletteSteps(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL CColorGridSeries::GetUsePalette()
{
	BOOL result;
	InvokeHelper(0xc, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CColorGridSeries::SetUsePalette(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

BOOL CColorGridSeries::GetUseColorRange()
{
	BOOL result;
	InvokeHelper(0xb, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CColorGridSeries::SetUseColorRange(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xb, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void CColorGridSeries::ClearPalette()
{
	InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CColorGridSeries::CreateDefaultPalette(long NumSteps)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 NumSteps);
}

unsigned long CColorGridSeries::GetSurfacePaletteColor(double Y)
{
	unsigned long result;
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		Y);
	return result;
}

unsigned long CColorGridSeries::GetMidColor()
{
	unsigned long result;
	InvokeHelper(0x21, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CColorGridSeries::SetMidColor(unsigned long newValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x21, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

void CColorGridSeries::CreateRangePalette()
{
	InvokeHelper(0x22, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long CColorGridSeries::GetPaletteStyle()
{
	long result;
	InvokeHelper(0x23, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CColorGridSeries::SetPaletteStyle(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x23, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL CColorGridSeries::GetUsePaletteMin()
{
	BOOL result;
	InvokeHelper(0x12d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CColorGridSeries::SetUsePaletteMin(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x12d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

double CColorGridSeries::GetPaletteMin()
{
	double result;
	InvokeHelper(0x12e, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void CColorGridSeries::SetPaletteMin(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x12e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

double CColorGridSeries::GetPaletteStep()
{
	double result;
	InvokeHelper(0x12f, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
	return result;
}

void CColorGridSeries::SetPaletteStep(double newValue)
{
	static BYTE parms[] =
		VTS_R8;
	InvokeHelper(0x12f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 newValue);
}

void CColorGridSeries::InvertPalette()
{
	InvokeHelper(0x130, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CColorGridSeries::AddCustomPalette(const VARIANT& colorArray)
{
	static BYTE parms[] =
		VTS_VARIANT;
	InvokeHelper(0x131, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 &colorArray);
}

long CColorGridSeries::GetNumXValues()
{
	long result;
	InvokeHelper(0x6, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CColorGridSeries::SetNumXValues(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CColorGridSeries::GetNumZValues()
{
	long result;
	InvokeHelper(0x7, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CColorGridSeries::SetNumZValues(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

double CColorGridSeries::GetXZValue(long X, long Z)
{
	double result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_R8, (void*)&result, parms,
		X, Z);
	return result;
}

BOOL CColorGridSeries::GetIrregularGrid()
{
	BOOL result;
	InvokeHelper(0x139, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CColorGridSeries::SetIrregularGrid(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x139, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void CColorGridSeries::SmoothGrid3D()
{
	InvokeHelper(0x191, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL CColorGridSeries::GetReuseGridIndex()
{
	BOOL result;
	InvokeHelper(0x192, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CColorGridSeries::SetReuseGridIndex(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x192, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void CColorGridSeries::FillGridIndex(long StartIndex)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x193, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 StartIndex);
}

double CColorGridSeries::MaxXValue()
{
	double result;
	InvokeHelper(0xe9, DISPATCH_METHOD, VT_R8, (void*)&result, NULL);
	return result;
}

double CColorGridSeries::MaxYValue()
{
	double result;
	InvokeHelper(0x14, DISPATCH_METHOD, VT_R8, (void*)&result, NULL);
	return result;
}

double CColorGridSeries::MinYValue()
{
	double result;
	InvokeHelper(0x15, DISPATCH_METHOD, VT_R8, (void*)&result, NULL);
	return result;
}

BOOL CColorGridSeries::GetCenteredPoints()
{
	BOOL result;
	InvokeHelper(0x1f5, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CColorGridSeries::SetCenteredPoints(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1f5, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

void CColorGridSeries::SetBitmap(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1f7, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

BOOL CColorGridSeries::GetSmoothBitmap()
{
	BOOL result;
	InvokeHelper(0x1f6, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
	return result;
}

void CColorGridSeries::SetSmoothBitmap(BOOL bNewValue)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1f6, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 bNewValue);
}

long CColorGridSeries::GetTransparency()
{
	long result;
	InvokeHelper(0x1f8, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CColorGridSeries::SetTransparency(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1f8, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CColorGridSeries::GetDrawPlane3D()
{
	long result;
	InvokeHelper(0x1f9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CColorGridSeries::SetDrawPlane3D(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1f9, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CColorGridSeries::GetDrawPosition()
{
	long result;
	InvokeHelper(0x1fa, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CColorGridSeries::SetDrawPosition(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1fa, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

CChartHiddenPen CColorGridSeries::GetFrame()
{
	LPDISPATCH pDispatch;
	InvokeHelper(0x1fb, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, NULL);
	return CChartHiddenPen(pDispatch);
}

long CColorGridSeries::GetXGridEvery()
{
	long result;
	InvokeHelper(0x1fc, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CColorGridSeries::SetXGridEvery(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1fc, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}

long CColorGridSeries::GetZGridEvery()
{
	long result;
	InvokeHelper(0x1fd, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
	return result;
}

void CColorGridSeries::SetZGridEvery(long nNewValue)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1fd, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms,
		 nNewValue);
}
