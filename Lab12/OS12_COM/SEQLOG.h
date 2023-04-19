#pragma once
#include <fstream>

extern LONG Seq;
extern std::fstream LogCOM;

#define SEQ LONG __XXCSeq = InterlockedIncrement(&Seq)
#define LOG(x,y) LogCOM << __XXCSeq << ": " << x << y << "\n"