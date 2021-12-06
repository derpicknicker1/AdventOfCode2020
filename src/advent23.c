/*
--- Day 23: Crab Cups ---
The small crab challenges you to a game! The crab is going to mix up some cups, and you have to predict where they'll end up.

The cups will be arranged in a circle and labeled clockwise (your puzzle input). For example, if your labeling were 32415, there would be five cups in the circle; going clockwise around the circle from the first cup, the cups would be labeled 3, 2, 4, 1, 5, and then back to 3 again.

Before the crab starts, it will designate the first cup in your list as the current cup. The crab is then going to do 100 moves.

Each move, the crab does the following actions:

The crab picks up the three cups that are immediately clockwise of the current cup. They are removed from the circle; cup spacing is adjusted as necessary to maintain the circle.
The crab selects a destination cup: the cup with a label equal to the current cup's label minus one. If this would select one of the cups that was just picked up, the crab will keep subtracting one until it finds a cup that wasn't just picked up. If at any point in this process the value goes below the lowest value on any cup's label, it wraps around to the highest value on any cup's label instead.
The crab places the cups it just picked up so that they are immediately clockwise of the destination cup. They keep the same order as when they were picked up.
The crab selects a new current cup: the cup which is immediately clockwise of the current cup.
For example, suppose your cup labeling were 389125467. If the crab were to do merely 10 moves, the following changes would occur:

-- move 1 --
cups: (3) 8  9  1  2  5  4  6  7 
pick up: 8, 9, 1
destination: 2

-- move 2 --
cups:  3 (2) 8  9  1  5  4  6  7 
pick up: 8, 9, 1
destination: 7

-- move 3 --
cups:  3  2 (5) 4  6  7  8  9  1 
pick up: 4, 6, 7
destination: 3

-- move 4 --
cups:  7  2  5 (8) 9  1  3  4  6 
pick up: 9, 1, 3
destination: 7

-- move 5 --
cups:  3  2  5  8 (4) 6  7  9  1 
pick up: 6, 7, 9
destination: 3

-- move 6 --
cups:  9  2  5  8  4 (1) 3  6  7 
pick up: 3, 6, 7
destination: 9

-- move 7 --
cups:  7  2  5  8  4  1 (9) 3  6 
pick up: 3, 6, 7
destination: 8

-- move 8 --
cups:  8  3  6  7  4  1  9 (2) 5 
pick up: 5, 8, 3
destination: 1

-- move 9 --
cups:  7  4  1  5  8  3  9  2 (6)
pick up: 7, 4, 1
destination: 5

-- move 10 --
cups: (5) 7  4  1  8  3  9  2  6 
pick up: 7, 4, 1
destination: 3

-- final --
cups:  5 (8) 3  7  4  1  9  2  6 
In the above example, the cups' values are the labels as they appear moving clockwise around the circle; the current cup is marked with ( ).

After the crab is done, what order will the cups be in? Starting after the cup labeled 1, collect the other cups' labels clockwise into a single string with no extra characters; each number except 1 should appear exactly once. In the above example, after 10 moves, the cups clockwise from 1 are labeled 9, 2, 6, 5, and so on, producing 92658374. If the crab were to complete all 100 moves, the order after cup 1 would be 67384529.

Using your labeling, simulate 100 moves. What are the labels on the cups after cup 1?

Your puzzle answer was 69425837.

--- Part Two ---
Due to what you can only assume is a mistranslation (you're not exactly fluent in Crab), you are quite surprised when the crab starts arranging many cups in a circle on your raft - one million (1000000) in total.

Your labeling is still correct for the first few cups; after that, the remaining cups are just numbered in an increasing fashion starting from the number after the highest number in your list and proceeding one by one until one million is reached. (For example, if your labeling were 54321, the cups would be numbered 5, 4, 3, 2, 1, and then start counting up from 6 until one million is reached.) In this way, every number from one through one million is used exactly once.

After discovering where you made the mistake in translating Crab Numbers, you realize the small crab isn't going to do merely 100 moves; the crab is going to do ten million (10000000) moves!

The crab is going to hide your stars - one each - under the two cups that will end up immediately clockwise of cup 1. You can have them if you predict what the labels on those cups will be when the crab is finished.

In the above example (389125467), this would be 934001 and then 159792; multiplying these together produces 149245887792.

Determine which two cups will end up immediately clockwise of cup 1. What do you get if you multiply their labels together?

Your puzzle answer was 218882971435.
*/
#include "advent.h"

