#include <iostream>
#include <windows.h>
#include <tchar.h>

using namespace std;

#ifdef UNICODE
#define _tcout wcout
#elif
#define _tcout cout
#endif

typedef bool (*CRYPT)(
	unsigned long long OpenMsg, 
	unsigned long long E, 
	unsigned long long n, 
	unsigned long long* CryptMsg);
typedef bool (*DECRYPT)(
	unsigned long long CryptMsg, 
	unsigned long long D, 
	unsigned long long n,
	unsigned long long* OpenMsg);
typedef unsigned long long (*GENKEY)(
	unsigned long long* E, 
	unsigned long long* D);

void testRSA(GENKEY GenKey, CRYPT Crypt, DECRYPT DeCrypt) {
	unsigned long long E0, D0, E1, D1;
	unsigned long long n0 = GenKey(&E0, &D0);
	unsigned long long n1 = GenKey(&E1, &D1);

	srand(time(NULL));

	cout << "n0 = " << n0 << ", n1 = " << n1 << endl;
	cout << "E0 = " << E0 << ", D0 = " << D0 << endl;
	cout << "E1 = " << E1 << ", D1 = " << D1 << endl;

	unsigned long long t, e1t, d1e1t, e0d1e1t, d0e0d1e1t;

	for (int i = 0; i < 10; i++) {
		t = rand() % min(n0, n1);

		Crypt(t, E1, n1, &e1t);
		DeCrypt(e1t, D1, n1, &d1e1t);

		cout << "t[" << i << "] = " << t << ", decrypted with {d1, n1} = " << d1e1t << ((t == d1e1t) ? " OK" : " ERROR") << endl;

		Crypt(d1e1t, E0, n0, &e0d1e1t);
		DeCrypt(e0d1e1t, D0, n0, &d0e0d1e1t);

		cout << "t[" << i << "] = " << t << ", decrypted with {d0, n0} = " << d0e0d1e1t << ((t == d1e1t) ? " OK" : " ERROR") << endl;
	}
}

int main(int argc, char* argv[]) {
	TCHAR Surname[30];
	TCHAR Faculty[30];
	TCHAR Group[30];
	TCHAR Subject[30];

	HMODULE hLocal;

	if (argc < 2) {
		cout << "Command line arguments not provided!" << endl;
		return -1;
	}
	if (argv[1][0] == '0') {
		hLocal = LoadLibrary(_T("LAB3ENGLISH.dll"));
	}
	else if (argv[1][0] == '1') {
		hLocal = LoadLibrary(_T("LAB3UKRAINIAN.dll"));
		setlocale(LC_ALL, "Ukrainian");
		SetConsoleOutputCP(1251);
		SetConsoleCP(1251);
	}
	else {
		cout << "Unknown language option: " << argv[1][0] << endl;
		return -1;
	}
	if (!hLocal) {
		cout << "Failed to load the localization library!" << endl;
		return -1;
	}

	LoadString(hLocal, 101, Surname, 30);
	LoadString(hLocal, 102, Faculty, 30);
	LoadString(hLocal, 103, Group, 30);
	LoadString(hLocal, 104, Subject, 30);

	_tcout << "Surname: " << Surname << endl;
	_tcout << "Faculty: " << Faculty << endl;
	_tcout << "Group: " << Group << endl;
	_tcout << "Subject: " << Subject << endl;

	FreeLibrary(hLocal);
	
	cout << "\n\nRSA library:\n\n";

	HMODULE hRSA = LoadLibrary(_T("LAB3DLL.dll"));
	
	if (!hRSA) {
		cout << "Failed to load the RSA library!" << endl;
		return -1;
	}

	CRYPT Crypt = (CRYPT)GetProcAddress(hRSA, "Crypt");
	GENKEY GenKey = (GENKEY)GetProcAddress(hRSA, "GenKey");
	DECRYPT DeCrypt = (DECRYPT)GetProcAddress(hRSA, "DeCrypt");

	if (!GenKey || !Crypt || !DeCrypt) {
		cout << "Failed to get process addresses!" << endl;
		return -1;
	}

	testRSA(GenKey, Crypt, DeCrypt);
	FreeLibrary(hRSA);

	return 0;
}
