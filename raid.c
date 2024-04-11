#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char** argv) {
	// global variables
	char* T = malloc(sizeof(char*));
	unsigned char N;
	unsigned char C;
	long long S;
	uint Q;

	// read in input from stdin
	scanf("%s %hhu %hhu %lld %u", T, &N, &C, &S, &Q);

	// iterate through list of queries
	for(int i = 0; i < Q; i++) {
		uint block;
		uint disk;
		uint stripe;
		uint disk2;
		// read in block
		scanf("%d", &block);
		// raid 0
		if(strcmp(T, "0") == 0){
			disk = (block / C) % N;
			stripe = ((block / C) / N) * C + (block % C);
			printf("%d %d\n", disk, stripe);
		} else if (strcmp(T, "1") == 0) {
			disk = 0;
			stripe = block;
			printf("%d %d %d\n", disk, stripe, 1);
		} else if (strcmp(T, "01") == 0) {
			disk = block % (N / 2);
			stripe = block / (N / 2);
			disk2 = disk + (N / 2);
			printf("%d %d %d\n", disk, stripe, disk2);
		} else if (strcmp(T, "10") == 0) {
			disk = block % (N / 2) * (C + 1);
			stripe = block / (N / 2);
			disk2 = disk + 1;
			printf("%d %d %d\n", disk, stripe, disk2);
		} else if (strcmp(T, "4") == 0) {
			disk = block % (N - 1);
			stripe = (block - disk) / (N - 1);
			disk2 = N - 1;
			printf("%d %d %d\n", disk, stripe, disk2);
		} else if (strcmp(T, "5") == 0) {
			disk = block % N;
			stripe = block / (N - 1);
			disk2 = (N - 1) - stripe % N;
			printf("%d %d %d\n", disk, stripe, disk2);
		}
	}

	return 0;
}