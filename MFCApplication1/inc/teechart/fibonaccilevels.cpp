// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


#include "stdafx.h"
#include "fibonaccilevels.h"

// Dispatch interfaces referenced by this interface
#include "FibonacciItem.h"


/////////////////////////////////////////////////////////////////////////////
// CFibonacciLevels properties

/////////////////////////////////////////////////////////////////////////////
// CFibonacciLevels operations

CFibonacciItem CFibonacciLevels::GetLevel(long Index)
{
	LPDISPATCH pDispatch;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0xc9, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&pDispatch, parms,
		Index);
	return CFibonacciItem(pDispatch);
}
