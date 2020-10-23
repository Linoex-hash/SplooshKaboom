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
	char **grid = malloc(GRIDSIZE * sizeof(char));
	for(int i = 0; i < GRIDSIZE; ++i){
		//for every row, malloc the collumns and initialize this with all spaces
		grid[i] = malloc(GRIDSIZE * sizeof(char))
		for(int j = 0; j < GRIDSIZE; ++j){
			grid[i][j] = ' ';
		}
	}
	return grid;
}

/* header functions. Functionality described in header file sploohskaboom.h. Any provided implementaiton may be wrong */

//already implemented
int printOutputOfGame(char **grid){
	//print the numbers 1 to F
	puts("     1     2     3     4     5     6     7     8     9     A     B     C     D     E     F");
	puts("  |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|");
	for(int i = 0; i < GRIDSIZE; ++i){
		printf("%d |", i + 1);
		for(int j = 0; j < GRIDSIZE; ++j){
			printf("  %c  |", grid[i][j]);
		}
		putchar('\n');
		puts("  |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|");
	}
	return 1;
}

//already impelmented
int splooshKaboom(char **grid, Point **squidfour, Point**squidthree, Point*squidtwo, int x, int y){
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
	//get direction and check if the direction is correct
	Point **fourSquid = malloc(SQUIDFOUR * sizeof(Point));
	fourSquid[0] -> x = x;
	fourSquid[0] -> y = y;
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
	Point **threeSquid = malloc(SQUIDTHREE * sizeof(Point));
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
	Point **twoSquid = malloc(SQUIDTWO * sizeof(Point));
	twoSquid[0] -> x = x;
	twoSquid[0] -> y = y;
	return twoSquid;	
}

