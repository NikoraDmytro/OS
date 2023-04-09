#include <iostream>
#include <tchar.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <Windows.h>

using namespace std;

int qcmp(const void* a, const void* b)
{
	return _wcsicmp(*(const wchar_t**)a, *(const wchar_t**)b);
}

bool cmp(const wchar_t* lhs, const wchar_t* rhs)
{
	return _wcsicmp(lhs, rhs) == 1 ? true : false;
}

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

		MessageBoxW(0, wfamily[i], L"Family", MB_OK);
	}

	qsort(wfamily, count, sizeof(wfamily[0]), qcmp);

	cout << "\nAfter qsort: " << endl;
	for (int i = 0; i < count; i++)
	{
		wcout << "\t" << wfamily[i] << endl;
	}

	sort(wfamily, wfamily + count, cmp);

	cout << "\nAfter sort: " << endl;
	for (int i = 0; i < count; i++)
	{
		wcout << "\t" << wfamily[i] << endl;
	}

	char* familyASCII[count];

	for (int i = 0; i < count; i++)
	{
		familyASCII[i] = new char[size];

		WideCharToMultiByte(
			CP_ACP,         // ������ �������, �������� �������� CP_ACP
			0,				// 0
			wfamily[i],     // �����, ���� ��������������
			size,			// ����� (� ������)
			familyASCII[i], // ����� - ���������
			size,			// ����� � char ��������.
			NULL,			// ������ �������, ���� ���������� 
			//������, �� ��������������, ���� �� �� ���� ���� �����������. ������� NULL, ���� ��������������� ������ ��  �������������.
			NULL			// �������� �� ���������, ���� ����� �� ��, �� ���������������� ������ �� ������������� � ������������  ��������.
		);
	}

	cout << "\nFamily (in ASCII): " << endl;
	for (int i = 0; i < count; i++)
	{
		printf("\t%s (printf)\n", familyASCII[i]);
		cout << "\t" << familyASCII[i] << " (cout)" << endl;

		MessageBoxA(0, familyASCII[i], "Family", MB_OK);
	}

	ifstream inputA("inputA.txt", ios::binary);
	ifstream inputU("inputU.txt", ios::binary);
	ofstream outputA("outputA.txt");
	ofstream outputU("outputU.txt");

	if (!inputA.is_open() || !inputU.is_open()) {
		std::cerr << "Unable to open files" << std::endl;
		return 1;
	}

	vector<wchar_t> buff;

	for (char ch; inputA.get(ch);)
	{
		buff.push_back(ch);
	}

	reverse(buff.begin(), buff.end());

	for (char ch : buff)
	{
		outputA.put(ch);
	}

	buff.clear();

	for (char ch; inputU.get(ch);)
	{
		buff.push_back(ch);
	}

	reverse(buff.begin(), buff.end());

	for (char ch : buff)
	{
		outputU.put(ch);
	}

	inputA.close();
	inputU.close();
	outputA.close();
	outputU.close();
}