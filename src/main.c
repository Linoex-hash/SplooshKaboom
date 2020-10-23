#include <stdio.h>
#include <stdlib.h>
#include "splooshkaboom.h"


int main(int argc, char const *argv[])
{
	printf("Welcome to sploosh kaboom.\nThis game is based off of Legend of Zelda: The Wind Waker.\nThe rules are to shoot 
		at the grid until all the squids are found. Enjoy!\n");

	char **grid = gengrid();
	const Point **fourSquid = generate4squid();
	const Point **threeSquid = generate3squid();
	const Point **twoSquid = generate2Squid();
	//this is going to either equal sploosh or kaboom.
	int instanceOutput = 0;
	int currentX = 0;
	int currentY = 0;
	int hits = 0;

	for(int i = 0;; i < ATTEMPTS && hits < SQUIDFOUR + SQUIDTHREE + SQUIDTWO; ++i){
		printOutputOfGame(grid);
		if(i <= 0){
			printf("chosen x: not chosen yet");
			printf("chosen y: not chosen yet");
		}
		else{
			printf("chosen x: %d\n", currentX);
			printf("chosen y: %d\n", currentY);
		}
		switch (instanceOutput){
			case KABOOM: 
				printf("KABOOM!\n");
				break;
			case SPLOOSH:
				printf("SPLOOSH\n");
				break;
			default: //don't do anything
		}
		printf("Please enter x coordinate or press q to quit: ");
		//while this input isn't a valid number. If q is entered, return 0 and stop the game
		printf("Please enter y coordinate or press q to quit: ");
		//while this input isn't a valid number. If q is entered, return 0 and stop the game
		while((instanceOutput = splooshKaboom(grid, fourSquid, threeSquid, twoSquid, currentX - 1, currentY - 1)) == 0){
			//reparse the input
		}
		if(instanceOutput == KABOOM){
			++hits;
		}
		//clear the terminal
	}
	//LOST
	if(hits < SQUIDFOUR + SQUIDTHREE + SQUIDTWO){
		printAnswerOfGame(grid,fourSquid,threeSquid,twoSquid)
		printf("You lost the game. Please restart application to try again.\n");
	}
	//WON
	else{
		printOutputOfGame(grid);
		printf("You won the game! congradulations!\n");
	}


	return 0;
}