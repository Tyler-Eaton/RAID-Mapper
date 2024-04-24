#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// global variables
unsigned char N;
unsigned char C;
long long S;
uint Q;

// struct to hold disk and stripe information
typedef struct {
	uint disk;
	uint stripe;
	uint disk2;
} location;

// modify location with new disk, stripe and disk2 information
void modify_location(location* data, uint disk, uint stripe, uint disk2) {
	data->disk = disk;
	data->stripe = stripe;
	data->disk2 = disk2;
}

// functions to calculate location with different raid variations
void raid_0(location* data, uint block) {
	uint disk = (block / C) % N;
	uint stripe = ((block / C) / N) * C + (block % C);
	uint disk2 = 0;
	modify_location(data, disk, stripe, disk2);
}

void raid_1(location* data, uint block) {
	uint disk = 0;
	uint stripe = block;
	uint disk2 = 1;
	modify_location(data, disk, stripe, disk2);
}

void raid_01(location* data, uint block) {
	uint disk = block % (N / 2);
	uint stripe = block / (N / 2);
	uint disk2 = disk + (N / 2);
	modify_location(data, disk, stripe, disk2);
}

void raid_10(location* data, uint block) {
	uint disk = block % (N / 2) * (C + 1);
	uint stripe = block / (N / 2);
	uint disk2 = disk + 1;
	modify_location(data, disk, stripe, disk2);
}

void raid_4(location* data, uint block) {
	uint disk = block % (N - 1);
	uint stripe = block / (N - 1);
	uint disk2 = N - 1;
	modify_location(data, disk, stripe, disk2);
}

void raid_5(location* data, uint block) {
	uint disk = block % N;
	uint stripe = block / (N - 1);
	uint disk2 = (N - 1) - (stripe % N);
	modify_location(data, disk, stripe, disk2);
}

// created an array of the raid functions to simplify calling
void (*raid_functions[6])(location* data, uint block) = {
	raid_0, raid_1, raid_01, raid_10, raid_4, raid_5
};

int main(int argc, char** argv) {
	// allocate space for
	char* T = malloc(sizeof(char*));
	// index to pick the correct raid function from array of functions
	int index;

	// struct to hold location information
	location data;

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
		raid_functions[index](&data, block);
		// if raid 0, only print disk and stripe
		if(index == 0) {
			printf("%d %d\n", data.disk, data.stripe);
		}
		else {
			printf("%d %d %d\n", data.disk, data.stripe, data.disk2);
		}
	}

	free(T);
	return 0;
}