#if !defined(AFX_CHARTGRIDNAVIGATOR_H__0F2B9A54_AC18_4A14_9E67_FA80BEFFB87C__INCLUDED_)
#define AFX_CHARTGRIDNAVIGATOR_H__0F2B9A54_AC18_4A14_9E67_FA80BEFFB87C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CChartGridNavigator wrapper class

class CChartGridNavigator : public CWnd
{
protected:
	DECLARE_DYNCREATE(CChartGridNavigator)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0xcca57a27, 0x7b4e, 0x49d0, { 0xba, 0x80, 0xcf, 0x8, 0x14, 0xbc, 0x9c, 0xb3 } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName,
		LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect,
		CWnd* pParentWnd, UINT nID,
		CCreateContext* pContext = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); }

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect, CWnd* pParentWnd, UINT nID,
		CFile* pPersist = NULL, BOOL bStorage = FALSE,
		BSTR bstrLicKey = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); }

// Attributes
public:

// Operations
public:
	void SetGrid(LPDISPATCH newValue);
	void SetGridLink(long nNewValue);
	void EnableButtons();
	unsigned long GetColor();
	void SetColor(unsigned long newValue);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHARTGRIDNAVIGATOR_H__0F2B9A54_AC18_4A14_9E67_FA80BEFFB87C__INCLUDED_)
