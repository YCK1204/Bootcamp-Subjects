#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define HALF_INT_MIN -1073741824;

int SignToggle(int n);
int Abs(int n);
void Add(int* a, int b);
int Divide(int* a, int b);
void Subtract(int* a, int b);
void Multiply(int* a, int b);

int main(void) {
	int a, b;
	char operator;

	while (true) {
		scanf_s("%d %c %d", &a, &operator, 1, &b);

		switch (operator)
		{
		case '+':
			Add(&a, b);
			break;
		case '-':
			Subtract(&a, b);
			break;
		case '/':
			b = Divide(&a, b);
			break;
		case '*':
			Multiply(&a, b);
			break;
		default:
			fprintf(stderr, "Error : operator is not avlid %c\n", operator);
			return 1;
		}
		if (operator == '/')
			printf("¸ò:%d, ³ª¸ÓÁö:%d\n", b, a);
		else
			printf("%d\n", a);
	}
	return 0;
}

int SignToggle(int n) {
	return (~n + 1);
}

int Abs(int n) {
	return (n < 0) ? SignToggle(n) : n;
}

void Add(int* a, int b) {
	while (b != 0) {
		int c = *a & b;
		*a = *a ^ b;
		b = c << 1;
	}
}

void Subtract(int* a, int b) {
	Add(a, SignToggle(b));
}

int Divide(int* a, int b) {
	if (b == 0)
	{
		fprintf(stderr, "Error : Division by zero");
		exit(1);
	}

	if (*a == INT_MIN && b == INT_MIN) {
		*a = 0;
		return 1;
	}

	if (b == INT_MIN)
		return 0;

	if (*a == INT_MIN) {
		if (b == -1) {
			fprintf(stderr, "Error : Integer Overflow");
			exit(1);
		}

		int t = HALF_INT_MIN; // INT_MIN / 2

		if (Abs(b) > Abs(t)) {
			Add(a, Abs(b));
			if (b < 0)
				return 1;
			return -1;
		}

		int n = Divide(&t, b);
		Multiply(&n, 2);
		Multiply(&t, 2);
		if (Abs(t) >= Abs(b)) {
			Add(&n, 1);
			t = SignToggle(Abs(t) - Abs(b));
		}
		*a = t;
		return n;
	}

	bool negativeResult = false;
	if ((*a < 0 && b > 0) || (*a > 0 && b < 0))
		negativeResult = true;
	bool negativeA = *a < 0;

	*a = Abs(*a);
	b = Abs(b);

	int ret = 0;
	while (*a >= b) {
		int t1 = b;
		int t2 = 1;
		while (*a >= (t1 << 1) && (t1 << 1) > 0) {
			t1 <<= 1;
			t2 <<= 1;
		}
		Add(&ret, t2);
		Subtract(a, t1);
	}
	if (negativeResult)
		ret = SignToggle(ret);
	if (negativeA)
		*a = SignToggle(*a);
	return ret;
}

void Multiply(int* a, int b) {
	bool negativeResult = false;
	if ((*a < 0 && b > 0) || (*a > 0 && b < 0))
		negativeResult = true;

	*a = Abs(*a);
	b = Abs(b);

	int t = 0;
	while (b != 0) {
		if (b & 1)
			Add(&t, *a);
		*a <<= 1;
		if ((b >> 1) == b)
			break;
		b >>= 1;
	}

	if (negativeResult)
		t = SignToggle(t);
	*a = t;
}