#include "pch.h"
#include "Lab3_DLL_inner.h"
#include "Lab3_DLL_outer.h"
#include <stdlib.h>
#include <time.h>

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