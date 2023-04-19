#include "pch.h"
#include "OS12.h"
#include "SEQLOG.h"

extern ULONG g_Components;

OS12::OS12() : m_Ref(1)
{
	SEQ;
	InterlockedIncrement(&g_Components);
	LOG("OS12::OS12, g_Components = ", g_Components);
}

OS12::~OS12()
{
	SEQ;
	InterlockedDecrement(&g_Components);
	LOG("OS12::~OS12, g_Components = ", g_Components);
}

HRESULT STDMETHODCALLTYPE OS12::QueryInterface(REFIID riid, void** ppv)
{
	SEQ;
	HRESULT rc = S_OK;
	if (riid == IID_IUnknown)
		*ppv = (IUnknown*)this;
	else if (riid == IID_IAdder)
		*ppv = (IAdder*)this;
	else if (riid == IID_IMultiplier)
		*ppv = (IMultiplier*)this;
	else rc = E_NOINTERFACE;
	if (rc == S_OK)
		this->AddRef();
	LOG("OS12::QueryInterface, rc = ", rc);
	return rc;
}

ULONG STDMETHODCALLTYPE OS12::AddRef(void)
{
	SEQ;
	InterlockedIncrement(&this->m_Ref);
	LOG("OS12::AddRef, m_Ref = ", this->m_Ref);
	return this->m_Ref;
}

ULONG STDMETHODCALLTYPE OS12::Release(void)
{
	SEQ;
	ULONG m_Ref = this->m_Ref;
	if ((m_Ref = InterlockedDecrement(&this->m_Ref)) == 0)
		delete this;
	LOG("OS12::Release, m_Ref = ", m_Ref);
	return m_Ref;
}

HRESULT STDMETHODCALLTYPE OS12::Add(const double x, const double y, double& z)
{
	SEQ;
	HRESULT rc = S_OK;
	z = x + y;
	char result[50];
	sprintf_s(result, "%f + %f = %f", x, y, z);
	LOG("OS12::Add, ", result);
	return rc;
}

HRESULT STDMETHODCALLTYPE OS12::Sub(const double x, const double y, double& z)
{
	SEQ;
	HRESULT rc = S_OK;
	z = x - y;
	char result[50];
	sprintf_s(result, "%f - %f = %f", x, y, z);
	LOG("OS12::Sub, ", result);
	return rc;
}

HRESULT STDMETHODCALLTYPE OS12::Mul(const double x, const double y, double& z)
{
	SEQ;
	HRESULT rc = S_OK;
	z = x * y;
	char result[50];
	sprintf_s(result, "%f * %f = %f", x, y, z);
	LOG("OS12::Mul, ", result);
	return rc;
}

HRESULT STDMETHODCALLTYPE OS12::Div(const double x, const double y, double& z)
{
	SEQ;
	HRESULT rc = S_OK;
	z = x / y;
	char result[50];
	sprintf_s(result, "%f / %f = %f", x, y, z);
	LOG("OS12::Div, ", result);
	return rc;
}