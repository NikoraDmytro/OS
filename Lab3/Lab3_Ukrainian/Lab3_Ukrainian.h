// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the LAB3UKRAINIAN_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// LAB3UKRAINIAN_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef LAB3UKRAINIAN_EXPORTS
#define LAB3UKRAINIAN_API __declspec(dllexport)
#else
#define LAB3UKRAINIAN_API __declspec(dllimport)
#endif

// This class is exported from the dll
class LAB3UKRAINIAN_API CLab3Ukrainian {
public:
	CLab3Ukrainian(void);
	// TODO: add your methods here.
};

extern LAB3UKRAINIAN_API int nLab3Ukrainian;

LAB3UKRAINIAN_API int fnLab3Ukrainian(void);
