// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CSARFunction wrapper class

class CSARFunction : public COleDispatchDriver
{
public:
	CSARFunction() {}		// Calls COleDispatchDriver default constructor
	CSARFunction(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CSARFunction(const CSARFunction& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	double GetAccelerationFactor();
	void SetAccelerationFactor(double newValue);
	double GetMaxStep();
	void SetMaxStep(double newValue);
};
