// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类
#pragma once   //add by qq
#import "C:\\WINDOWS\\system32\\FlexCell.ocx" no_namespace

// Dispatch interfaces referenced by this interface
///////////////////////////////////////////////////////////////////////////
#include "font.h"

/////////////////////////////////////////////////////////////////////////////
// CF_Cell 包装类

class CF_Cell : public COleDispatchDriver
{
public:
	CF_Cell(){} // 调用 COleDispatchDriver 默认构造函数
	CF_Cell(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CF_Cell(const CF_Cell& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}
	

	// 属性
public:
	
	//long m_CellIndex;     //add by qq

	// 操作
public:
////add by qq
//void SetCellErrorIndex(long index)
//{
//	m_CellIndex = index;
//}
//long GetCellErrorIndex()
//{
//	return m_CellIndex;
//}
////end add
	// _Cell 方法
public:
	long get_Row()
	{
		long result;
		InvokeHelper(0x68030018, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get_Col()
	{
		long result;
		InvokeHelper(0x68030017, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	CString get_Tag()
	{
		CString result;
		InvokeHelper(0x68030016, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_Tag(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x68030016, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_Text()
	{
		CString result;
		InvokeHelper(0x68030015, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_Text(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x68030015, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_ImageKey()
	{
		CString result;
		InvokeHelper(0x68030014, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	long get_Alignment()
	{
		long result;
		InvokeHelper(0x68030013, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Alignment(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x68030013, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	unsigned long get_BackColor()
	{
		unsigned long result;
		InvokeHelper(0x68030012, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, NULL);
		return result;
	}
	void put_BackColor(unsigned long newValue)
	{
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x68030012, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	unsigned long get_ForeColor()
	{
		unsigned long result;
		InvokeHelper(0x68030011, DISPATCH_PROPERTYGET, VT_UI4, (void*)&result, NULL);
		return result;
	}
	void put_ForeColor(unsigned long newValue)
	{
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x68030011, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_Locked()
	{
		BOOL result;
		InvokeHelper(0x68030010, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_Locked(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x68030010, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_Mask()
	{
		long result;
		InvokeHelper(0x6803000f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Mask(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x6803000f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_Border(long Edge)
	{
		long result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x6803000e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, parms, Edge);
		return result;
	}
	void put_Border(long Edge, long newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x6803000e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, Edge, newValue);
	}
	long get_CellType()
	{
		long result;
		InvokeHelper(0x6803000d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_CellType(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x6803000d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void SetFocus()
	{
		InvokeHelper(0x6003001a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void EnsureVisible()
	{
		InvokeHelper(0x6003001b, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	//edit by qq
	COleFont get_Font()
	{
		LPDISPATCH result;
		InvokeHelper(0x6803000c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return COleFont(result);
	}
	BOOL get_Printable()
	{
		BOOL result;
		InvokeHelper(0x6803000b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_Printable(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x6803000b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_WrapText()
	{
		BOOL result;
		InvokeHelper(0x6803000a, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_WrapText(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x6803000a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_MergeCell()
	{
		BOOL result;
		InvokeHelper(0x68030009, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void SetImage(LPCTSTR ImageKey)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x6003001d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ImageKey);
	}
	void Refresh()
	{
		InvokeHelper(0x6003001e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	BOOL get_BooleanValue()
	{
		BOOL result;
		InvokeHelper(0x68030008, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	short get_IntegerValue()
	{
		short result;
		InvokeHelper(0x68030007, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
		return result;
	}
	long get_LongValue()
	{
		long result;
		InvokeHelper(0x68030006, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	float get_SingleValue()
	{
		float result;
		InvokeHelper(0x68030005, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
		return result;
	}
	double get_DoubleValue()
	{
		double result;
		InvokeHelper(0x68030004, DISPATCH_PROPERTYGET, VT_R8, (void*)&result, NULL);
		return result;
	}
	long get_Left()
	{
		long result;
		InvokeHelper(0x68030003, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get_Top()
	{
		long result;
		InvokeHelper(0x68030002, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get_Width()
	{
		long result;
		InvokeHelper(0x68030001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get_Height()
	{
		long result;
		InvokeHelper(0x68030000, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}

	// _Cell 属性
public:

};
