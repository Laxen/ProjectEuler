#include <stdio.h>
#include <math.h>

int getConcealedSquare(int knownDigits[], int N, int min, int max) {
	for(int i = min; i < max; ++i) {
		long long int num = pow(i, 2);
		if(num < 0) {
			printf("OVERFLOW\n");
			fflush(stdout);
			return -1;
		}

		int correct = 1;
		for (int j = 0; j < N; ++j) {
			int element = (num % (int) pow(10, 2*j+1) - num % (int) pow(10, 2*j)) / pow(10, 2*j);
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

void getLimits(int N, int knownDigits[], int *min, int *max) {
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
	/*
	int N;
    scanf("%i", &N);
    int knownDigits[N];
    
    for(int i = 0; i < N; ++i) {
        scanf("%i", knownDigits + i);
    }

	int min, max;
	getLimits(N, knownDigits[0], &min, &max);

	int concealedSquare = getConcealedSquare(knownDigits, N, min, max);
	printf("%i\n", concealedSquare);

	return 0;
	*/

	// 18291249246071025
	// 1 2 1 4 2 6 7 0 5
	int knownDigits[] = { 1, 2, 1, 4, 2, 6, 7, 0, 5 };
	int N = 9;

	//int knownDigits[] = { 8, 7, 6 };
	//int N = 3;
	//int knownDigits[] = { 1, 2, 3, 4 };
	//int N = 4;

	int min, max;
	getLimits(N, knownDigits, &min, &max);

	printf("min = %i, max = %i\n", min, max);
	fflush(stdout);
	int concealedSquare = getConcealedSquare(knownDigits, N, min, max);
	printf("%i\n", concealedSquare);

	return 0;
}
