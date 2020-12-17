/*
--- Day 17: Conway Cubes ---
As your flight slowly drifts through the sky, the Elves at the Mythical Information Bureau at the North Pole contact you. They'd like some help debugging a malfunctioning experimental energy source aboard one of their super-secret imaging satellites.

The experimental energy source is based on cutting-edge technology: a set of Conway Cubes contained in a pocket dimension! When you hear it's having problems, you can't help but agree to take a look.

The pocket dimension contains an infinite 3-dimensional grid. At every integer 3-dimensional coordinate (x,y,z), there exists a single cube which is either active or inactive.

In the initial state of the pocket dimension, almost all cubes start inactive. The only exception to this is a small flat region of cubes (your puzzle input); the cubes in this region start in the specified active (#) or inactive (.) state.

The energy source then proceeds to boot up by executing six cycles.

Each cube only ever considers its neighbors: any of the 26 other cubes where any of their coordinates differ by at most 1. For example, given the cube at x=1,y=2,z=3, its neighbors include the cube at x=2,y=2,z=2, the cube at x=0,y=2,z=3, and so on.

During a cycle, all cubes simultaneously change their state according to the following rules:

If a cube is active and exactly 2 or 3 of its neighbors are also active, the cube remains active. Otherwise, the cube becomes inactive.
If a cube is inactive but exactly 3 of its neighbors are active, the cube becomes active. Otherwise, the cube remains inactive.
The engineers responsible for this experimental energy source would like you to simulate the pocket dimension and determine what the configuration of cubes should be at the end of the six-cycle boot process.

For example, consider the following initial state:

.#.
..#
###
Even though the pocket dimension is 3-dimensional, this initial state represents a small 2-dimensional slice of it. (In particular, this initial state defines a 3x3x1 region of the 3-dimensional space.)

Simulating a few cycles from this initial state produces the following configurations, where the result of each cycle is shown layer-by-layer at each given z coordinate (and the frame of view follows the active cells in each cycle):

Before any cycles:

z=0
.#.
..#
###


After 1 cycle:

z=-1
#..
..#
.#.

z=0
#.#
.##
.#.

z=1
#..
..#
.#.


After 2 cycles:

z=-2
.....
.....
..#..
.....
.....

z=-1
..#..
.#..#
....#
.#...
.....

z=0
##...
##...
#....
....#
.###.

z=1
..#..
.#..#
....#
.#...
.....

z=2
.....
.....
..#..
.....
.....


After 3 cycles:

z=-2
.......
.......
..##...
..###..
.......
.......
.......

z=-1
..#....
...#...
#......
.....##
.#...#.
..#.#..
...#...

z=0
...#...
.......
#......
.......
.....##
.##.#..
...#...

z=1
..#....
...#...
#......
.....##
.#...#.
..#.#..
...#...

z=2
.......
.......
..##...
..###..
.......
.......
.......
After the full six-cycle boot process completes, 112 cubes are left in the active state.

Starting with your given initial configuration, simulate six cycles. How many cubes are left in the active state after the sixth cycle?

Your puzzle answer was 426.

--- Part Two ---
For some reason, your simulated results don't match what the experimental energy source engineers expected. Apparently, the pocket dimension actually has four spatial dimensions, not three.

The pocket dimension contains an infinite 4-dimensional grid. At every integer 4-dimensional coordinate (x,y,z,w), there exists a single cube (really, a hypercube) which is still either active or inactive.

Each cube only ever considers its neighbors: any of the 80 other cubes where any of their coordinates differ by at most 1. For example, given the cube at x=1,y=2,z=3,w=4, its neighbors include the cube at x=2,y=2,z=3,w=3, the cube at x=0,y=2,z=3,w=4, and so on.

The initial state of the pocket dimension still consists of a small flat region of cubes. Furthermore, the same rules for cycle updating still apply: during each cycle, consider the number of active neighbors of each cube.

For example, consider the same initial state as in the example above. Even though the pocket dimension is 4-dimensional, this initial state represents a small 2-dimensional slice of it. (In particular, this initial state defines a 3x3x1x1 region of the 4-dimensional space.)

Simulating a few cycles from this initial state produces the following configurations, where the result of each cycle is shown layer-by-layer at each given z and w coordinate:

Before any cycles:

z=0, w=0
.#.
..#
###


After 1 cycle:

z=-1, w=-1
#..
..#
.#.

z=0, w=-1
#..
..#
.#.

z=1, w=-1
#..
..#
.#.

z=-1, w=0
#..
..#
.#.

z=0, w=0
#.#
.##
.#.

z=1, w=0
#..
..#
.#.

z=-1, w=1
#..
..#
.#.

z=0, w=1
#..
..#
.#.

z=1, w=1
#..
..#
.#.


After 2 cycles:

z=-2, w=-2
.....
.....
..#..
.....
.....

z=-1, w=-2
.....
.....
.....
.....
.....

z=0, w=-2
###..
##.##
#...#
.#..#
.###.

z=1, w=-2
.....
.....
.....
.....
.....

z=2, w=-2
.....
.....
..#..
.....
.....

z=-2, w=-1
.....
.....
.....
.....
.....

z=-1, w=-1
.....
.....
.....
.....
.....

z=0, w=-1
.....
.....
.....
.....
.....

z=1, w=-1
.....
.....
.....
.....
.....

z=2, w=-1
.....
.....
.....
.....
.....

z=-2, w=0
###..
##.##
#...#
.#..#
.###.

z=-1, w=0
.....
.....
.....
.....
.....

z=0, w=0
.....
.....
.....
.....
.....

z=1, w=0
.....
.....
.....
.....
.....

z=2, w=0
###..
##.##
#...#
.#..#
.###.

z=-2, w=1
.....
.....
.....
.....
.....

z=-1, w=1
.....
.....
.....
.....
.....

z=0, w=1
.....
.....
.....
.....
.....

z=1, w=1
.....
.....
.....
.....
.....

z=2, w=1
.....
.....
.....
.....
.....

z=-2, w=2
.....
.....
..#..
.....
.....

z=-1, w=2
.....
.....
.....
.....
.....

z=0, w=2
###..
##.##
#...#
.#..#
.###.

z=1, w=2
.....
.....
.....
.....
.....

z=2, w=2
.....
.....
..#..
.....
.....
After the full six-cycle boot process completes, 848 cubes are left in the active state.

Starting with your given initial configuration, simulate six cycles in a 4-dimensional space. How many cubes are left in the active state after the sixth cycle?

Your puzzle answer was 1892.
*/
#include "advent.h"
#define DIMX 23
#define DIMY 23
#define DIMZ 15
#define DIMK 15

