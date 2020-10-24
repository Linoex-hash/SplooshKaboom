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

void debugPrint(Point **squid, int length, char *squidName){
	puts(squidName);
	for(int i = 0; i < length; ++i){
		printf("squid[%d] -> x: %d\n", i ,squid[i] -> x);
		printf("squid[%d] -> y: %d\n", i ,squid[i] -> y);
	}
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
int printOutputOfGame(char **grid, int attemptsLeft){
	putchar('\n');
	//print the numbers 1 to F
	printf("        1     2     3     4     5     6     7     8     9    10    11    12    13    14    15             Shots: %d\n", attemptsLeft);
	puts("     |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|");
	for(int i = 0; i < GRIDSIZE; ++i){
		if(i + 1 < 10){
			printf("  %d  |", i + 1);
		}
		else{
			switch(i + 1){
				case 10: 
					printf("  10 |");
					break;
				case 11:
					printf("  11 |");
					break;
				case 12:
					printf("  12 |");
					break;
				case 13:
					printf("  13 |");
					break;
				case 14:
					printf("  14 |");
					break;
				case 15:
					printf("  15 |");
					break;
			}
		}
		for(int j = 0; j < GRIDSIZE; ++j){
			printf("  %c  |", grid[i][j]);
		}
		//print the number of spaces
		printf("          ");
		//print the number of shots
		for(int k = 0; k < attemptsLeft && k < 5; ++k){
			printf("X ");
		}
		//update the number of attempts to be -= 5
		attemptsLeft -= 5;
		putchar('\n');
		puts("     |-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|-----|");
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
	return printOutputOfGame(grid, 0);
}
//needs to be implemented
Point **generate4squid(){
	int x = rand() % GRIDSIZE;
	int y = rand() % GRIDSIZE;
	//malloc the squid
	Point **fourSquid = malloc(SQUIDFOUR * sizeof(Point *));
	for(int i = 0; i < SQUIDFOUR; ++i){
		//malloc the point
		fourSquid[i] = malloc(sizeof(Point));
	}
	fourSquid[0] -> x = x;
	fourSquid[0] -> y = y;
	//get direction and check if the direction is correct
	//There are 4 directions. UP DOWN LEFT RIGHT. Start with generating a random direction UP DOWN LEFT RIGHT
	int direction = rand() % 4 + 1;
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
			direction = RIGHT;
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
			direction = DOWN;
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
			direction = LEFT;
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
			direction = UP;
			goto U;
		}
	}
	//debugPrint(fourSquid, SQUIDFOUR, "FourSquid");
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
	for(int i = 0; i < SQUIDTHREE; ++i){
		threeSquid[i] = malloc(sizeof(Point));
	}

	threeSquid[0] -> x = x;
	threeSquid[0] -> y = y;

	int direction = rand() % 4 + 1;
	U: if(direction == UP){
		// in the case that y = 3, this is a valid starting point; index 2 1 and 0 would all be valid for the squid
		//needs to be at least 3 points from the top
		if(isvalidPoint(threeSquid[0] -> y - SQUIDTHREE + 1)){
			for(int i = 1; i < SQUIDTHREE; ++i){
				if(contains(fourSquid, SQUIDFOUR, x, y - i)){
					direction = RIGHT;
					goto R;
				}
				//y - 1, y - 2, y - 3
				else{
					threeSquid[i] -> x = threeSquid[0] -> x;
					threeSquid[i] -> y = threeSquid[0] -> y - i;
				}
			}
		}
		else{
			direction = RIGHT;
			goto R;
		}
		//printf("direction: %d\n", direction);
	}
	R: if(direction == RIGHT){
		//needs to be at least 3 points from the right
		if(isvalidPoint(threeSquid[0] -> x + SQUIDTHREE - 1)){
			for(int i = 1; i < SQUIDTHREE; ++i){
				if(contains(fourSquid, SQUIDFOUR, x + i, y)){
					direction = DOWN;
					goto D;
				}
				//x + 1, x + 2, x + 3
				else{
					threeSquid[i] -> x = threeSquid[0] -> x + i;
					threeSquid[i] -> y = threeSquid[0] -> y;				
				}

			}
		}
		else{
			direction = DOWN;
			goto D;
		}
		//printf("direction: %d\n", direction);
	}

	D: if(direction == DOWN){
		//needs to be at least 3 points from the bottom
		if(isvalidPoint(threeSquid[0] -> y + SQUIDTHREE - 1)){
			for(int i = 1; i < SQUIDTHREE; ++i){
				if(contains(fourSquid, SQUIDFOUR, x, y + i)){
					direction = LEFT;
					goto L;
				}
				//y + 1, y + 2, y + 3
				else{
					threeSquid[i] -> x = threeSquid[0] -> x;
					threeSquid[i] -> y = threeSquid[0] -> y + i;					
				}

			}
		}
		else{
			direction = LEFT;
			goto L;
		}
		//printf("direction: %d\n", direction);
	}

	L: if(direction == LEFT){
		//needs to be at least 3 points from the bottom
		if(isvalidPoint(threeSquid[0] -> x - SQUIDTHREE + 1)){
			for(int i = 1; i < SQUIDTHREE; ++i){
				if(contains(fourSquid, SQUIDFOUR, x - i, y)){
					direction = UP;
					goto U;
				}
				//x - 1, x - 2, x - 3
				else{
					threeSquid[i] -> x = threeSquid[0] -> x - i;
					threeSquid[i] -> y = threeSquid[0] -> y;
				}
			}
		}
		else{
			direction = UP;
			goto U;
		}
		//printf("direction: %d\n", direction);
	}

	//debugPrint(threeSquid, SQUIDTHREE, "ThreeSquid");
	return threeSquid;
}
//needs to be implemented
Point **generate2squid(Point **fourSquid, Point **threeSquid){
	int x = rand() % GRIDSIZE;
	int y = rand() % GRIDSIZE;
	//x and y is a corner and forSquid and 3 Squid contain points 
	int top_left_invalid = (x == 0 && y == 0 && (contains(fourSquid, SQUIDFOUR, x + 1, y) || contains(threeSquid, SQUIDTHREE, x + 1, y)) && (contains(fourSquid, SQUIDFOUR, x, y + 1) || contains(threeSquid, SQUIDTHREE, x, y  + 1)));
	int bottom_left_invalid = (x == 0 && y == GRIDSIZE - 1 && (contains(fourSquid, SQUIDFOUR, x + 1, y) || contains(threeSquid, SQUIDTHREE, x + 1, y)) && (contains(fourSquid, SQUIDFOUR, x, y - 1) || contains(threeSquid, SQUIDTHREE, x, y - 1)));
	int top_right_invalid = (x == GRIDSIZE - 1 && y == 0 && (contains(fourSquid, SQUIDFOUR, x - 1, y) || contains(threeSquid, SQUIDTHREE, x - 1, y)) && (contains(fourSquid, SQUIDFOUR, x, y + 1) || contains(threeSquid, SQUIDTHREE, x, y + 1)));
	int bottom_right_invalid = (x == GRIDSIZE - 1 && y == GRIDSIZE - 1 && (contains(fourSquid, SQUIDFOUR, x - 1, y) || contains(threeSquid, SQUIDTHREE, x - 1, y)) && (contains(fourSquid, SQUIDFOUR, x, y - 1) || contains(threeSquid, SQUIDTHREE, x, y - 1)));
	while(contains(fourSquid,SQUIDFOUR,x,y) || contains(threeSquid,SQUIDTHREE,x,y) || top_right_invalid || top_left_invalid || bottom_right_invalid || bottom_left_invalid){
		x = rand() % GRIDSIZE;
		y = rand() % GRIDSIZE;
		top_left_invalid = (x == 0 && y == 0 && (contains(fourSquid, SQUIDFOUR, x + 1, y) || contains(threeSquid, SQUIDTHREE, x + 1, y)) && (contains(fourSquid, SQUIDFOUR, x, y + 1) || contains(threeSquid, SQUIDTHREE, x, y  + 1)));
		bottom_left_invalid = (x == 0 && y == GRIDSIZE - 1 && (contains(fourSquid, SQUIDFOUR, x + 1, y) || contains(threeSquid, SQUIDTHREE, x + 1, y)) && (contains(fourSquid, SQUIDFOUR, x, y - 1) || contains(threeSquid, SQUIDTHREE, x, y - 1)));
		top_right_invalid = (x == GRIDSIZE - 1 && y == 0 && (contains(fourSquid, SQUIDFOUR, x - 1, y) || contains(threeSquid, SQUIDTHREE, x - 1, y)) && (contains(fourSquid, SQUIDFOUR, x, y + 1) || contains(threeSquid, SQUIDTHREE, x, y + 1)));
		bottom_right_invalid = (x == GRIDSIZE - 1 && y == GRIDSIZE - 1 && (contains(fourSquid, SQUIDFOUR, x - 1, y) || contains(threeSquid, SQUIDTHREE, x - 1, y)) && (contains(fourSquid, SQUIDFOUR, x, y - 1) || contains(threeSquid, SQUIDTHREE, x, y - 1)));
	}




	//get direction from rand and check validity. Use goto statements and labels to save on syntax.
	Point **twoSquid = malloc(SQUIDTWO * sizeof(Point *));

	for(int i = 0; i < SQUIDTWO; ++i){
		twoSquid[i] = malloc(sizeof(Point));
	}
	twoSquid[0] -> x = x;
	twoSquid[0] -> y = y;

	int direction = rand() % 4 + 1;
	U: if(direction == UP){
		// in the case that y = 3, this is a valid starting point; index 2 1 and 0 would all be valid for the squid
		//needs to be at least 3 points from the top
		if(isvalidPoint(twoSquid[0] -> y - SQUIDTWO + 1)){
			for(int i = 1; i < SQUIDTWO; ++i){
				if(contains(fourSquid, SQUIDFOUR, x, y - i) || contains(threeSquid, SQUIDTHREE, x, y - i)){
					direction = RIGHT;
					goto R;
				}
				//y - 1, y - 2, y - 3
				else{
					twoSquid[i] -> x = twoSquid[0] -> x;
					twoSquid[i] -> y = twoSquid[0] -> y - i;				
				}

			}
		}
		else{
			direction = RIGHT;
			goto R;
		}
		//printf("direction: %d\n", direction);
	}
	R: if(direction == RIGHT){
		//needs to be at least 3 points from the right
		if(isvalidPoint(twoSquid[0] -> x + SQUIDTWO - 1)){
			for(int i = 1; i < SQUIDTWO; ++i){
				if(contains(fourSquid, SQUIDFOUR, x + i, y) || contains(threeSquid, SQUIDTHREE, x + i, y)){
					direction = DOWN;
					goto D;
				}
				//x + 1, x + 2, x + 3
				else{
					twoSquid[i] -> x = twoSquid[0] -> x + i;
					twoSquid[i] -> y = twoSquid[0] -> y;
				}
			}
		}
		else{
			direction = DOWN;
			goto D;
		}
		//printf("direction: %d\n", direction);
	}

	D: if(direction == DOWN){
		//needs to be at least 3 points from the bottom
		if(isvalidPoint(twoSquid[0] -> y + SQUIDTWO - 1)){
			for(int i = 1; i < SQUIDTWO; ++i){
				if(contains(fourSquid, SQUIDFOUR, x, y + i) || contains(threeSquid, SQUIDTHREE, x, y + i)){
					direction = LEFT;
					goto L;
				}
				//y + 1, y + 2, y + 3
				else{
					twoSquid[i] -> x = twoSquid[0] -> x;
					twoSquid[i] -> y = twoSquid[0] -> y + i;
				}
			}
		}
		else{
			direction = LEFT;
			goto L;
		}
		//printf("direction: %d\n", direction);
	}

	L: if(direction == LEFT){
		//needs to be at least 3 points from the bottom
		if(isvalidPoint(twoSquid[0] -> x - SQUIDTWO + 1)){
			for(int i = 1; i < SQUIDTWO; ++i){
				if(contains(fourSquid, SQUIDFOUR, x - i, y) || contains(threeSquid, SQUIDTHREE, x - i, y)){
					direction = UP;
					goto U;
				}
				//x - 1, x - 2, x - 3
				else{
					twoSquid[i] -> x = twoSquid[0] -> x - i;
					twoSquid[i] -> y = twoSquid[0] -> y;

				}
			}
		}
		else{
			direction = UP;
			goto U;
		}
		//printf("direction: %d\n", direction);
	}
	//debugPrint(twoSquid, SQUIDTWO, "TwoSquid");
	return twoSquid;	
}

