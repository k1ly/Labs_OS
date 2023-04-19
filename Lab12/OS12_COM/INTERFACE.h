#pragma once
#include <objbase.h>

#define FNAME L"OS12.COM"
#define VINDX L"OS12.1"
#define PRGID L"OS12"

// {B5485506-91A6-40AA-A4F2-C20A27B9F06A}
static const GUID CLSID_OS12 =
{ 0xb5485506, 0x91a6, 0x40aa, { 0xa4, 0xf2, 0xc2, 0xa, 0x27, 0xb9, 0xf0, 0x6a } };

// {7315BDF7-4E17-47D1-B599-693F7D47A0D6}
static const GUID IID_IAdder =
{ 0x7315bdf7, 0x4e17, 0x47d1, { 0xb5, 0x99, 0x69, 0x3f, 0x7d, 0x47, 0xa0, 0xd6 } };

// {16771D67-ABFA-4A70-A377-0EF6FB76459C}
static const GUID IID_IMultiplier =
{ 0x16771d67, 0xabfa, 0x4a70, { 0xa3, 0x77, 0xe, 0xf6, 0xfb, 0x76, 0x45, 0x9c } };


interface IAdder : IUnknown
{
	virtual	HRESULT STDMETHODCALLTYPE Add(const double x, const double y, double& z) = 0;
	virtual	HRESULT STDMETHODCALLTYPE Sub(const double x, const double y, double& z) = 0;
};

interface IMultiplier : IUnknown
{
	virtual	HRESULT STDMETHODCALLTYPE Mul(const double x, const double y, double& z) = 0;
	virtual	HRESULT STDMETHODCALLTYPE Div(const double x, const double y, double& z) = 0;
};
