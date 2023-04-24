#pragma once

#ifdef LAB3DLL_EXPORTS
#define LAB3API	extern "C"  _declspec (dllexport)
#else
#define LAB3API	extern "C"  _declspec (dllimport)
#endif

LAB3API bool Crypt(unsigned long long, unsigned long long, unsigned long long, unsigned long long*);
LAB3API bool DeCrypt(unsigned long long, unsigned long long, unsigned long long, unsigned long long*);
LAB3API unsigned long long GenKey(unsigned long long*, unsigned long long*);