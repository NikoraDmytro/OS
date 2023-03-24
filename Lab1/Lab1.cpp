#include <iostream>
#include <tchar.h>
#include <Windows.h>

using namespace std;

int main() 
{
	cout << "sizeof(TCHAR) = " << sizeof(TCHAR) << endl;
	cout << "default encoding : " 
		 << (sizeof(TCHAR) == 2 ? "UNICODE" : "ASCII") 
		 << endl;

	setlocale(LC_ALL, "Ukrainian");
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	char family[][30] =
	{
		"ͳ���� ������ ��������",
		"ͳ���� ������ ������������",
		"ͳ���� ���� ����������",
		"ͳ���� ������ ��������"
	};

	cout << "Family (in ASCII): " << endl;
	for (const char* member : family)
	{
		cout << "\t" << member << endl;
	}

	const int size = sizeof(family[0]);
	const int count = sizeof(family) / size;
	wchar_t* wfamily[count];

	for (int i = 0; i < count; i++)
	{
		wfamily[i] = new wchar_t[size];

		MultiByteToWideChar(
			CP_ACP,				// ������ �������, �������� �������� CP_ACP
			0, 					// 0
			family[i], 			// �����, ���� ��������������
			size, 				// ����� (� ������)
			wfamily[i], 		// ����� - ���������
			size				// ����� � wchar_t ��������.
		);
	}

	cout << "Family (in UNICODE): " << endl;
	for (int i = 0; i < count; i++)
	{
		_tprintf(_T("\t%ls (_tprintf)\n"), wfamily[i]);
		wcout << "\t" << wfamily[i] << " (wcout)" << endl;
		MessageBox(0, _T(wfamily[i]), _T("Family"), MB_OK);
	}
}
