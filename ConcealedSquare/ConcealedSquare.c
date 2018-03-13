#include <stdio.h>
#include <math.h>
#include <string.h>

typedef struct {
	char data[29];
	int N;
} bignum;

void bignum_init(bignum *b, const char* str, int N) {
	b->N = N;

	for(int i = 0; i < N; ++i) {
		char c = str[N-1 - i];
		if(c == '*')
			b->data[28 - i] = c;
		else
			b->data[28 - i] = c - 48;
	}
}

void bignum_print(bignum *b) {
	for(int i = 0; i < 29; ++i) {
		char c = b->data[i];
		if(c == '*')
			printf("%c ", c);
		else
			printf("%i ", c);
	}
	printf("(%i)\n", b->N);
	fflush(stdout);
}

void bignum_square(bignum *b) {
	bignum res = { .data = {0}, .N = 0 };

	for(int i = 28; i > 28 - b->N; --i) {
		int carry = 0;

		for(int j = 28; j > 28 - b->N; --j) {
			int index = i + j - 28;
			int mul = b->data[i] * b->data[j] + carry;
			/* printf("%i * %i + %i = %i --- ", b->data[i], b->data[j], carry, mul); */
			carry = mul / 10;
			res.data[index] += mul % 10;
			/* printf("carry is %i and data at index %i is %i\n", carry, index, res.data[index]); */

			/* bignum_print(&res); */
			int val = res.data[index];
			int c = 0;
			while(val / 10 > 0) {
				res.data[index-c-1] += res.data[index-c] / 10;
				res.data[index-c] = res.data[index-c] % 10;
				val = res.data[index-c-1];
				++c;
			}
			/* bignum_print(&res); */
		}

		/* printf("Inner loop ended, carry is added\n"); */
		int index = i + 28 - b->N - 28;
		res.data[index] += carry;
		int val = res.data[index];
		int c = 0;
		while(val / 10 > 0) {
			res.data[index-c-1] += res.data[index-c] / 10;
			res.data[index-c] = res.data[index-c] % 10;
			val = res.data[index-c-1];
			++c;
		}
		/* bignum_print(&res); */
	}

	for(int i = 0; i < 29; i++) {
		b->data[i] = res.data[i];
	}
}

void bignum_copy(bignum *b1, bignum *b2) {
	b1->N = b2->N;

	for(int i = 0; i < 29; ++i) {
		b1->data[i] = b2->data[i];
	}
}

int bignum_compare(bignum *b1, bignum *b2) {
	for(int i = 28; i >= 0; --i) {
		if(b1->data[i] == b2->data[i] || b1->data[i] == '*' || b2->data[i] == '*') {
			continue;
		} else {
			return 0;
		}
	}

	return 1;
}

void bignum_increase(bignum *b, int i) {
	b->data[28] += i;

	int val = b->data[28];
	int c = 0;
	while(val / 10 > 0) {
		b->data[28-c-1] += b->data[28-c] / 10;
		b->data[28-c] = b->data[28-c] % 10;
		val = b->data[28-c-1];
		++c;
	}

	if(c + 1 > b->N) {
		b->N = c+1;
	}
}

void getLimits(int N, int firstKnownDigit, bignum *min, bignum *max) {
	min->N = N / 2 + 1;
	max->N = N;
	min->data[28 - min->N+1] = 1;
	max->data[28 - max->N+1] = 1;
}

int findRoot(bignum *target, bignum *min, bignum *max, bignum *root) {
	bignum i;
	bignum_copy(&i, min);

	bignum square;
	for(; bignum_compare(&i, max) == 0; bignum_increase(&i, 1)) {
		printf("i = ");
		bignum_print(&i);
		bignum_copy(&square, &i);
		bignum_square(&square);
		if(bignum_compare(&square, target) == 1) {
			bignum_copy(root, &i);
			return 1;
		}
	}

	return 0;
}

int main(void) {
	/* int N; */
    /* scanf("%i", &N); */
    /* int knownDigits[N]; */
    /*  */
    /* for(int i = 0; i < N; ++i) { */
    /*     scanf("%i", knownDigits + i); */
    /* } */

	// 11241047259121309353409
	// 1 2 1 4 2 9 2 3 9 5 4 9
	//int knownDigits[] = { 1, 2, 1, 4, 2, 9, 2, 3, 9, 5, 4, 9 };
	//int N = 12;

	bignum square = { .data = {0}, .N = 1 };
	int N = 23;
	bignum_init(&square, "1*2*1*4*2*9*2*3*9*5*4*9", N);
	bignum_print(&square);

	bignum min = { .data = {0}, .N = 1 };
	bignum max = { .data = {0}, .N = 1 };
	getLimits(N, square.data[28 - N + 1], &min, &max);

	printf("min = ");
	bignum_print(&min);
	printf("max = ");
	bignum_print(&max);

	bignum root = { .data = {0}, .N = 1 };
	int rootFound = findRoot(&square, &min, &max, &root);
	if(rootFound)
		bignum_print(&root);

	/* int knownDigits[] = { 8, 7, 6 }; */
	/* int N = 3; */
	/* int knownDigits[] = { 1, 2, 3, 4 }; */
	/* int N = 4; */

	/* unsigned long long int min, max; */
	/* getLimits(N, knownDigits, &min, &max); */
    /*  */
	/* printf("min = %lli, max = %lli\n", min, max); */
	/* fflush(stdout); */
	/* printf("%i\n", concealedSquare); */

	return 0;
}
