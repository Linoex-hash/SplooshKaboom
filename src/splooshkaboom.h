#ifndef SPLOOSH_H

/* This is the definition of the squid lengths*/
#define SQUIDFOUR 4
#define SQUIDTHREE 3
#define SQUIDTWO 2

/* define the total number of attempts and grid size */

#define ATTEMPTS 24
#define GRIDSIZE 15

/* define miss (sploosh) and hit (kaboom)*/

#define SPLOOSH 'X'
#define KABOOM 'O'

/* define the directions for generating the squids (UP DOWN LEFT RIGHT) */

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4


/* define the struct points */

typedef struct Point{
	int x; /* x coordinate */
	int y; /* y coordinate */
} Point;

/* define the functions */
/* creates a grid of empty spaces. Use double pointers for practice and efficiency I guess */
char **gengrid();
/* integer validator for coordinates */
int isvalidPoint(int x);

/* takes a grid and prints the output of that grid. O for faliure, any other number for success */
/* format should be exactly this: */
/*  1   2   3   4   5   6   7   8   9   A   B   C   D   E   F
  |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
1 | C | C | C | C | C | C | C | C | C | C | C | C | C | C | C |
  |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
2 | C | C | C | C | C | C | C | C | C | C | C | C | C | C | C |
  |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
3 |	C | C | C | C | C | C | C | C | C | C | C | C | C | C | C |
  |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
4 |	C | C | C | C | C | C | C | C | C | C | C | C | C | C | C |
  |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
5 |	C | C | C | C | C | C | C | C | C | C | C | C | C | C | C |
  |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
6 |	C | C | C | C | C | C | C | C | C | C | C | C | C | C | C |
  |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
7 |	C | C | C | C | C | C | C | C | C | C | C | C | C | C | C |
  |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
8 |	C | C | C | C | C | C | C | C | C | C | C | C | C | C | C |   
  |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
9 |	C | C | C | C | C | C | C | C | C | C | C | C | C | C | C |
  |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
A |	C | C | C | C | C | C | C | C | C | C | C | C | C | C | C |
  |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
B |	C | C | C | C | C | C | C | C | C | C | C | C | C | C | C |
  |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
C |	C | C | C | C | C | C | C | C | C | C | C | C | C | C | C |
  |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
D |	C | C | C | C | C | C | C | C | C | C | C | C | C | C | C |
  |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
E |	C | C | C | C | C | C | C | C | C | C | C | C | C | C | C |
  |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---|
F |	C | C | C | C | C | C | C | C | C | C | C | C | C | C | C |
  |---|---|---|---|---|---|---|---|---|---|---|---|---|---|---| */

int printOutputOfGame(char **grid);
/* takes a grid and plays one instance of sploosh kaboom. 
Return 0 if the player shoots off the grid or a location already marked and KABOOM or SPLOOSH on successful attempt */
int splooshKaboom(char **grid, Point **squidfour, Point**squidthree, Point*squidtwo, int x, int y);
/* prints the answer of the grid upon losing */
int printAnswerOfGame(char **grid, Point **fourSquid, Point **threeSquid, Point **twoSquid);
/* generates a squid of 4 length */
Point **generate4squid();
/* generates a squid of 3 length. Takes in a squid of four length */
Point **generate3squid(Point **fourSquid);
/* generates a squid of 2 length and requires a squid of 3 and 4 to make sure there isn't overlap */
Point **generate2squid(Point **fourSquid, Point **threeSquid);

#endif /*SPLOOSH_H*/