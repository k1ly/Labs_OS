#pragma once
#include "INTERFACE.h"

class OS12 : IUnknown, IAdder, IMultiplier
{
public:
	virtual HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** ppv);
	virtual ULONG STDMETHODCALLTYPE AddRef(void);
	virtual ULONG STDMETHODCALLTYPE Release(void);

	virtual	HRESULT STDMETHODCALLTYPE Add(const double x, const double y, double& z);
	virtual	HRESULT STDMETHODCALLTYPE Sub(const double x, const double y, double& z);
	virtual	HRESULT STDMETHODCALLTYPE Mul(const double x, const double y, double& z);
	virtual	HRESULT STDMETHODCALLTYPE Div(const double x, const double y, double& z);
	OS12();
	~OS12();
private:
	volatile ULONG m_Ref;
};
