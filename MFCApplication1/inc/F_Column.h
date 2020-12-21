// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类
#pragma once    //add by qq
#import "C:\\WINDOWS\\system32\\FlexCell.ocx" no_namespace



//////////////////////////////////////////////////////////////////////
// CF_Column 包装类

class CF_Column : public COleDispatchDriver
{
public:
	CF_Column(){} // 调用 COleDispatchDriver 默认构造函数
	CF_Column(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CF_Column(const CF_Column& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 属性
public:

	// 操作
public:


	// _Column 方法
public:
	long get_Alignment()
	{
		long result;
		InvokeHelper(0x6803000a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Alignment(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x6803000a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	short get_DecimalLength()
	{
		short result;
		InvokeHelper(0x68030009, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
		return result;
	}
	void put_DecimalLength(short newValue)
	{
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x68030009, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_Locked()
	{
		BOOL result;
		InvokeHelper(0x68030008, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_Locked(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x68030008, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_Mask()
	{
		long result;
		InvokeHelper(0x68030007, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Mask(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x68030007, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_SearchMethod()
	{
		long result;
		InvokeHelper(0x68030006, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_SearchMethod(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x68030006, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	short get_MaxLength()
	{
		short result;
		InvokeHelper(0x68030005, DISPATCH_PROPERTYGET, VT_I2, (void*)&result, NULL);
		return result;
	}
	void put_MaxLength(short newValue)
	{
		static BYTE parms[] = VTS_I2 ;
		InvokeHelper(0x68030005, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_CellType()
	{
		long result;
		InvokeHelper(0x68030004, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_CellType(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x68030004, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_Width()
	{
		long result;
		InvokeHelper(0x68030003, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Width(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x68030003, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_FormatString()
	{
		CString result;
		InvokeHelper(0x68030002, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_FormatString(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x68030002, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_UserSortIndicator()
	{
		long result;
		InvokeHelper(0x68030001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_UserSortIndicator(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x68030001, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void put_Position(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x68030000, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void Sort(long Order)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x6003000d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Order);
	}
	void AutoFit()
	{
		InvokeHelper(0x6003000e, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}

	// _Column 属性
public:

};
