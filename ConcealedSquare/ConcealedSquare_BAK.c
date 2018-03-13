#include <stdio.h>
#include <math.h>

int getConcealedSquare(int knownDigits[], int N, unsigned long long int min, unsigned long long int max) {
	for(unsigned long long int i = min; i < max; ++i) {
		//unsigned long long int num = pow(i, base);
		unsigned long long int num = i * i;
		if(i == 135245145)
			printf("num is %lli\n", num);

		int correct = 1;
		for (int j = 0; j < N; ++j) {
			int element = (num % (unsigned long long int) pow(10, 2*j+1) - num % (unsigned long long int) pow(10, 2*j)) / pow(10, 2*j);
			if(num == 18291249246071025)
				printf("%lli has %i at index %i, we want it to have %i\n", num, element, j, knownDigits[N - j - 1]);

			if(element != knownDigits[N - j - 1]) {
				correct = 0;
				break;
			} else {
				//printf("%lli has %i at index %i\n", num, element, j);
			}
		}

		if(correct) {
			return i;
		}
	}

	return -1;
}

void getLimits(int N, int knownDigits[], unsigned long long int *min, unsigned long long int *max) {
	*min = 0;
	*max = 0;

	int nTotalDigits = 2 * N - 1;
	for (int i = 0; i < N; ++i) {
		*min += knownDigits[i] * pow(10, nTotalDigits - 2*i - 1);
		*min += 1*pow(10, nTotalDigits - 2*i - 2);

		*max += knownDigits[i] * pow(10, nTotalDigits - 2*i - 1);
		*max += 9*pow(10, nTotalDigits - 2*i - 2);
	}

	*min = sqrt(*min);
	*max = sqrt(*max);
}

int main(void) {
	/*
	* Can probably do this with bits if you
	* construct a sequence using the known
	* digits where unknown spots has 0, and
	* then AND it with possible solutions.
	* If it returns the original sequence,
	* you've found the solution
	*/
	int N;
    scanf("%i", &N);
    int knownDigits[N];

    for(int i = 0; i < N; ++i) {
        scanf("%i", knownDigits + i);
    }

	// 11241047259121309353409
	// 1 2 1 4 2 9 2 3 9 5 4 9
	//int knownDigits[] = { 1, 2, 1, 4, 2, 9, 2, 3, 9, 5, 4, 9 };
	//int N = 12;

	//int knownDigits[] = { 8, 7, 6 };
	//int N = 3;
	//int knownDigits[] = { 1, 2, 3, 4 };
	//int N = 4;

	unsigned long long int min, max;
	getLimits(N, knownDigits, &min, &max);

	printf("min = %lli, max = %lli\n", min, max);
	fflush(stdout);
	int concealedSquare = getConcealedSquare(knownDigits, N, min, max);
	printf("%i\n", concealedSquare);

	return 0;
}