static char arr[DIMK][DIMX][DIMY][DIMZ] = {};
static char arrCpy[DIMK][DIMX][DIMY][DIMZ] = {};
static int cnt;

/*##########################
# Get input data from file #
##########################*/
static int getInput(char *f) {
	char * line = NULL;
	size_t l;
	cnt = 0;
	int x = DIMX / 2 + 1;
	int y = DIMY / 2 + 1;
	int z = DIMZ / 2 + 1;
	int k = DIMK / 2 + 1;

	for(int kk = 0; kk < DIMK; kk++)
		for(int zz = 0; zz < DIMZ; zz++)
			for(int yy = 0; yy < DIMY; yy++)
				for(int xx = 0; xx < DIMX; xx++) {
					arr[kk][xx][yy][zz] = 0;
					arrCpy[kk][xx][yy][zz] = 0;
				}

	FILE *file = fopen(f, "r");
	if(file == NULL) {
		printf("ERR: CAN NOT OPEN '%s'\n\n", f);
		return 0;
	}

	while( getline(&line, &l, file) != -1) {
		line = trim(line);
		for(int i = 0; i < strlen(line) ; i++)
			arr[k][x-strlen(line)/2+i][y-strlen(line)/2+cnt][z] = line[i] == '.' ? 0 : 1;
		cnt++;
	}

	free(line);
	fclose(file);
	return 1;
}

