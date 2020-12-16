/*
--- Day 16: Ticket Translation ---
As you're walking to yet another connecting flight, you realize that one of the legs of your re-routed trip coming up is on a high-speed train. However, the train ticket you were given is in a language you don't understand. You should probably figure out what it says before you get to the train station after the next flight.

Unfortunately, you can't actually read the words on the ticket. You can, however, read the numbers, and so you figure out the fields these tickets must have and the valid ranges for values in those fields.

You collect the rules for ticket fields, the numbers on your ticket, and the numbers on other nearby tickets for the same train service (via the airport security cameras) together into a single document you can reference (your puzzle input).

The rules for ticket fields specify a list of fields that exist somewhere on the ticket and the valid ranges of values for each field. For example, a rule like class: 1-3 or 5-7 means that one of the fields in every ticket is named class and can be any value in the ranges 1-3 or 5-7 (inclusive, such that 3 and 5 are both valid in this field, but 4 is not).

Each ticket is represented by a single line of comma-separated values. The values are the numbers on the ticket in the order they appear; every ticket has the same format. For example, consider this ticket:

.--------------------------------------------------------.
| ????: 101    ?????: 102   ??????????: 103     ???: 104 |
|                                                        |
| ??: 301  ??: 302             ???????: 303      ??????? |
| ??: 401  ??: 402           ???? ????: 403    ????????? |
'--------------------------------------------------------'
Here, ? represents text in a language you don't understand. This ticket might be represented as 101,102,103,104,301,302,303,401,402,403; of course, the actual train tickets you're looking at are much more complicated. In any case, you've extracted just the numbers in such a way that the first number is always the same specific field, the second number is always a different specific field, and so on - you just don't know what each position actually means!

Start by determining which tickets are completely invalid; these are tickets that contain values which aren't valid for any field. Ignore your ticket for now.

For example, suppose you have the following notes:

class: 1-3 or 5-7
row: 6-11 or 33-44
seat: 13-40 or 45-50

your ticket:
7,1,14

nearby tickets:
7,3,47
40,4,50
55,2,20
38,6,12
It doesn't matter which position corresponds to which field; you can identify invalid nearby tickets by considering only whether tickets contain values that are not valid for any field. In this example, the values on the first nearby ticket are all valid for at least one field. This is not true of the other three nearby tickets: the values 4, 55, and 12 are are not valid for any field. Adding together all of the invalid values produces your ticket scanning error rate: 4 + 55 + 12 = 71.

Consider the validity of the nearby tickets you scanned. What is your ticket scanning error rate?

Your puzzle answer was 26053.

--- Part Two ---
Now that you've identified which tickets contain invalid values, discard those tickets entirely. Use the remaining valid tickets to determine which field is which.

Using the valid ranges for each field, determine what order the fields appear on the tickets. The order is consistent between all tickets: if seat is the third field, it is the third field on every ticket, including your ticket.

For example, suppose you have the following notes:

class: 0-1 or 4-19
row: 0-5 or 8-19
seat: 0-13 or 16-19

your ticket:
11,12,13

nearby tickets:
3,9,18
15,1,5
5,14,9
Based on the nearby tickets in the above example, the first position must be row, the second position must be class, and the third position must be seat; you can conclude that in your ticket, class is 12, row is 11, and seat is 13.

Once you work out which field is which, look for the six fields on your ticket that start with the word departure. What do you get if you multiply those six values together?

Your puzzle answer was 1515506256421.
*/
#include "advent.h"
#define INRANGE2(v,w,x,y,z) (INRANGE((v),(w),(x)) || INRANGE((v),(y),(z)))

typedef struct {
	int val[40];
} Ticket;

typedef struct {
	char name[40];
	int min1;
	int min2;
	int max1;
	int max2;
	int pos;
} Range;

static Ticket *tickets;
static Range *ranges;
static int cntT;
static int cntR;
static int cntV;

