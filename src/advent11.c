/*
--- Day 11: Seating System ---
Your plane lands with plenty of time to spare. The final leg of your journey is a ferry that goes directly to the tropical island where you can finally start your vacation. As you reach the waiting area to board the ferry, you realize you're so early, nobody else has even arrived yet!

By modeling the process people use to choose (or abandon) their seat in the waiting area, you're pretty sure you can predict the best place to sit. You make a quick map of the seat layout (your puzzle input).

The seat layout fits neatly on a grid. Each position is either floor (.), an empty seat (L), or an occupied seat (#). For example, the initial seat layout might look like this:

L.LL.LL.LL
LLLLLLL.LL
L.L.L..L..
LLLL.LL.LL
L.LL.LL.LL
L.LLLLL.LL
..L.L.....
LLLLLLLLLL
L.LLLLLL.L
L.LLLLL.LL
Now, you just need to model the people who will be arriving shortly. Fortunately, people are entirely predictable and always follow a simple set of rules. All decisions are based on the number of occupied seats adjacent to a given seat (one of the eight positions immediately up, down, left, right, or diagonal from the seat). The following rules are applied to every seat simultaneously:

If a seat is empty (L) and there are no occupied seats adjacent to it, the seat becomes occupied.
If a seat is occupied (#) and four or more seats adjacent to it are also occupied, the seat becomes empty.
Otherwise, the seat's state does not change.
Floor (.) never changes; seats don't move, and nobody sits on the floor.

After one round of these rules, every seat in the example layout becomes occupied:

#.##.##.##
#######.##
#.#.#..#..
####.##.##
#.##.##.##
#.#####.##
..#.#.....
##########
#.######.#
#.#####.##
After a second round, the seats with four or more occupied adjacent seats become empty again:

#.LL.L#.##
#LLLLLL.L#
L.L.L..L..
#LLL.LL.L#
#.LL.LL.LL
#.LLLL#.##
..L.L.....
#LLLLLLLL#
#.LLLLLL.L
#.#LLLL.##
This process continues for three more rounds:

#.##.L#.##
#L###LL.L#
L.#.#..#..
#L##.##.L#
#.##.LL.LL
#.###L#.##
..#.#.....
#L######L#
#.LL###L.L
#.#L###.##
#.#L.L#.##
#LLL#LL.L#
L.L.L..#..
#LLL.##.L#
#.LL.LL.LL
#.LL#L#.##
..L.L.....
#L#LLLL#L#
#.LLLLLL.L
#.#L#L#.##
#.#L.L#.##
#LLL#LL.L#
L.#.L..#..
#L##.##.L#
#.#L.LL.LL
#.#L#L#.##
..L.L.....
#L#L##L#L#
#.LLLLLL.L
#.#L#L#.##
At this point, something interesting happens: the chaos stabilizes and further applications of these rules cause no seats to change state! Once people stop moving around, you count 37 occupied seats.

Simulate your seating area by applying the seating rules repeatedly until no seats change state. How many seats end up occupied?

Your puzzle answer was 2418.

--- Part Two ---
As soon as people start to arrive, you realize your mistake. People don't just care about adjacent seats - they care about the first seat they can see in each of those eight directions!

Now, instead of considering just the eight immediately adjacent seats, consider the first seat in each of those eight directions. For example, the empty seat below would see eight occupied seats:

.......#.
...#.....
.#.......
.........
..#L....#
....#....
.........
#........
...#.....
The leftmost empty seat below would only see one empty seat, but cannot see any of the occupied ones:

.............
.L.L.#.#.#.#.
.............
The empty seat below would see no occupied seats:

.##.##.
#.#.#.#
##...##
...L...
##...##
#.#.#.#
.##.##.
Also, people seem to be more tolerant than you expected: it now takes five or more visible occupied seats for an occupied seat to become empty (rather than four or more from the previous rules). The other rules still apply: empty seats that see no occupied seats become occupied, seats matching no rule don't change, and floor never changes.

Given the same starting layout as above, these new rules cause the seating area to shift around as follows:

L.LL.LL.LL
LLLLLLL.LL
L.L.L..L..
LLLL.LL.LL
L.LL.LL.LL
L.LLLLL.LL
..L.L.....
LLLLLLLLLL
L.LLLLLL.L
L.LLLLL.LL
#.##.##.##
#######.##
#.#.#..#..
####.##.##
#.##.##.##
#.#####.##
..#.#.....
##########
#.######.#
#.#####.##
#.LL.LL.L#
#LLLLLL.LL
L.L.L..L..
LLLL.LL.LL
L.LL.LL.LL
L.LLLLL.LL
..L.L.....
LLLLLLLLL#
#.LLLLLL.L
#.LLLLL.L#
#.L#.##.L#
#L#####.LL
L.#.#..#..
##L#.##.##
#.##.#L.##
#.#####.#L
..#.#.....
LLL####LL#
#.L#####.L
#.L####.L#
#.L#.L#.L#
#LLLLLL.LL
L.L.L..#..
##LL.LL.L#
L.LL.LL.L#
#.LLLLL.LL
..L.L.....
LLLLLLLLL#
#.LLLLL#.L
#.L#LL#.L#
#.L#.L#.L#
#LLLLLL.LL
L.L.L..#..
##L#.#L.L#
L.L#.#L.L#
#.L####.LL
..#.#.....
LLL###LLL#
#.LLLLL#.L
#.L#LL#.L#
#.L#.L#.L#
#LLLLLL.LL
L.L.L..#..
##L#.#L.L#
L.L#.LL.L#
#.LLLL#.LL
..#.L.....
LLL###LLL#
#.LLLLL#.L
#.L#LL#.L#
Again, at this point, people stop shifting around and the seating area reaches equilibrium. Once this occurs, you count 26 occupied seats.

Given the new visibility method and the rule change for occupied seats becoming empty, once equilibrium is reached, how many seats end up occupied?

Your puzzle answer was 2144.
*/
#include "advent.h"

