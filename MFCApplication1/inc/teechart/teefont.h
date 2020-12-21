// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


// Dispatch interfaces referenced by this interface
class CTeeShadow;
class CPen1;
class CGradient;
class CTeePicture;

/////////////////////////////////////////////////////////////////////////////
// CTeeFont wrapper class

class CTeeFont : public COleDispatchDriver
{
public:
	CTeeFont() {}		// Calls COleDispatchDriver default constructor
	CTeeFont(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CTeeFont(const CTeeFont& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	long GetSize();
	void SetSize(long nNewValue);
	BOOL GetBold();
	void SetBold(BOOL bNewValue);
	BOOL GetItalic();
	void SetItalic(BOOL bNewValue);
	BOOL GetUnderline();
	void SetUnderline(BOOL bNewValue);
	BOOL GetStrikethrough();
	void SetStrikethrough(BOOL bNewValue);
	short GetCharset();
	void SetCharset(short nNewValue);
	unsigned long GetColor();
	void SetColor(unsigned long newValue);
	long GetHeight();
	void SetHeight(long nNewValue);
	long GetPixelsPerInch();
	long GetInterCharSize();
	void SetInterCharSize(long nNewValue);
	CTeeShadow GetShadow();
	CPen1 GetOutline();
	CGradient GetGradient();
	void ShowEditor();
	CTeePicture GetPicture();
};
