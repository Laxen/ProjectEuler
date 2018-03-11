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

void getLimits(int N, int firstKnownDigit, int *min, int *max) {
	int nTotalDigits = 2 * N - 1;
	*min = sqrt(firstKnownDigit * pow(10, nTotalDigits - 1));
	*max = pow(10, (nTotalDigits + 1) / 2);
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

	int knownDigits[] = { 1, 2, 7, 1, 7, 4, 1 };
	int N = 7;
	int min, max;
	getLimits(N, knownDigits[0], &min, &max);

	printf("min = %i, max = %i\n", min, max);
	int concealedSquare = getConcealedSquare(knownDigits, N, min, max);
	printf("%i\n", concealedSquare);

	return 0;
}
