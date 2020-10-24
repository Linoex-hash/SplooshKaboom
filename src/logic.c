#include <stdlib.h>
#include <stdio.h>
#include "splooshkaboom.h"
#include <math.h>
#include <time.h>

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
	//get direction and check if the direction is correct
	Point **fourSquid = malloc(SQUIDFOUR * sizeof(Point *));
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
        int direction = rand() % RIGHT;
        //if the first direction doesn't work, pick another direction clockwise
        int coordinatesCreated = 1;
        int sidesTried = 0;
        int xCoordinates[SQUIDTHREE];
        int yCoordinates[SQUIDTHREE];
        while (coordinatesCreated < 3) {
            if(sidesTried == 4) {
                //randomize coordinate and direction again
            }
            else {
                if (direction == UP) {
                    //if squid goes up, only the y coordinates would change by -1
                    int y2 = y - 1;
                    int y3 = y2 - 1;
                    if (contains(fourSquid,SQUIDFOUR,x,y2) == 0 && contains(fourSquid,SQUIDFOUR, x, y3) == 0 && (isvalidPoint(y2)) + (isvalidPoint(y3)) == 2) {
                        //if both contains return false, these coordinates are valid
                        coordinatesCreated += 2;
                        xCoordinates[0] = x;
                        xCoordinates[1] = x;
                        xCoordinates[2] = x;
                        yCoordinates[0] = y;
                        yCoordinates[1] = y2;
                        yCoordinates[2] = y3;
                    }
                    else {
                        direction = RIGHT;
                        sidesTried +=1;
                    }
                }
                else if (direction == RIGHT) {
                    //if squid goes right, only the x coordinates change by +1
                    int x2 = x + 1;
                    int x3 = x2 + 1;
                    if (contains(fourSquid,SQUIDFOUR,x2,y) == 0 && contains(fourSquid,SQUIDFOUR, x3, y) == 0 && (isvalidPoint(x2)) + (isvalidPoint(x3)) == 2) {
                        //if both contains return false, these coordinates are valid
                        coordinatesCreated += 2;
                        xCoordinates[0] = x;
                        xCoordinates[1] = x2;
                        xCoordinates[2] = x3;
                        yCoordinates[0] = y;
                        yCoordinates[1] = y;
                        yCoordinates[2] = y;
                    }
                    else {
                        direction = DOWN;
                        sidesTried += 1;
                    }
                }
                else if (direction == DOWN) {
                    //if squid goes down, only the y coordinates change by + 1
                    int y2 = y + 1;
                    int y3 = y2 + 1;
                    if (contains(fourSquid,SQUIDFOUR,x,y2) == 0 && contains(fourSquid,SQUIDFOUR, x, y3) == 0 &&(isvalidPoint(y2)) + (isvalidPoint(y3)) == 2) {
                        //if both contains return false, these coordinates are valid
                        coordinatesCreated += 2;
                        xCoordinates[0] = x;
                        xCoordinates[1] = x;
                        xCoordinates[2] = x;
                        yCoordinates[0] = y;
                        yCoordinates[1] = y2;
                        yCoordinates[2] = y3;
                    }
                    else {
                        direction = LEFT;
                        sidesTried += 1;
                    }
                }
                else {
                    //if squid goes left, the x coordinate changes by -1
                    int x2 = x - 1;
                    int x3 = x2 - 1;
                    if (contains(fourSquid,SQUIDFOUR,x2,y) == 0 && contains(fourSquid,SQUIDFOUR, x3, y) == 0 && (isvalidPoint(x2)) + (isvalidPoint(x3)) == 2) {
                        coordinatesCreated += 2;
                        xCoordinates[0] = x;
                        xCoordinates[1] = x2;
                        xCoordinates[2] = x3;
                        yCoordinates[0] = y;
                        yCoordinates[1] = y;
                        yCoordinates[2] = y;
                    }
                    else {
                        direction = UP;
                        sidesTried += 1;
                    }
                }
            }
        }
        Point **threeSquid = malloc(SQUIDTHREE * sizeof(Point *));
        for (int index = 0; index < SQUIDTHREE; index++) {
            threeSquid[index] = malloc(sizeof(Point));
            threeSquid[index] -> x = xCoordinates[index];
            threeSquid[index] -> y = yCoordinates[index];
        }
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
        //get direction from rand and check validity.
        int direction = rand() % RIGHT;
        //if the first direction doesn't work, pick another direction clockwise
        int coordinatesCreated = 1;
        int sidesTried = 0;
        int xCoordinates[SQUIDTWO];
        int yCoordinates[SQUIDTWO];
        while (coordinatesCreated < 2) {
            if(sidesTried == 4) {
                //randomize coordinate and direction again
            }
            else {
                if (direction == UP) {
                    //if squid goes up, only the y coordinates would change by -1
                    int y2 = y - 1;
                    if (contains(fourSquid,SQUIDFOUR,x,y2) == 0 && contains(threeSquid,SQUIDTHREE, x, y2) == 0 && isvalidPoint(y2) == 1) {
                        //if both contains return false, these coordinates are valid
                        coordinatesCreated += 1;
                        xCoordinates[0] = x;
                        xCoordinates[1] = x;
                        xCoordinates[2] = x;
                        yCoordinates[0] = y;
                        yCoordinates[1] = y2;
                        yCoordinates[2] = y3;
                    }
                    else {
                        direction = RIGHT;
                        sidesTried +=1;
                    }
                }
                else if (direction == RIGHT) {
                    //if squid goes right, only the x coordinates change by +1
                    int x2 = x + 1;
                    if (contains(fourSquid,SQUIDFOUR,x2,y) == 0 && contains(threeSquid,SQUIDTHREE, x2, y) == 0 && isvalidPoint(x2) == 1) {
                        //if both contains return false, these coordinates are valid
                        coordinatesCreated += 1;
                        xCoordinates[0] = x;
                        xCoordinates[1] = x2;
                        xCoordinates[2] = x3;
                        yCoordinates[0] = y;
                        yCoordinates[1] = y;
                        yCoordinates[2] = y;
                    }
                    else {
                        direction = DOWN;
                        sidesTried += 1;
                    }
                }
                else if (direction == DOWN) {
                    //if squid goes down, only the y coordinates change by + 1
                    int y2 = y + 1;
                    if (contains(fourSquid,SQUIDFOUR,x,y2) == 0 && contains(threeSquid,SQUIDTHREE,x,y2)== 0 && isvalidPoint(y2) == 1) {
                        //if both contains return false, these coordinates are valid
                        coordinatesCreated += 1;
                        xCoordinates[0] = x;
                        xCoordinates[1] = x;
                        yCoordinates[0] = y;
                        yCoordinates[1] = y2;
                    }
                    else {
                        direction = LEFT;
                        sidesTried += 1;
                    }
                }
                else {
                    //if squid goes left, the x coordinate changes by -1
                    int x2 = x - 1;
                    if (contains(fourSquid,SQUIDFOUR,x2,y) == 0 && contains(threeSquid,SQUIDTHREE,x2,y) == 0 && isvalidPoint(x2) == 1) {
                        coordinatesCreated += 1;
                        xCoordinates[0] = x;
                        xCoordinates[1] = x2;
                        yCoordinates[0] = y;
                        yCoordinates[1] = y;
                    }
                    else {
                        direction = UP;
                        sidesTried += 1;
                    }
                }
            }
        }
	Point **twoSquid = malloc(SQUIDTWO * sizeof(Point *));
        for (int index = 0; index < SQUIDTWO; index++) {
            threeSquid[index] = malloc(sizeof(Point));
            threeSquid[index] -> x = xCoordinates[index];
            threeSquid[index] -> y = yCoordinates[index];
        }
	return twoSquid;
}
