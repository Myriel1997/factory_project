#if !defined(AFX_XLSEXPORT_H__15EBF020_61C9_4125_815B_106488F951E8__INCLUDED_)
#define AFX_XLSEXPORT_H__15EBF020_61C9_4125_815B_106488F951E8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CXLSExport wrapper class

class CXLSExport : public COleDispatchDriver
{
public:
	CXLSExport() {}		// Calls COleDispatchDriver default constructor
	CXLSExport(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CXLSExport(const CXLSExport& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	BOOL GetIncludeHeader();
	void SetIncludeHeader(BOOL bNewValue);
	BOOL GetIncludeLabels();
	void SetIncludeLabels(BOOL bNewValue);
	BOOL GetIncludeIndex();
	void SetIncludeIndex(BOOL bNewValue);
	VARIANT GetSeries();
	void SetSeries(const VARIANT& newValue);
	void SaveToFile(LPCTSTR FileName);
	VARIANT SaveToStream();
	CString AsString();
	BOOL GetIncludeColors();
	void SetIncludeColors(BOOL bNewValue);
	BOOL GetUseSeriesFormat();
	void SetUseSeriesFormat(BOOL bNewValue);
	CString GetValueFormat();
	void SetValueFormat(LPCTSTR lpszNewValue);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_XLSEXPORT_H__15EBF020_61C9_4125_815B_106488F951E8__INCLUDED_)