/*##########################
# Function to solve part A #
##########################*/
void get17a(char * f) {
	if(!getInput(f))
		return;
	
	int resultA = 0;
	int x = DIMX / 2 - cnt/2;
	int y = DIMY / 2 - cnt/2;
	int z = DIMZ / 2;
	int k = DIMK / 2 + 1;
	int cntZ = 3;
	int cntXY = cnt + 2;
	for(int i = 0; i < 6; i++){
		for(int zz = z; zz < z+cntZ; zz++)
			for(int yy = y; yy < y+cntXY; yy++)
				for(int xx = x; xx < x+cntXY; xx++){
					int cntA = 0;
					for(int a=xx-1,b=yy-1,c=zz-1; c <= zz+1; (a < xx+1)? a++ : (b < yy+1) ? (b++, a = xx-1) : (b = yy-1, a = xx-1, c++) )
						if(arr[k][a][b][c] && (a!=xx || b!=yy || c!=zz)) cntA++;


					if(arr[k][xx][yy][zz] && (cntA > 3 || cntA < 2))
						arrCpy[k][xx][yy][zz] = 0;
					else if (!arr[k][xx][yy][zz] && cntA == 3)
						arrCpy[k][xx][yy][zz] = 1;
					else
						arrCpy[k][xx][yy][zz] = arr[k][xx][yy][zz];

				}

		for(int zz = 0; zz < DIMZ; zz++)
			for(int yy = 0; yy < DIMY; yy++)
				for(int xx = 0; xx < DIMX; xx++)
					arr[k][xx][yy][zz] = arrCpy[k][xx][yy][zz];
	
		cntXY += 2;
		cntZ += 2;
		x--;
		y--;
		z--;
	}

	for(int zz = 0; zz < DIMZ; zz++)
		for(int yy = 0; yy < DIMY; yy++)
			for(int xx = 0; xx < DIMX; xx++)
				if(arr[k][xx][yy][zz]) resultA++;;

	printf("17a: %d\n", resultA);
	assert(resultA == 426);
}

/*##########################
# Function to solve part B #
##########################*/
void get17b(char *f) {
	if(!getInput(f))
		return;

	int resultB = 0;
	int x = DIMX / 2 - cnt/2;
	int y = DIMY / 2 - cnt/2;
	int z = DIMZ / 2;
	int k = DIMK / 2;
	int cntKZ = 3;
	int cntXY = cnt + 2;

	for(int i = 0; i < 6; i++){
		for(int kk = k; kk < k+cntKZ; kk++){
			for(int zz = z; zz < z+cntKZ; zz++){
				for(int yy = y; yy < y+cntXY; yy++){
					for(int xx = x; xx < x+cntXY; xx++){
						int cntA = 0;

						for(int a=xx-1,b=yy-1,c=zz-1; c <= zz+1; (a < xx+1)? a++ : (b < yy+1) ? (b++, a = xx-1) : (b = yy-1, a = xx-1, c++) )
							for(int d = kk-1; d <= kk+1; d++)
								if(arr[d][a][b][c] && (a!=xx || b!=yy || c!=zz || d!=kk)) cntA++;

						if(arr[kk][xx][yy][zz] && (cntA > 3 || cntA < 2))
							arrCpy[kk][xx][yy][zz] = 0;
						else if (!arr[kk][xx][yy][zz] && cntA == 3)
							arrCpy[kk][xx][yy][zz] = 1;
						else
							arrCpy[kk][xx][yy][zz] = arr[kk][xx][yy][zz];

					}
				}
			}
		}

		for(int kk = 0; kk < DIMK; kk++)
			for(int zz = 0; zz < DIMZ; zz++)
				for(int yy = 0; yy < DIMY; yy++)
					for(int xx = 0; xx < DIMX; xx++)
						arr[kk][xx][yy][zz] = arrCpy[kk][xx][yy][zz];
	
		cntXY += 2;
		cntKZ += 2;
		x--;
		y--;
		z--;
		k--;
	}
	for(int kk = k; kk < DIMK; kk++)
		for(int zz = 0; zz < DIMZ; zz++)
			for(int yy = 0; yy < DIMY; yy++)
				for(int xx = 0; xx < DIMX; xx++)
					if(arr[kk][xx][yy][zz]) resultB++;;

	printf("17b: %d\n\n", resultB);
	assert(resultB == 1892);
}