/*##########################
# Get input data from file #
##########################*/
static int getInput(char *f) {
	char * line = NULL;
	size_t l;
	tickets = NULL;
	ranges = NULL;
	cntT = 0;
	cntR = 0;

	FILE *file = fopen(f, "r");
	if(file == NULL) {
		printf("ERR: CAN NOT OPEN '%s'\n\n", f);
		return 0;
	}

	while( getline(&line, &l, file) != -1) {
		
		if(strcmp(line,"\n") == 0 || strcmp(line,"your ticket:\n") == 0 || strcmp(line,"nearby tickets:\n") == 0)
			continue;
		else if(line[0] > 47 && line[0] < 58){
			tickets = realloc(tickets, ++cntT * sizeof(Ticket));
			cntV = 0;
			char *p = strtok(line,",");
			while(p){
				tickets[cntT-1].val[cntV++] = toI(p);
				p = strtok(NULL, ",");
			}
		}
		else {
			ranges = realloc(ranges, ++cntR * sizeof(Range));
			sscanf(line,"%[^:]: %d-%d or %d-%d",ranges[cntR-1].name, &ranges[cntR-1].min1, &ranges[cntR-1].max1, &ranges[cntR-1].min2, &ranges[cntR-1].max2);
		}
	}
	free(line);
	fclose(file);
	return 1;
}

/*##########################
# Function to solve part A #
##########################*/
void get16a(char * f) {
	if(!getInput(f))
		return;
	
	int result = 0;

	for(int i = 1, k= 0; i < cntT; (k < cntV-1) ? k++ :(k = 0, i++)) {
			int valid = false;
			for(int m = 0; m < cntR; m++)
				if(INRANGE2(tickets[i].val[k], ranges[m].min1, ranges[m].max1, ranges[m].min2, ranges[m].max2))
					valid = true;
			if(!valid)
				result += tickets[i].val[k];
	}
	
	printf("16a: %d\n", result);
	free(tickets);
	free(ranges);
}

/*##########################
# Function to solve part B #
##########################*/
void get16b(char *f) {
	if(!getInput(f))
		return;

	unsigned long long result = 1;
	int pos[cntR][cntV];
	char *pre = "departure";
	int cntValid = 0, cntPos = 0, ticketValid;

	for(int i = 0, k = 0; i < cntR; (k < cntV-1) ? k++ : (k = 0, i++))
		pos[i][k] = 0;

	for(int i = 1; i < cntT; i++){
		for(int k = 0; k < cntV; k++){
			ticketValid = false;
			for(int m = 0; m < cntR; m++)
				if(INRANGE2(tickets[i].val[k], ranges[m].min1, ranges[m].max1, ranges[m].min2, ranges[m].max2))
					ticketValid = true;
			if(!ticketValid)
				break;
		}
		if(ticketValid) {
			cntValid++;
			for(int k = 0, m = 0; k < cntV; m < cntR-1 ? m++ : (m = 0, k++))
				if(INRANGE2(tickets[i].val[k], ranges[m].min1, ranges[m].max1, ranges[m].min2, ranges[m].max2))
					pos[m][k]++;
		}
	}

	while(cntPos < cntR){
		for(int i = 0; i < cntV; i++) {
			int cntFound = 0;
			int posFound = 0;
			for(int k = 0; k < cntR; k++)
				if(pos[k][i] == cntValid) {
					cntFound++;
					posFound = k;
				}
			if(cntFound == 1) {
				cntPos++;
				ranges[posFound].pos = i;
				for(int m = 0; m < cntV; m++)
					pos[posFound][m] = 0;
			}
		}
	}

	for(int i =0; i < cntR;i++)
		if(strncmp(pre,ranges[i].name,strlen(pre)) == 0)
			result *= tickets[0].val[ranges[i].pos];

	printf("16b: %llu\n\n", result);
	free(tickets);
	free(ranges);
}
