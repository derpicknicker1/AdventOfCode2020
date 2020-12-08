/*
--- Day 7: Handy Haversacks ---
You land at the regional airport in time for your next flight. In fact, it looks like you'll even have time to grab some food: all flights are currently delayed due to issues in luggage processing.

Due to recent aviation regulations, many rules (your puzzle input) are being enforced about bags and their contents; bags must be color-coded and must contain specific quantities of other color-coded bags. Apparently, nobody responsible for these regulations considered how long they would take to enforce!

For example, consider the following rules:

light red bags contain 1 bright white bag, 2 muted yellow bags.
dark orange bags contain 3 bright white bags, 4 muted yellow bags.
bright white bags contain 1 shiny gold bag.
muted yellow bags contain 2 shiny gold bags, 9 faded blue bags.
shiny gold bags contain 1 dark olive bag, 2 vibrant plum bags.
dark olive bags contain 3 faded blue bags, 4 dotted black bags.
vibrant plum bags contain 5 faded blue bags, 6 dotted black bags.
faded blue bags contain no other bags.
dotted black bags contain no other bags.
These rules specify the required contents for 9 bag types. In this example, every faded blue bag is empty, every vibrant plum bag contains 11 bags (5 faded blue and 6 dotted black), and so on.

You have a shiny gold bag. If you wanted to carry it in at least one other bag, how many different bag colors would be valid for the outermost bag? (In other words: how many colors can, eventually, contain at least one shiny gold bag?)

In the above rules, the following options would be available to you:

A bright white bag, which can hold your shiny gold bag directly.
A muted yellow bag, which can hold your shiny gold bag directly, plus some other bags.
A dark orange bag, which can hold bright white and muted yellow bags, either of which could then hold your shiny gold bag.
A light red bag, which can hold bright white and muted yellow bags, either of which could then hold your shiny gold bag.
So, in this example, the number of bag colors that can eventually contain at least one shiny gold bag is 4.

How many bag colors can eventually contain at least one shiny gold bag? (The list of rules is quite long; make sure you get all of it.)

Your puzzle answer was 274.

--- Part Two ---
It's getting pretty expensive to fly these days - not because of ticket prices, but because of the ridiculous number of bags you need to buy!

Consider again your shiny gold bag and the rules from the above example:

faded blue bags contain 0 other bags.
dotted black bags contain 0 other bags.
vibrant plum bags contain 11 other bags: 5 faded blue bags and 6 dotted black bags.
dark olive bags contain 7 other bags: 3 faded blue bags and 4 dotted black bags.
So, a single shiny gold bag must contain 1 dark olive bag (and the 7 bags within it) plus 2 vibrant plum bags (and the 11 bags within each of those): 1 + 1*7 + 2 + 2*11 = 32 bags!

Of course, the actual rules have a small chance of going several levels deeper than this example; be sure to count all of the bags, even if the nesting becomes topologically impractical!

Here's another example:

shiny gold bags contain 2 dark red bags.
dark red bags contain 2 dark orange bags.
dark orange bags contain 2 dark yellow bags.
dark yellow bags contain 2 dark green bags.
dark green bags contain 2 dark blue bags.
dark blue bags contain 2 dark violet bags.
dark violet bags contain no other bags.
In this example, a single shiny gold bag must contain 126 other bags.

How many individual bags are required inside your single shiny gold bag?

Your puzzle answer was 158730.
*/
#include "advent.h"

typedef struct {
	char name[25]; //max 20
	int  nr;
	int  inCnt;
	int  bags[25]; //max 19
	int  containAmnt[25];
	int  contain[25];
	int  conCnt;

} Bag;

static Bag *bags;
static int cntBags;

static int getOrSetBagName(char *bagName,int in) {

	for(int i = 0; i < cntBags; i++)
		if(strcmp(bags[i].name,bagName) == 0 ) {
			if(in != -1)
				bags[i].bags[bags[i].inCnt++] = in;
			return i;
		}

	bags = realloc(bags, ++cntBags * sizeof(Bag));
	strcpy(bags[cntBags-1].name, bagName);
	bags[cntBags-1].nr = cntBags - 1;
	bags[cntBags-1].bags[0] = in;		
	bags[cntBags-1].inCnt = (in == -1) ? 0 : 1;
	bags[cntBags-1].conCnt = 0;

	return cntBags - 1;

}

static void insertBag(int bag, int conBag, int amnt) {
	for(int i = 0; i < cntBags; i++)
		if(bags[i].nr == bag) {
			bags[i].containAmnt[bags[i].conCnt] = amnt;
			bags[i].contain[bags[i].conCnt++] = conBag;
		}

}

static void cntInBags(int bag ,int *res, int arr[]){
	if(bags[bag].inCnt > 0)
		for(int i = 0; i < bags[bag].inCnt; i++) 
			if(arr[bags[bag].bags[i]]) {
				arr[bags[bag].bags[i]] = 0;
				*res+=1;
				cntInBags(bags[bag].bags[i], res, arr);
			}
}


static void cntConBags(int bag ,int *res, int arr[], int mul){
	if(bags[bag].conCnt > 0)
		for(int i = 0; i < bags[bag].conCnt; i++) {
			*res += bags[bag].containAmnt[i] * mul;
			cntConBags(bags[bag].contain[i], res, arr, bags[bag].containAmnt[i]*mul);
		}
							
}

/*##########################
# Get input data from file #
##########################*/
static int getInput(char *f) {
	char * line = NULL;
	size_t l;
	bags = NULL;
	cntBags = 0;

	FILE *file = fopen(f, "r");
	if(file == NULL) {
		printf("ERR: CAN NOT OPEN '%s'\n\n", f);
		return 0;
	}

	while( getline(&line, &l, file) != -1) {
		char buff1[25]; //complete name (buff1+buff2) max 20
		char buff2[25];
		char buffRest[150]; //max 93		
		sscanf(line, "%s %s bags contain %[^.]", buff1, buff2, buffRest);
		int bag = getOrSetBagName(strcat(buff1,buff2), -1);
		char *p = strtok(buffRest,",");
		while(p) {
			if(p[0] != 'n') {
				int x;
				sscanf(p, "%d %s %s", &x, buff1, buff2);
				int conBag = getOrSetBagName(strcat(buff1,buff2), bag);
				insertBag(bag, conBag, x);
			}
			p = strtok(NULL,",");
		}
		
	}

	free(line);
	fclose(file);
	return 1;
}

/*##########################
# Function to solve part A #
##########################*/
void get7a(char * f) {
	if(!getInput(f))
		return;

	int result = 0;
	int bag;
	int arr[cntBags];

	for (int i = 0; i < cntBags; i++) {
		if(strcmp(bags[i].name,"shinygold") == 0) 
			bag = bags[i].nr;
		arr[i] = 1;
	}

	cntInBags(bag, &result, arr);

	printf("7a: %d\n", result);
	free(bags);
}


/*##########################
# Function to solve part B #
##########################*/
void get7b(char *f) {
	if(!getInput(f))
		return;

	int result = 0;
	int bag;
	int arr[cntBags];

	for (int i = 0; i < cntBags; i++) {
		if(strcmp(bags[i].name,"shinygold") == 0) 
			bag = bags[i].nr;
		arr[i] = 1;
	}

	cntConBags(bag, &result, arr, 1);

	printf("7b: %d\n\n", result);
	free(bags);
}