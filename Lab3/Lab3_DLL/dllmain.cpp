// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "Lab3_DLL_inner.h"
#include <iostream>

using namespace std;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        cout 
            << "lpReserved = "
            << lpReserved
            << " using " 
            << (lpReserved ? "static" : "dynamic") 
            << "\n\n";

        char dllName[MAX_PATH];
        GetModuleFileNameA(hModule, dllName, MAX_PATH);

        if (!CheckControlBlock(dllName)) {
            return false;
        }

        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

