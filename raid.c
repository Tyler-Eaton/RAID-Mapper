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
		int block;
		int disk;
		int stripe;
		// read in block
		scanf("%d", &block);
		// raid 0
		if(strcmp(T, "0") == 0){
			disk = (block / C) % N;
			stripe = disk < N / 2 ? (block % C) + (block / N) : ((block % C) + (block / N) - 1);
			printf("%d %d\n", disk, stripe);
		} else if (strcmp(T, "1") == 0) {
			disk = 0;
			stripe = block;
			printf("%d %d %d\n", disk, stripe, 1);
		} else if (strcmp(T, "01") == 0) {
			disk = block % (N / 2);
			stripe = block / (N / 2);
			int disk2 = disk + (N / 2);
			printf("%d %d %d\n", disk, stripe, disk2);
		}
	}

	return 0;
}