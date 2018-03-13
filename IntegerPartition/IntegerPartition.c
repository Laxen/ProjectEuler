#include <stdio.h>
#include <math.h>

double findPartition(int k) {
	double x = 0.5 + sqrt(0.25 + k);
	double t = 2*log(x) / log(4);

	return t;
}

int main() {
	double t = findPartition(5);
	printf("%f\n", t);

	if(ceilf(t) == t) {
		printf("THIS BE INT");
	}

	return 0;
}

/*
 * 
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

double findPartition(int k) {
	double x = 0.5 + sqrt(0.25 + k);
	double t = 2*log(x) / log(4);

	return t;
}

int main() {    
    int BUFFERSIZE = 18;    
    char buffer[BUFFERSIZE];
    char *end;
    
    scanf("%s", buffer);
    int nQueries = strtol(buffer, &end, 10);    
    printf("nQueries = %i\n", nQueries);
    
    for(int i = 0; i < nQueries; ++i) {        
        scanf("%s", buffer);
        int a = strtol(buffer, &end, 10);
        printf("a = %i\n", a);

        scanf("%s", buffer);
        int b = strtol(buffer, &end, 10);
        printf("b = %i\n", b);
        
        double t = findPartition(5);
        printf("%f\n", t);

        if(ceilf(t) == t) {
            printf("THIS BE INT");
        }
    }
    
    return 0;
}
*/
