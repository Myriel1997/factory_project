// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类
#pragma once    //add by qq
#import "C:\\WINDOWS\\system32\\FlexCell.ocx" no_namespace

////////////////////////////////////////////////////////////////////////
// CF_Selection 包装类

class CF_Selection : public COleDispatchDriver
{
public:
	CF_Selection(){} // 调用 COleDispatchDriver 默认构造函数
	CF_Selection(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CF_Selection(const CF_Selection& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 属性
public:

	// 操作
public:


	// _Selection 方法
public:
	void put_BackColor(unsigned long newValue)
	{
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x68030013, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void put_CellType(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x68030012, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void put_ForeColor(unsigned long newValue)
	{
		static BYTE parms[] = VTS_UI4 ;
		InvokeHelper(0x68030011, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void put_Alignment(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x68030010, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void put_Locked(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x6803000f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void put_Mask(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x6803000e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void put_Printable(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x6803000d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void put_WrapText(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x6803000c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void put_Borders(long Edge, long newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x6803000b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, Edge, newValue);
	}
	void put_MergeCells(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x6803000a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void put_FontName(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x68030009, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void put_FontSize(float newValue)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x68030008, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void put_FontBold(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x68030007, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void put_FontItalic(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x68030006, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void put_FontUnderline(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x68030005, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void put_FontStrikethrough(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x68030004, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_FirstRow()
	{
		long result;
		InvokeHelper(0x68030003, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get_LastRow()
	{
		long result;
		InvokeHelper(0x68030002, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get_FirstCol()
	{
		long result;
		InvokeHelper(0x68030001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get_LastCol()
	{
		long result;
		InvokeHelper(0x68030000, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void ClearAll()
	{
		InvokeHelper(0x60030015, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void ClearText()
	{
		InvokeHelper(0x60030016, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void ClearFormat()
	{
		InvokeHelper(0x60030017, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void DeleteByRow()
	{
		InvokeHelper(0x60030018, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void DeleteByCol()
	{
		InvokeHelper(0x60030019, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Merge()
	{
		InvokeHelper(0x6003001a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	VARIANT CopyData()
	{
		VARIANT result;
		InvokeHelper(0x6003001b, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	VARIANT CutData()
	{
		VARIANT result;
		InvokeHelper(0x6003001c, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	VARIANT PasteData()
	{
		VARIANT result;
		InvokeHelper(0x6003001d, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	void InsertRows()
	{
		InvokeHelper(0x6003001e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void InsertCols()
	{
		InvokeHelper(0x6003001f, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}

	// _Selection 属性
public:

};
