/*

*/
#include "advent.h"

static char **arr;
static int cnt;
static void freeAll() {
	for(int i = 0; i < cnt; i++)
		free(arr[i]);
	free(arr);
}

/*##########################
# Get input data from file #
##########################*/
static int getInput(char *f) {
	char * line = NULL;
	size_t l;
	arr = NULL;
	cnt = 0;

	FILE *file = fopen(f, "r");
	if(file == NULL) {
		printf("ERR: CAN NOT OPEN '%s'\n\n", f);
		return 0;
	}

	while( getline(&line, &l, file) != -1) {
		arr = realloc(arr, ++cnt * sizeof(char*));
		line = trim(line);
		arr[cnt-1] = malloc(strlen(line) + 1);
		strcpy(arr[cnt-1],line);
	}

	free(line);
	fclose(file);
	return 1;
}

/*##########################
# Function to solve part A #
##########################*/
void get18a(char * f) {
	if(!getInput(f))
		return;
	unsigned long long result = 0;
	char operands[20] = {};
	unsigned long long braces[20] = {};
	int cntBraces = 0;
	int cntOperands = 0;
	for(int i = 0; i < cnt; i++) {
		for(int i = 0; i < 20; i++)
			braces[i] = 0;
		cntBraces = 0;
		cntOperands = 0;
		for(int k = 0; k < strlen(arr[i]); k++) {
			if(arr[i][k] == ' ')
				continue;
			else if(arr[i][k] == '(') {
				 if(arr[i][k+1] == '(')
				 	operands[cntOperands] = operands[cntOperands++];
				 cntBraces++;
			}
			else if(arr[i][k] == ')') {
				if(cntOperands == 0)
					braces[cntBraces-1] = braces[cntBraces];
				else if(operands[cntOperands-1] == '*'){
					if(braces[cntBraces-1] == 0)
						braces[cntBraces-1] = 1;
					braces[cntBraces-1] *= braces[cntBraces];
					
				}
				else
					braces[cntBraces-1] += braces[cntBraces];
				braces[cntBraces] = 0;
				if(cntOperands)cntOperands--;
					cntBraces--;
			}
			else if(arr[i][k] == '+' || arr[i][k] == '*')
				operands[cntOperands++] = arr[i][k];
			else {
				if(cntBraces > 0) {
					if(arr[i][k-1] == '(')
						braces[cntBraces] = arr[i][k]-48;
					else if(operands[cntOperands-1] == '*'){
						if(braces[cntBraces] == 0)
							braces[cntBraces] = 1;
						braces[cntBraces] *= arr[i][k]-48;
					}
					else
						braces[cntBraces] += arr[i][k]-48;
					if(!(arr[i][k-1] == '('))
						cntOperands--;
					
				}
				else {
					if(cntOperands) {
						if(operands[cntOperands-1] == '*')
							braces[cntBraces] *= arr[i][k]-48;
						else
							braces[cntBraces] += arr[i][k]-48;
						cntOperands--;
					}
					else
						braces[cntBraces] = arr[i][k]-48;
				}
			}
		}
		result += braces[0];	
		
	}
	//7293529867931

	printf("18a: %llu\n", result);
	freeAll();
}

/*##########################
# Function to solve part B #
##########################*/
void get18b(char *f) {
	if(!getInput(f))
		return;

	unsigned long long result = 0;
	char operands[20] = {};
	unsigned long long braces[20] = {};
	int cntBraces = 0;
	int cntOperands = 0;
	
	for(int i = 0; i < cnt; i++) {
		for(int k = 0; k < strlen(arr[i]); k++) {
			
		}
		result += braces[0];	
	}

	printf("18b: %d\n\n", result);
	freeAll();
}