typedef struct cup {
	int val;
	struct cup *next;
	struct cup *prev;
} Cup;

struct cuup
{
    struct cuup *next;
};
struct cuup  cuups[1000000];

static Cup *cups = NULL;
static int cnt;
static int maxVal;

static void freeCups() {
	Cup *ptr;
	cups->prev->next = NULL;
	do {
		ptr = cups->next;
		free(cups);
		cups = ptr;
	} while(ptr != NULL);
}

/*##########################
# Get input data from file #
##########################*/
static int getInput(char *f) {
	char * line = NULL;
	size_t l;
	cups = NULL;
	cnt = 0;
	maxVal = 0;

	FILE *file = fopen(f, "r");
	if(file == NULL) {
		printf("ERR: CAN NOT OPEN '%s'\n\n", f);
		return 0;
	}

	while( getline(&line, &l, file) != -1) {
		line = trim(line);
		Cup *head;
		for(int i = 0; i < strlen(line); i++) {
			cnt++;
			int val = line[i] - 48;
			if(cups == NULL) {
				cups = malloc(sizeof(Cup));
				cups->val = val;
				head = cups;
			}
			else{
				cups->next = malloc(sizeof(Cup));
				cups->next->prev = cups;
				cups = cups->next;
				cups->val = val;
			}
			if(line[i]-48 > maxVal)
				maxVal = line[i]-48;
		}
		cups->next = head;
		head->prev = cups;
		cups = head;
	}

	free(line);
	fclose(file);
	return 1;
}

/*##########################
# Function to solve part A #
##########################*/
void get23a(char * f) {
	if(!getInput(f))
		return;

	int val, max;
	Cup *start, *end, *begin, *dest;

	for(int i = 0; i < 100; i++) {
		// cut out three cups
		start=cups->next;
		end=cups->next->next->next;
		cups->next = end->next;
		end->next->prev = cups;
		val = cups->val -1;
		begin = cups->next;

		// search for smaller lable
		while(val > 0) {
			while(begin != cups) {
				if(begin->val == val)
					break;
				else
					begin = begin->next;
			}
			if(begin != cups)
				break;
			else
				begin = begin->next;
			val--;
		}

		// no smaller found, so find max
		if(val < 1) {
			max = 0;
			for(int k = 0; k < cnt-3; k++) {
				if(begin->val > max){
					max = begin->val;
					dest = begin;
				}
				begin = begin->next;
			}
			begin = dest;
		}

		// insert the three cups
		start->prev = begin;
		end->next = begin->next;
		end->next->prev = end;
		begin->next = start;
		cups = cups->next;
	}

	while(cups->val != 1) cups = cups->next;
		
	printf("23a: ");
	for(int i = 0; i < cnt-1; i++) {
		cups = cups->next;
		printf("%d",cups->val);
	}
	printf("\n");
	freeCups();
}

/*##########################
# Function to solve part B #
##########################*/
void get23b(char *f) {
	/*if(!getInput(f))
		return;*/

    unsigned long long result=1;
    int total=10000000, size=1000000;
    char buf[16];
    int dest;
    int shufflea,shuffleb,shufflec;
    struct cuup *last, *first, *current, *shuffle;

    FILE * fp;

    if((fp = fopen (f, "r"))==NULL) {
        printf("error opening file %s\n", f);
        return;
    }
    while(fgets(buf, 16, fp) != NULL) {
        last=first=&cuups[buf[0]-49];
        for(int i=1;i<9;i++) {
            last->next=&cuups[buf[i]-49];
            last=&cuups[buf[i]-49];
        }
    }

    for(int i=9;i<size;i++)
    {
        last->next=&cuups[i];
        last=&cuups[i];
    }

    //Linked list implementation
    last->next=first;
    current=first;
    for(int i=0;i<total;i++)
    {
        shuffle=current->next;
        shufflea=((current->next+1)-cuups);
        shuffleb=((current->next->next+1)-cuups);
        shufflec=((current->next->next->next+1)-cuups);
        current->next=current->next->next->next->next;
        dest =(current)-cuups;
        if(!dest)
            dest=size;
        while((dest==shufflea)||(dest==shuffleb)||(dest==shufflec))
            if(!--dest)
                dest=size;
        last=cuups[dest-1].next;
        cuups[dest-1].next=shuffle;
        shuffle->next->next->next=last;
        current=current->next;
    }
    current=cuups[0].next;

    result*=(current+1)-cuups;
    current=current->next;
    result*=(current+1)-cuups;
    printf("23b: %llu\n",result);
}
