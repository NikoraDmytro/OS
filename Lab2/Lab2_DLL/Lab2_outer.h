#pragma once

#ifdef LAB2DLL_EXPORTS
#define LAB2API	extern "C"  _declspec (dllexport)
#else
#define LAB2API	extern "C"  _declspec (dllimport)
#endif

LAB2API bool Crypt(unsigned long long, unsigned long long, unsigned long long, unsigned long long*);
LAB2API bool DeCrypt(unsigned long long, unsigned long long, unsigned long long, unsigned long long*);
LAB2API unsigned long long GenKey(unsigned long long*, unsigned long long*);