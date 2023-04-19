#pragma once
#define OS12HANDLE void*

namespace OS12
{
	OS12HANDLE Init();                                // инициализация OS12
	//   if CoCreateInstance(... IID_Unknown)!= succesfull --> throw (int)HRESULT  

	namespace Adder
	{
		double Add(OS12HANDLE h, double x, double y);        // return x+y
		//  if QueryInteface(IID_IAdder) != succesfull -->  throw (int)HRESULT     
		double Sub(OS12HANDLE h, double x, double y);        // return x-y
		//  if QueryInteface(IID_IAdder) != succesfull -->  throw (int)HRESULT
	}

	namespace Multiplier
	{
		double Mul(OS12HANDLE h, double x, double y);        // return x*y
		//  if QueryInteface(IID_IMultiplier) != succesfull -->  throw (int)HRESULT 
		double Div(OS12HANDLE h, double x, double y);        // return x/y
		//  if QueryInteface(IID_IMultiplier) != succesfull -->  throw (int)HRESULT 
	}

	void Dispose(OS12HANDLE h);                       // завершение работы с OS12                  
}
