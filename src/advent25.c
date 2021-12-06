/*

*/
#include "advent.h"

int key[2];
/*##########################
# Get input data from file #
##########################*/
static bool getInput(char *f) {


	FILE *file = fopen(f, "r");
	if (file == NULL) {
		printf("ERR: CAN NOT OPEN '%s'\n\n", f);
		return false;
	}

	fscanf(file, "%d%d", &key[0], &key[1]);

	fclose(file);
	return true;
}

/*##########################
# Function to solve part A #
##########################*/
void get7a(char * f) {
	if (!getInput(f)) return;
	
	long long result = 1,loop =0;
	while (result != key[0]) {
		result = (result * 7) % 20201227;
		loop++;
	}
	result = 1;
	for (int i = 0; i < loop; i++)
		result = (result * key[1]) % 20201227;
	
	printf("7a: %ld\n", result);
}

/*##########################
# Function to solve part B #
##########################*/
void get7b(char *f) {
	//if (!getInput(f)) return;

	int result = 0;

	printf("7b: %d\n\n", result);
}
