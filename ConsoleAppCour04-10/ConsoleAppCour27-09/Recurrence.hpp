#pragma once

class Recurrence {
public :
	static int Add(int a, int b) {
		if (b == 0) return a;
		if (a == 0) return b;

		if (b < 0) {
			return Add(a - 1, b + 1);
		}
		return Add(a + 1, b - 1);
	}

	static int Sub(int a, int b) {
		return Add(a, -b);
	}

	static int Mul(int a, int b) {
		if (b == 0) return 0;
		if (a == 0) return 0;
		if (b > 0) {
			return Add(a, Mul(a, b - 1));  //empile Add - empile a, execute Mul, empile a, empile b
		}
		return -Mul(a, -b);
	}
	//éviter les apelle de fonction tardif 
	static int MulTerminalRecursion(int a, int b, int res = 0) {
		if (b == 0) return 0;
		if (a == 0) return 0;
		if (b == 1) return a;
		if (a == 1) return b;
		if (b > 0) {
			return MulTerminalRecursion(a, b - 1, a + res);
		}
		return MulTerminalRecursion(a, -b, -res);
	}

	static int Div(int a, int b) {
		if (a == 0) return 0;
		if (b == 0) {
			return 0;
		}
		if (b == 1) return a;
		if (a < b) return 0;
		if (a == b) return 1;

		if (b < 0) return -Div(a, -b);
		if (a < 0) return -Div(-a, b);

		return 1 + Div(Sub(a, b), b);
	}
	static int DivTR(int a, int b, int res = 0) {
		if (a == 0) return res;
		if (b == 0) {
			return 0;
		}
		if (b == 1) return a + res;
		if (a < b) return 0 + res;
		if (a == b) return 1 + res;

		if (b < 0) return DivTR(a, -b, res);
		if (a < 0) return DivTR(-a, b, -res);

		int leftover = a - b;
		return DivTR(leftover, b, res);
	}
};