#include <stdlib.h>
#include <stdio.h>
#include "splooshkaboom.h"
#include <math.h>

/* takes a coordinate and returns whether that point is valid or not*/
int isvalidPoint(int x){
	return x >= 0 && x < GRIDSIZE;
}

/* takes an x and y coordinate and determines whether a Point contains that point */
int contains(Point **squid, int length, int x, int y){
	// loop through the Points and try to see if each point contains x and y. Returns 1 on one match
	for(int i = 0; i < length; ++i){
		if(squid[i] -> x == x && squid[i] -> y == y){
			return 1;
		}
	}
	return 0;
}

char **gengrid(){
	//malloc the rows
	char **grid = malloc(GRIDSIZE * sizeof(char *));
	for(int i = 0; i < GRIDSIZE; ++i){
		//for every row, malloc the collumns and initialize this with all spaces
		grid[i] = malloc(GRIDSIZE * sizeof(char));
		for(int j = 0; j < GRIDSIZE; ++j){
			grid[i][j] = ' ';
		}
	}
	return grid;
}

/* header functions. Functionality described in header file sploohskaboom.h. Any provided implementaiton may be wrong */

//already implemented
int printOutputOfGame(char **grid){
	putchar('\n');
	//print the numbers 1 to F
	puts("       1     2     3     4     5     6     7     8     9     A     B     C     D     E     F");
	puts("    |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|");
	for(int i = 0; i < GRIDSIZE; ++i){
		if(i + 1 < 10){
			printf("  %d |", i + 1);
		}
		else{
			switch(i + 1){
				case 10: 
					printf("  A |");
					break;
				case 11:
					printf("  B |");
					break;
				case 12:
					printf("  C |");
					break;
				case 13:
					printf("  D |");
					break;
				case 14:
					printf("  E |");
					break;
				case 15:
					printf("  F |");
					break;
			}
		}
		for(int j = 0; j < GRIDSIZE; ++j){
			printf("  %c  |", grid[i][j]);
		}
		putchar('\n');
		puts("    |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|");
	}
	putchar('\n');
	return 1;
}

//already impelmented
int splooshKaboom(char **grid, Point **squidfour, Point **squidthree, Point **squidtwo, int x, int y){
	if(grid[y][x] != ' '){
		//we already hit this spot
		printf("Spot already hit!\n");
		return 0;
	}
	else if(contains(squidfour,SQUIDFOUR,x,y) || contains(squidthree,SQUIDTHREE,x,y) || contains(squidtwo,SQUIDTWO,x,y)){
		grid[y][x] = KABOOM;
		return KABOOM;
	}
	else {
		grid[y][x] = SPLOOSH;
		return SPLOOSH;
	}
}

//already implemented
int printAnswerOfGame(char **grid, Point **fourSquid, Point **threeSquid, Point **twoSquid){
	for(int i = 0; i < SQUIDFOUR; ++i){
		//might change this to a special answer character
		grid[fourSquid[i] -> y][fourSquid[i] -> x] = KABOOM;
	}
	for(int i = 0; i < SQUIDTHREE; ++i){
		//might change this to a special answer character
		grid[threeSquid[i] -> y][threeSquid[i] -> x] = KABOOM;
	}
	for(int i = 0; i < SQUIDTWO; ++i){
		//might change this to a special answer character
		grid[twoSquid[i] -> y][twoSquid[i] -> x] = KABOOM;
	}
	return printOutputOfGame(grid);
}
//needs to be implemented
Point **generate4squid(){
	int x = rand() % GRIDSIZE;
	int y = rand() % GRIDSIZE;
	Point **fourSquid = malloc(SQUIDFOUR * sizeof(Point *));

	fourSquid[0] -> x = x;
	fourSquid[0] -> y = y;
	//get direction and check if the direction is correct
	//There are 4 directions. UP DOWN LEFT RIGHT. Start with generating a random direction UP DOWN LEFT RIGHT
	int direction = rand() % 4;
	U: if(direction == UP){
		// in the case that y = 3, this is a valid starting point; index 2 1 and 0 would all be valid for the squid
		//needs to be at least 3 points from the top
		if(isvalidPoint(fourSquid[0] -> y - SQUIDFOUR + 1)){
			for(int i = 1; i < SQUIDFOUR; ++i){
				//y - 1, y - 2, y - 3
				fourSquid[i] -> x = fourSquid[0] -> x;
				fourSquid[i] -> y = fourSquid[0] -> y - i;
			}
		}
		else{
			directon = RIGHT;
			goto R;
		}
	}
	R: if(direction == RIGHT){
		//needs to be at least 3 points from the right
		if(isvalidPoint(fourSquid[0] -> x + SQUIDFOUR - 1)){
			for(int i = 1; i < SQUIDFOUR; ++i){
				//x + 1, x + 2, x + 3
				fourSquid[i] -> x = fourSquid[0] -> x + i;
				fourSquid[i] -> y = fourSquid[0] -> y;
			}
		}
		else{
			directon = DOWN;
			goto D;
		}
	}

	D: if(direction == DOWN){
		//needs to be at least 3 points from the bottom
		if(isvalidPoint(fourSquid[0] -> y + SQUIDFOUR - 1)){
			for(int i = 1; i < SQUIDFOUR; ++i){
				//y + 1, y + 2, y + 3
				fourSquid[i] -> x = fourSquid[0] -> x;
				fourSquid[i] -> y = fourSquid[0] -> y + i;
			}
		}
		else{
			directon = LEFT;
			goto L;
		}
	}

	L: if(direction == LEFT){
		//needs to be at least 3 points from the bottom
		if(isvalidPoint(fourSquid[0] -> x - SQUIDFOUR + 1)){
			for(int i = 1; i < SQUIDFOUR; ++i){
				//x - 1, x - 2, x - 3
				fourSquid[i] -> x = fourSquid[0] -> x - i;
				fourSquid[i] -> y = fourSquid[0] -> y;
			}
		}
		else{
			directon = UP;
			goto U;
		}
	}
	return fourSquid;
}
//needs to be implemented
Point **generate3squid(Point **fourSquid){
	int x = rand() % GRIDSIZE;
	int y = rand() % GRIDSIZE;
	while(contains(fourSquid,SQUIDFOUR,x,y)){
		x = rand() % GRIDSIZE;
		y = rand() % GRIDSIZE;		
	}
	//get direction from rand and check validity.
	Point **threeSquid = malloc(SQUIDTHREE * sizeof(Point *));
	threeSquid[0] -> x = x;
	threeSquid[0] -> y = y;

	return threeSquid;
}
//needs to be implemented
Point **generate2squid(Point **fourSquid, Point **threeSquid){
	int x = rand() % GRIDSIZE;
	int y = rand() % GRIDSIZE;
	while(contains(fourSquid,SQUIDFOUR,x,y) || contains(threeSquid,SQUIDTHREE,x,y)){
		x = rand() % GRIDSIZE;
		y = rand() % GRIDSIZE;		
	}
	//get direction from rand and check validity. Use goto statements and labels to save on syntax.
	Point **twoSquid = malloc(SQUIDTWO * sizeof(Point *));
	twoSquid[0] -> x = x;
	twoSquid[0] -> y = y;
	return twoSquid;	
}

