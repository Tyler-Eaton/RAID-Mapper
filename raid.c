#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// global variables
unsigned char N;
unsigned char C;
long long S;
uint Q;

// functions to calculate location with different raid variations
void raid_0(char* output, uint block) {
	uint disk = (block / C) % N;
	uint stripe = ((block / C) / N) * C + (block % C);
	sprintf(output, "%d %d\n", disk, stripe);
}

void raid_1(char* output, uint block) {
	uint disk = 0;
	uint stripe = block;
	sprintf(output, "%d %d %d\n", disk, stripe, 1);
}

void raid_01(char* output, uint block) {
	uint disk = block % (N / 2);
	uint stripe = block / (N / 2);
	uint disk2 = disk + (N / 2);
	sprintf(output, "%d %d %d\n", disk, stripe, disk2);
}

void raid_10(char* output, uint block) {
	uint disk = block % (N / 2) * (C + 1);
	uint stripe = block / (N / 2);
	uint disk2 = disk + 1;
	sprintf(output, "%d %d %d\n", disk, stripe, disk2);
}

void raid_4(char* output, uint block) {
	uint disk = block % (N - 1);
	uint stripe = (block - disk) / (N - 1);
	uint disk2 = N - 1;
	sprintf(output, "%d %d %d\n", disk, stripe, disk2);
}

void raid_5(char* output, uint block) {
	uint disk = block % N;
	uint stripe = block / (N - 1);
	uint disk2 = (N - 1) - stripe % N;
	sprintf(output, "%d %d %d\n", disk, stripe, disk2);
}

// created an array of the raid functions to simplify calling
void (*raid_functions[6])(char* output, uint block) = {
	raid_0, raid_1, raid_01, raid_10, raid_4, raid_5
};

int main(int argc, char** argv) {
	// allocate space for
	char* T = malloc(sizeof(char*));
	char* output = malloc(sizeof(char*));
	int index;

	// read in header input and store in globals
	scanf("%s %hhu %hhu %lld %u", T, &N, &C, &S, &Q);

	// set array index based on raid number specified in input
	if(strcmp(T, "01") == 0) {
		index = 2;
	} else if(strcmp(T, "10") == 0) {
		index = 3;
	} else {
		index = atoi(T);
	}

	// iterate through all queries
	for(int i = 0; i < Q; i++) {
		uint block;
		// read in block and calculate specific raid location and output
		scanf("%d", &block);
		raid_functions[index](output, block);
		printf("%s", output);
	}
	free(output);
	free(T);
	return 0;
}