static char **arr;
static char **newArr;
static int cnt;
static int len;

static void freeAll() {
	for(int i = 0; i < cnt; i++){
		free(arr[i]);
		free(newArr[i]);
	}
	free(arr);
	free(newArr);
}

static int chkXY(int x, int y, int *sum) {
	*sum += arr[y][x];
	return !arr[y][x];
}

/*##########################
# Get input data from file #
##########################*/
static int getInput(char *f) {
	char * line = NULL;
	size_t l;
	arr = NULL;
	newArr = NULL;
	cnt = 0;

	FILE *file = fopen(f, "r");
	if(file == NULL) {
		printf("ERR: CAN NOT OPEN '%s'\n\n", f);
		return 0;
	}

	while( getline(&line, &l, file) != -1) {	
		len = strlen(line) ;	
		arr = realloc(arr, ++cnt * sizeof(char*));
		newArr = realloc(newArr, cnt * sizeof(char*));
		arr[cnt - 1] = malloc(len);
		newArr[cnt - 1] = malloc(len);
		for(int i = 0; i < strlen(line); i++)
			arr[cnt-1][i] = line[i] == '.' ? 0: 10;
		memcpy(newArr[cnt-1], arr[cnt-1], len);
	}

	free(line);
	fclose(file);
	return 1;
}

/*##########################
# Function to solve part A #
##########################*/
void get11a(char * f) {
	if(!getInput(f))
		return;
	
	int result = 0, change = 1, sum = 0, i, k, m;
		
	while(change != result){
		change = result;
		result = 0;
		for(i = 0, k = 0; i < cnt; k < len-1 ? k++ : (i++, k=0), sum = 0) {
			if(arr[i][k]) {
				for(m =  k ? k-1 : k; m <= (k < len-1 ? k+1 : k); m++){
					sum += i 		 ? arr[i-1][m] : 0;
					sum += m != k 	 ? arr[i][m]   : 0;
					sum += i < cnt-1 ? arr[i+1][m] : 0;
				}
				newArr[i][k] = (sum < 10) ? 10 : (sum >= 40) ? 1 : arr[i][k];
			}
			if(newArr[i][k] == 10)
				result++;
		}
		for(k = 0; k < cnt; k++) 
			memcpy(arr[k], newArr[k], len);
	}

	printf("11a: %d\n", result);
	freeAll();
}

/*##########################
# Function to solve part B #
##########################*/
void get11b(char *f) {
	if(!getInput(f))
		return;

	int result = 0, change = 1, sum = 0, x, y, i, k, m;

	while(change != result){
		change = result;
		result = 0;
		for(i = 0, k = 0; i < cnt; k < len-1 ? k++ : (i++, k=0), sum = 0) {
			if(arr[i][k]) {

				for(m = i+1; m < cnt && chkXY(k, m, &sum); m++);
				for(m = i-1; m >= 0  && chkXY(k, m, &sum); m--);
				for(m = k-1; m >= 0  && chkXY(m, i, &sum); m--);
				for(m = k+1; m < len && chkXY(m, i, &sum); m++);
				for(x = k-1, y = i-1; x >= 0  && y >= 0  && chkXY(x, y, &sum); x--, y--);
				for(x = k+1, y = i+1; x < len && y < cnt && chkXY(x, y, &sum); x++, y++);
				for(x = k+1, y = i-1; x < len && y >= 0  && chkXY(x, y, &sum); x++, y--);
				for(x = k-1, y = i+1; x >= 0  && y < cnt && chkXY(x, y, &sum); x--, y++);

				newArr[i][k] =(sum < 10) ? 10 : (sum >= 50) ? 1 : arr[i][k];
			}
			if(newArr[i][k] == 10)
				result++;
		}
		for(k = 0; k < cnt; k++) 
			memcpy(arr[k], newArr[k], len);	
	}

	printf("11b: %d\n\n", result);
	freeAll();
}