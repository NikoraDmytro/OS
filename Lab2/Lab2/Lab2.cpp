#include <iostream>

#include "../Lab2_DLL/Lab2_outer.h";

using namespace std;

int main() {
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
