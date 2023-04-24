// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the LAB3ENGLISH_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// LAB3ENGLISH_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef LAB3ENGLISH_EXPORTS
#define LAB3ENGLISH_API __declspec(dllexport)
#else
#define LAB3ENGLISH_API __declspec(dllimport)
#endif

// This class is exported from the dll
class LAB3ENGLISH_API CLab3English {
public:
	CLab3English(void);
	// TODO: add your methods here.
};

extern LAB3ENGLISH_API int nLab3English;

LAB3ENGLISH_API int fnLab3English(void);
