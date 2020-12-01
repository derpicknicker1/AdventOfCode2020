/*
--- Day 1: Report Repair ---
After saving Christmas five years in a row, you've decided to take a vacation at a nice resort on a tropical island. Surely, Christmas will go on without you.

The tropical island has its own currency and is entirely cash-only. The gold coins used there have a little picture of a starfish; the locals just call them stars. None of the currency exchanges seem to have heard of them, but somehow, you'll need to find fifty of these coins by the time you arrive so you can pay the deposit on your room.

To save your vacation, you need to get all fifty stars by December 25th.

Collect stars by solving puzzles. Two puzzles will be made available on each day in the Advent calendar; the second puzzle is unlocked when you complete the first. Each puzzle grants one star. Good luck!

Before you leave, the Elves in accounting just need you to fix your expense report (your puzzle input); apparently, something isn't quite adding up.

Specifically, they need you to find the two entries that sum to 2020 and then multiply those two numbers together.

For example, suppose your expense report contained the following:

1721
979
366
299
675
1456
In this list, the two entries that sum to 2020 are 1721 and 299. Multiplying them together produces 1721 * 299 = 514579, so the correct answer is 514579.

Of course, your expense report is much larger. Find the two entries that sum to 2020; what do you get if you multiply them together?

Your puzzle answer was 388075.

--- Part Two ---
The Elves in accounting are thankful for your help; one of them even offers you a starfish coin they had left over from a past vacation. They offer you a second one if you can find three numbers in your expense report that meet the same criteria.

Using the above example again, the three entries that sum to 2020 are 979, 366, and 675. Multiplying them together produces the answer, 241861950.

In your expense report, what is the product of the three entries that sum to 2020?

Your puzzle answer was 293450526.
*/
#include "advent.h"

int *arr;
int cnt;

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
		arr = realloc(arr, ++cnt * sizeof(int));
		arr[cnt-1] = toI(line);
	}

	free(line);
	fclose(file);
	return 1;
}

int solve(int n) {
	for(int i = 0; i < cnt; i++) 
		for(int k = i+1; k < cnt; k++) {
			if((arr[i] + arr[k]) == 2020 && !n)
				return arr[i] * arr[k];
			else if (n)
				for(int m = k+1; m < cnt; m++) 
					if((arr[i] + arr[k] + arr[m]) == 2020)
						return arr[i] * arr[k] * arr[m];
		}
}

/*##########################
# Function to solve part A #
##########################*/
void get1a(char * f) {
	if(!getInput(f))
		return;

	printf("1a: %d\n", solve(0));
	free(arr);
}


/*##########################
# Function to solve part B #
##########################*/
void get1b(char *f) {
	if(!getInput(f))
		return;

	printf("1b: %d\n\n", solve(1));
	free(arr);
}