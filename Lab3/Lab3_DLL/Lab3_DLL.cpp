#include "pch.h"
#include "Lab3_DLL_inner.h"
#include "Lab3_DLL_outer.h"
#include <stdlib.h>
#include <time.h>

const int BLOCK_SIZE = 8;

void CalculateChecksum(char* res, const char* data, uint32_t length) {
	uint32_t crc = 0xFFFFFFFF;
	uint32_t polynomial = 0xEDB88320;

	for (uint32_t i = 0; i < length; ++i) {
		crc ^= data[i];
		for (int j = 0; j < 8; ++j) {
			crc = (crc >> 1) ^ ((crc & 1) * polynomial);
		}
	}
	crc ^= 0xFFFFFFFF;

	snprintf(res, BLOCK_SIZE, "%08X", crc);
}

bool CheckControlBlock(char* fileName) {
	std::ifstream infile(fileName, std::ios::binary);

	if (!infile.is_open()) {
		std::cerr << "Error: Could not open DLL file.\n";
		return false;
	}

	infile.seekg(-BLOCK_SIZE, std::ios::end);
	uint32_t fileSize = infile.tellg();
	infile.seekg(0, std::ios::beg);

	char* fileData = new char[fileSize];
	infile.read(fileData, fileSize);

	char calculatedChecksum[BLOCK_SIZE];
	char expectedChecksum[BLOCK_SIZE];

	CalculateChecksum(calculatedChecksum, fileData, fileSize);
	infile.seekg(-BLOCK_SIZE, std::ios::end);
	infile.read(expectedChecksum, BLOCK_SIZE);
	infile.close();

	if (strcmp(expectedChecksum, calculatedChecksum) != 0) {
		std::cerr << "Error: Checksum mismatch.\n";
		std::cerr << "Expected: " << expectedChecksum << std::endl;
		std::cerr << "Calculated: " << calculatedChecksum << std::endl;
		return false;
	}

	return true;
};

extern "C" unsigned long long Simple() {
	srand(time(NULL));
	unsigned long long x = rand() % 1000000 + 3;
	x |= 1;

	while (1) {
		unsigned long long i = 3;

		for (; i * 1ll * i <= x; i += 2) {
			if (x % i == 0)  break;
		}

		if (x % i != 0) return x;
		x += 2;
	}
}

extern "C" unsigned long long Gdc(unsigned long long x, unsigned long long y) {
	while (x && y) {
		if (x > y)
		{
			x %= y;
		}
		else
		{
			y %= x;
		}
	}

	return x + y;
}

extern "C" unsigned long long PowMod(unsigned long long x, unsigned long long y, unsigned long long m) {
	unsigned long long r = 1;

	while (y)
	{
		if (y & 1)
		{
			r = (r * x) % m;
		}
		x = (x * x) % m;
		y >>= 1;
	}

	return r;
}

LAB3API unsigned long long GenKey(unsigned long long* E, unsigned long long* D) {
	int p, q;

	do
	{
		p = Simple();
		q = Simple();
	} while (p == q);

	unsigned n = p * q;
	unsigned fi = (p - 1) * (q - 1);
	for (*E = 3; Gdc(*E, fi) != 1; *E += 2);
	for (*D = 3; (*E) * (*D) % fi != 1; *D += 1);

	return n;
}


LAB3API bool Crypt(unsigned long long OpenMsg, unsigned long long E, unsigned long long n, unsigned long long* CryptMsg) {
	if (OpenMsg > n) return false;
	*CryptMsg = PowMod(OpenMsg, E, n);
	return true;
}

LAB3API bool DeCrypt(unsigned long long CryptMsg, unsigned long long D, unsigned long long n, unsigned long long* OpenMsg) {
	if (CryptMsg > n) return false;
	*OpenMsg = PowMod(CryptMsg, D, n);
	return true;
}