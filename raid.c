#include <stdio.h>
#include <stdlib.h>

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
		disk = (block / C) % N;
		stripe = disk < N / 2 ? (block % C) + (block / N) : ((block % C) + (block / N) - 1);
		printf("%d %d\n", disk, stripe);
	}

	return 0;
}