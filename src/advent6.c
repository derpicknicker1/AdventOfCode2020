/*
--- Day 6: Custom Customs ---
As your flight approaches the regional airport where you'll switch to a much larger plane, customs declaration forms are distributed to the passengers.

The form asks a series of 26 yes-or-no questions marked a through z. All you need to do is identify the questions for which anyone in your group answers "yes". Since your group is just you, this doesn't take very long.

However, the person sitting next to you seems to be experiencing a language barrier and asks if you can help. For each of the people in their group, you write down the questions for which they answer "yes", one per line. For example:

abcx
abcy
abcz
In this group, there are 6 questions to which anyone answered "yes": a, b, c, x, y, and z. (Duplicate answers to the same question don't count extra; each question counts at most once.)

Another group asks for your help, then another, and eventually you've collected answers from every group on the plane (your puzzle input). Each group's answers are separated by a blank line, and within each group, each person's answers are on a single line. For example:

abc

a
b
c

ab
ac

a
a
a
a

b
This list represents answers from five groups:

The first group contains one person who answered "yes" to 3 questions: a, b, and c.
The second group contains three people; combined, they answered "yes" to 3 questions: a, b, and c.
The third group contains two people; combined, they answered "yes" to 3 questions: a, b, and c.
The fourth group contains four people; combined, they answered "yes" to only 1 question, a.
The last group contains one person who answered "yes" to only 1 question, b.
In this example, the sum of these counts is 3 + 3 + 3 + 1 + 1 = 11.

For each group, count the number of questions to which anyone answered "yes". What is the sum of those counts?

Your puzzle answer was 6310.

--- Part Two ---
As you finish the last group's customs declaration, you notice that you misread one word in the instructions:

You don't need to identify the questions to which anyone answered "yes"; you need to identify the questions to which everyone answered "yes"!

Using the same example as above:

abc

a
b
c

ab
ac

a
a
a
a

b
This list represents answers from five groups:

In the first group, everyone (all 1 person) answered "yes" to 3 questions: a, b, and c.
In the second group, there is no question to which everyone answered "yes".
In the third group, everyone answered yes to only 1 question, a. Since some people did not answer "yes" to b or c, they don't count.
In the fourth group, everyone answered yes to only 1 question, a.
In the fifth group, everyone (all 1 person) answered "yes" to 1 question, b.
In this example, the sum of these counts is 3 + 0 + 1 + 1 + 1 = 6.

For each group, count the number of questions to which everyone answered "yes". What is the sum of those counts?

Your puzzle answer was 3193.
*/
#include "advent.h"

static char **arr;
static int *cntGrp;
static int cnt;

static void freeArr() {
	for(int i = 0; i < cnt; i++)
		free(arr[i]);
	free(arr);
	free(cntGrp);
}

static void newArrEntry(){
	arr = realloc(arr, ++cnt * sizeof(char*));
	cntGrp = realloc(cntGrp, cnt * sizeof(int));
	cntGrp[cnt - 1] = 0;
	arr[cnt - 1] = malloc(26);
	for( int i = 0; i < 26; i++)
		arr[cnt - 1][i] = 0;
}

/*##########################
# Get input data from file #
##########################*/
static int getInput(char *f) {
	char * line = NULL;
	size_t l;
	arr = NULL;
	cntGrp = NULL;
	cnt = 0;
   
	FILE *file = fopen(f, "r");
	if(file == NULL) {
		printf("ERR: CAN NOT OPEN '%s'\n\n", f);
		return 0;
	}

	newArrEntry();
	while( getline(&line, &l, file) != -1) {
		
		if(strcmp(trim(line), "") == 0){
			newArrEntry();
			continue;
		}
		cntGrp[cnt - 1]++;
		for(int i = 0; i < strlen(line); i++)
			arr[cnt - 1][line[i]-'a']++;
	}

	free(line);
	fclose(file);
	return 1;
}

/*##########################
# Function to solve part A #
##########################*/
void get6a(char * f) {
	if(!getInput(f))
		return;

	int result = 0;

	for(int i = 0; i < cnt; i++) {
		int cntLetter = 0;
		for(int k = 0; k < 26; k++)
			if(arr[i][k] != 0)
				cntLetter++;
		result += cntLetter;
	}
	
	printf("6a: %d\n", result);
	freeArr();
}


/*##########################
# Function to solve part B #
##########################*/
void get6b(char *f) {
	if(!getInput(f))
		return;

	int result = 0;
	for(int i = 0; i < cnt; i++) {
		int cntLetter = 0;
		for(int k = 0; k < 26; k++)
			if(arr[i][k] == cntGrp[i])
				cntLetter++;
		result += cntLetter;
	}

	printf("6b: %d\n\n", result);
	freeArr();
}