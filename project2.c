/* ENGGEN131 C Project 2023 - Battleships */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAP_SIZE 10
#define HIT 1000

// Prototype declarations of required functions
void PrintArray(int values[MAP_SIZE][MAP_SIZE]);
void InitialiseMap(int map[MAP_SIZE][MAP_SIZE]);
void AddRandomShip(int size, int map[MAP_SIZE][MAP_SIZE]);
int CountValues(int value, int map[MAP_SIZE][MAP_SIZE]);
int TopLeftPosition(int size, int *row, int *col, int map[MAP_SIZE][MAP_SIZE]);
int IsShipValid(int size, int map[MAP_SIZE][MAP_SIZE]);
void InitialiseRandomMap(int map[MAP_SIZE][MAP_SIZE]);
void FireShot(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE], int row, int col);
int CheckGameOver(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE]);


/******************************************************************************
*******************************************************************************
*******************************************************************************
// Implementations of the required functions should go below
*******************************************************************************
*******************************************************************************
******************************************************************************/

void PrintArray(int values[MAP_SIZE][MAP_SIZE])
{
	int i, j;
	for (i = 0; i < MAP_SIZE; i++) {
		for (j = 0; j < MAP_SIZE; j++) {
			if (j < (MAP_SIZE - 1)) {
				printf("%d ", values[i][j]);
			}
			if (j == (MAP_SIZE - 1)) {
				printf("%d\n", values[i][j]);
			}	
		}
	}
}

void InitialiseMap(int map[MAP_SIZE][MAP_SIZE])
{
	int i, j;
	for (i = 0; i < MAP_SIZE; i++) {
		for (j = 0; j < MAP_SIZE; j++) {
			map[i][j] = 0;
		}
	}

	for (i = 0; i < 2; i++) {
		map[i][0] = 2;
	}
	for (j = 0; j < 4; j++) {
		map[(MAP_SIZE - 1)][j] = 4;
	}
	for (j = 2; j < 5; j++) {
		map[1][j] = 3;
	}
	for (j = (MAP_SIZE - 1); j > (MAP_SIZE - 6); j--) {
		map[3][j] = 5;
	}
}

void AddRandomShip(int size, int map[MAP_SIZE][MAP_SIZE])
{
	int i;

	// deciding random arrangement of the ship to be either vertical or horizontal
	int arrage;
	arrage = rand() % 2;

	if (arrage == 1) { // horizontal
		int x, y;
		y = rand() % MAP_SIZE;
		x = rand() % (MAP_SIZE - size + 1);

		for (i = x; i < (x + size); i++) {
			map[y][i] = size;
		}
	} else { // vertical
		int x, y;
		y = rand() % (MAP_SIZE - size + 1);
		x = rand() % MAP_SIZE;

		for (i = y; i < (y + size); i++) {
			map[i][x] = size;
		}
	}
}

int CountValues(int value, int map[MAP_SIZE][MAP_SIZE])
{
	int i, j;
	int count = 0;
	for (i = 0; i < MAP_SIZE; i++) {
		for (j = 0; j < MAP_SIZE; j++) {
			if (map[i][j] == value)
			count++;
		}
	}
	return count;
}

int TopLeftPosition(int size, int *row, int *col, int map[MAP_SIZE][MAP_SIZE])
{
	int i, j;
	int found = 0;

	for (i = 0; i < MAP_SIZE; i++) {
		for (j = 0; j < MAP_SIZE; j++) {
			if (map[i][j] == size) {
				*row = i;
				*col = j;
				found = 1;
				break;
			}
		}
		if (found == 1) {
			break;
		}
	}

	if (map[(i + 1)][j] == size) {
		return 2;
	} else if (map[i][(j + 1)] == size) {
		return 1;
	} else {
		return -1;
	}
}

int IsShipValid(int size, int map[MAP_SIZE][MAP_SIZE])
{
	// getting the top left point and the direction of the ship
	int row, col, direction;
	direction = TopLeftPosition(size, &row, &col, map);

	if (direction == 1) { // when the ship is horizontal 
		int i;
		if (col == 0 && row == 0) { // 0, 0
			if (map[(row + 1)][col] != 0) {
				return 0;
			}
			for (i = col; i < (col + size); i++) {
				if (i < (col + size - 1)) {
					if ((map[0][i] != size) || (map[1][i] != 0)) {
						return 0;
					}
				} else {
					if ((map[0][(i + 1)] != 0) || (map[1][i] != 0) || (map[0][i] != size)) {
						return 0;
					}
				}
			} 

		} else if (col == 0 && row == (MAP_SIZE - 1)) { // end, 0
			if (map[(row - 1)][col] != 0) {
				return 0;
			}
			for (i = col; i < (col + size); i++) {
				if (i < (col + size - 1)) {
					if ((map[(MAP_SIZE - 1)][i] != size) || (map[(MAP_SIZE - 2)][i] != 0)) {
						return 0;
					}
				} else {
					if ((map[(MAP_SIZE - 1)][(i + 1)] != 0) || (map[(MAP_SIZE - 2)][i] != 0) || (map[(MAP_SIZE - 1)][i] != size)) {
						return 0;
					}
				}
			} 

		} else if ((col == 0) && (!(row == 0 || row == (MAP_SIZE - 1)))) { // first col middle
			if ((map[(row + 1)][col] != 0) || (map[(row - 1)][col] != 0)) {
				return 0;
			}

			for (i = col; i < (col + size); i++) {
				if (i < (col + size - 1)) {
					if ((map[(row - 1)][i] != 0) || (map[(row + 1)][i] != 0) || (map[row][i] != size)) {
						return 0;
					}
				} else {
					if ((map[(row - 1)][i] != 0) || (map[(row + 1)][i] != 0) || (map[row][i] != size) || (map[row][(i + 1)] != 0)) {
						return 0;
					}
				}
			}

		} else if ((row == 0) && (!(col == 0))) { // first row
			if ((map[row][(col - 1)] != 0) || (map[(row + 1)][col] != 0)) {
				return 0;
			}

			for (i = (col + 1); i < (col + size); i++) {
				if (i < (col + size - 1)) {
					if ((map[row][i] != size) || (map[(row + 1)][i] != 0)) {
						return 0;
					}
				} else {
					if (i == (MAP_SIZE - 1)) {
						if ((map[row][i] != size) || (map[(row + 1)][i] != 0)) {
							return 0;
						}
					} else {
						if ((map[row][i] != size) || (map[(row + 1)][i] != 0) || (map[(row)][(i + 1)] != 0)) {
							return 0;
						}
					}
				}
			}

		} else if ((row == (MAP_SIZE - 1)) && (!(col == 0))) { // last row
			if ((map[row][(col - 1)] != 0) || (map[(row - 1)][col] != 0)) {
				return 0;
			}

			for (i = (col + 1); i < (col + size); i++) {
				if (i < (col + size - 1)) {
					if ((map[row][i] != size) || (map[(row - 1)][i] != 0)) {
						return 0;
					}
				} else {
					if (i == (MAP_SIZE - 1)) {
						if ((map[row][i] != size) || (map[(row - 1)][i] != 0)) {
							return 0;
						}
					} else {
						if ((map[row][i] != size) || (map[(row - 1)][i] != 0) || (map[(row)][(i + 1)] != 0)) {
							return 0;
						}
					}
				}
			}
		} else { // middle
			if ((map[(row + 1)][col] != 0) || (map[(row - 1)][col] != 0) || (map[row][(col - 1)] != 0)) {
				return 0;
			}
			for (i = (col + 1); i < (col + size); i++) {
				if (i < (col + size - 1)) {
					if ((map[(row - 1)][i] != 0) || (map[(row + 1)][i] != 0) || (map[row][i] != size)) {
						return 0;
					}
				} else { 
					if (i == (MAP_SIZE - 1)) {
						if ((map[(row - 1)][i] != 0) || (map[(row + 1)][i] != 0) || (map[row][i] != size)) {
							return 0;
						}
					} else {
						if ((map[(row - 1)][i] != 0) || (map[(row + 1)][i] != 0) || (map[row][i] != size) || (map[row][(i + 1)] != 0)) {
							return 0;
						}
					}
				}
			}					
		}
		return 1;
	} else if (direction == 2) { // when the ship is vertical
		int i;
		if (col == 0 && row == 0) { // 0, 0
			if (map[row][(col + 1)] != 0) {
				return 0;
			}
			for (i = (row + 1); i < (row + size); i++) {
				if (i < (row + size - 1)) {
					if ((map[i][0] != size) || (map[i][1] != 0)) {
						return 0;
					}
				} else {
					if ((map[i][0] != size) || (map[i][1] != 0) || (map[(i + 1)][0] != 0)) {
						return 0;
					}
				}
			}	

		} else if (row == 0 && col == (MAP_SIZE - 1)) { // 0, end
			if (map[row][(col - 1)] != 0) {
				return 0;
			}
			for (i = (row + 1); i < (row + size); i++) {
				if (i < (row + size - 1)) {
					if ((map[i][col] != size) || (map[i][(col - 1)] != 0)) {
						return 0;
					}
				} else {
					if ((map[i][col] != size) || (map[i][(col - 1)] != 0) || (map[(i + 1)][col] != 0)) {
						return 0;
					}
				}
			}

		} else if ((row == 0) && (!(col == 0 || col == (MAP_SIZE - 1)))) { // first row middle
			if ((map[row][(col - 1)] != 0) || (map[row][(col + 1)] != 0)) {
				return 0;
			}
			for (i = (row + 1); i < (row + size); i++) {
				if (i < (row + size - 1)) {
					if ((map[i][col] != size) || (map[i][(col - 1)] != 0) || (map[i][(col + 1)] != 0)) {
						return 0;
					}
				} else {
					if ((map[i][col] != size) || (map[i][(col - 1)] != 0) || (map[(i + 1)][col] != 0) || (map[i][(col + 1)] != 0)) {
						return 0;
					}
				}
			}

		} else if ((col == 0) && (!(row == 0))) { // first col
			if ((map[(row - 1)][col] != 0) || (map[row][(col + 1)] != 0)) {
				return 0;
			}
			for (i = (row + 1); i < (row + size); i++) {
				if (i < (row + size - 1)) {
					if ((map[i][col] != size) || (map[i][(col + 1)] != 0)) {
						return 0;
					}
				} else {
					if (i == (MAP_SIZE - 1)) {
						if ((map[i][col] != size) || (map[i][(col + 1)] != 0)) {
							return 0;
						}
					} else {
						if ((map[i][col] != size) || (map[(i + 1)][col] != 0) || (map[i][(col + 1)] != 0)) {
							return 0;
						}
					}
				}
			}

		} else if ((col == (MAP_SIZE - 1)) && (!(row == 0))) { // last col
			if ((map[(row - 1)][col] != 0) || (map[row][(col - 1)] != 0)) {
				return 0;
			}
			for (i = (row + 1); i < (row + size); i++) {
				if (i < (row + size - 1)) {
					if ((map[i][col] != size) || (map[i][(col - 1)] != 0)) {
						return 0;
					}
				} else {
					if (i == (MAP_SIZE -1)) {
						if ((map[i][col] != size) || (map[i][(col - 1)] != 0)) {
							return 0;
						}
					} else {
						if ((map[i][col] != size) || (map[(i + 1)][col] != 0) || (map[i][(col - 1)] != 0)) {
							return 0;
						}
					}
				}
			}

		} else { // middle
			if ((map[(row - 1)][col] != 0) || (map[row][(col + 1)] != 0) || (map[row][(col - 1)] != 0)) {
				return 0;
			}
			for (i = (row + 1); i < (row + size); i++) {
				if (i < (row + size - 1)) {
					if ((map[i][col] != size) || (map[i][(col + 1)] != 0) || (map[i][(col - 1)] != 0)) {
						return 0;
					}
				} else {
					if (i == (MAP_SIZE - 1)) {
						if ((map[i][col] != size) || (map[i][(col + 1)] != 0) || (map[i][(col - 1)] != 0)) {
							return 0;
						}
					} else {
						if ((map[i][col] != size) || (map[(i + 1)][col] != 0) || (map[i][(col + 1)] != 0) || (map[i][(col - 1)] != 0)) {
							return 0;
						}
					}
				}
			}
		}
		return 1;
	} else {
		return 0;
	}
}

void InitialiseRandomMap(int map[MAP_SIZE][MAP_SIZE])
{
	int valid2, valid3, valid4, valid5; // variable that checks the map is valid
	int condition = 0;
	while (condition == 0) {
		// Initialisation to 0
		int i, j;
		for (i = 0; i < MAP_SIZE; i++) {
			for (j = 0; j < MAP_SIZE; j++) {
				map[i][j] = 0;
			}
		}

		AddRandomShip(2, map);
		AddRandomShip(3, map);
		AddRandomShip(4, map);
		AddRandomShip(5, map);
		valid2 = IsShipValid(2, map);
		valid3 = IsShipValid(3, map);
		valid4 = IsShipValid(4, map);
		valid5 = IsShipValid(5, map);

		if (valid2 && valid3 && valid4 && valid5) {
			condition = 1;
		}
	}
}

void FireShot(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE], int row, int col)
{
	int count = 0; // counts how many non zero numbers are in shots array
	int sn; // the shot number
	int i, j;

	for (i = 0; i < MAP_SIZE; i++) {
		for (j = 0; j < MAP_SIZE; j++) {
			if (shots[i][j] > 0) {
				count++;
			}
		}
	}
	sn = count + 1;

	if (map[row][col] == 0 && shots[row][col] == 0) {
		shots[row][col] = sn;
	} else if (map[row][col] > 0 && shots[row][col] == 0) {
		shots[row][col] = sn + 1000;
	}

	int row2, col2, row3, col3, row4, col4, row5, col5;
	int direction2, direction3, direction4, direction5;
	direction2 = TopLeftPosition(2, &row2, &col2, map);
	direction3 = TopLeftPosition(3, &row3, &col3, map);
	direction4 = TopLeftPosition(4, &row4, &col4, map);
	direction5 = TopLeftPosition(5, &row5, &col5, map);

	if (direction2 == 1) { // horizontal 2
		if ((shots[row2][col2] > 1000 && shots[row2][col2] < 2000) && (shots[row2][(col2 + 1)] > 1000 && shots[row2][(col2 + 1)] < 2000)) {
			shots[row2][col2] = shots[row2][col2] + 1000;
			shots[row2][(col2 + 1)] = shots[row2][(col2 + 1)] + 1000;
		}
	} else if (direction2 == 2) { // vertical 2
		if ((shots[row2][col2] > 1000 && shots[row2][col2] < 2000) && (shots[(row2 + 1)][col2] > 1000 && shots[(row2 + 1)][col2] < 2000)) {
			shots[row2][col2] = shots[row2][col2] + 1000;
			shots[(row2 + 1)][col2] = shots[(row2 + 1)][col2] + 1000;
		}
	}

	if (direction3 == 1) { // horizontal 3
		if ((shots[row3][col3] > 1000 && shots[row3][col3] < 2000) && (shots[row3][(col3 + 1)] > 1000 && shots[row3][(col3 + 1)] < 2000) && (shots[row3][(col3 + 2)] > 1000 && shots[row3][(col3 + 2)] < 2000)) {
			shots[row3][col3] = shots[row3][col3] + 2000;
			shots[row3][(col3 + 1)] = shots[row3][(col3 + 1)] + 2000;
			shots[row3][(col3 + 2)] = shots[row3][(col3 + 2)] + 2000;
		}
	} else if (direction3 == 2) { // vertical 3
		if ((shots[row3][col3] > 1000 && shots[row3][col3] < 2000) && (shots[(row3 + 1)][col3] > 1000 && shots[(row3 + 1)][col3] < 2000) && (shots[(row3 + 2)][col3] > 1000 && shots[(row3 + 2)][col3] < 2000)) {
			shots[row3][col3] = shots[row3][col3] + 2000;
			shots[(row3 + 1)][col3] = shots[(row3 + 1)][col3] + 2000;
			shots[(row3 + 2)][col3] = shots[(row3 + 2)][col3] + 2000;
		}
	}

	if (direction4 == 1) { // horizontal 4
		if ((shots[row4][col4] > 1000 && shots[row4][col4] < 2000) && (shots[row4][(col4 + 1)] > 1000 && shots[row4][(col4 + 1)] < 2000) && (shots[row4][(col4 + 2)] > 1000 && shots[row4][(col4 + 2)] < 2000) && (shots[row4][(col4 + 3)] > 1000 && shots[row4][(col4 + 3)] < 2000)) {
			shots[row4][col4] = shots[row4][col4] + 3000;
			shots[row4][(col4 + 1)] = shots[row4][(col4 + 1)] + 3000;
			shots[row4][(col4 + 2)] = shots[row4][(col4 + 2)] + 3000;
			shots[row4][(col4 + 3)] = shots[row4][(col4 + 3)] + 3000;
		}
	} else if (direction4 == 2) { // vertical 4
		if ((shots[row4][col4] > 1000 && shots[row4][col4] < 2000) && (shots[(row4 + 1)][col4] > 1000 && shots[(row4 + 1)][col4] < 2000) && (shots[(row4 + 2)][col4] > 1000 && shots[(row4 + 2)][col4] < 2000) && (shots[(row4 + 3)][col4] > 1000 && shots[(row4 + 3)][col4] < 2000)) {
			shots[row4][col4] = shots[row4][col4] + 3000;
			shots[(row4 + 1)][col4] = shots[(row4 + 1)][col4] + 3000;
			shots[(row4 + 2)][col4] = shots[(row4 + 2)][col4] + 3000;
			shots[(row4 + 3)][col4] = shots[(row4 + 3)][col4] + 3000;
		}
	}

	if (direction5 == 1) { // horizontal 5
		if ((shots[row5][col5] > 1000 && shots[row5][col5] < 2000) && (shots[row5][(col5 + 1)] > 1000 && shots[row5][(col5 + 1)] < 2000) && (shots[row5][(col5 + 2)] > 1000 && shots[row5][(col5 + 2)] < 2000) && (shots[row5][(col5 + 3)] > 1000 && shots[row5][(col5 + 3)] < 2000) && (shots[row5][(col5 + 4)] > 1000 && shots[row5][(col5 + 4)] < 2000)) {
			shots[row5][col5] = shots[row5][col5] + 4000;
			shots[row5][(col5 + 1)] = shots[row5][(col5 + 1)] + 4000;
			shots[row5][(col5 + 2)] = shots[row5][(col5 + 2)] + 4000;
			shots[row5][(col5 + 3)] = shots[row5][(col5 + 3)] + 4000;
			shots[row5][(col5 + 4)] = shots[row5][(col5 + 4)] + 4000;
		}
	} else if (direction5 == 2) { // vertical 5
		if ((shots[row5][col5] > 1000 && shots[row5][col5] < 2000) && (shots[(row5 + 1)][col5] > 1000 && shots[(row5 + 1)][col5] < 2000) && (shots[(row5 + 2)][col5] > 1000 && shots[(row5 + 2)][col5] < 2000) && (shots[(row5 + 3)][col5] > 1000 && shots[(row5 + 3)][col5] < 2000) && (shots[(row5 + 4)][col5] > 1000 && shots[(row5 + 4)][col5] < 2000)) {
			shots[row5][col5] = shots[row5][col5] + 4000;
			shots[(row5 + 1)][col5] = shots[(row5 + 1)][col5] + 4000;
			shots[(row5 + 2)][col5] = shots[(row5 + 2)][col5] + 4000;
			shots[(row5 + 3)][col5] = shots[(row5 + 3)][col5] + 4000;
			shots[(row5 + 4)][col5] = shots[(row5 + 4)][col5] + 4000;
		}
	}
}

int CheckGameOver(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE])
{
	int i, j;
	for (i = 0; i < MAP_SIZE; i++) {
		for (j =0; j < MAP_SIZE; j++) {
			if (map[i][j] != 0) {
				if (shots[i][j] < 1000) {
					return 0;
				}
			}
		}
	}

	return 1;
}

/******************************************************************************
*******************************************************************************
*******************************************************************************
// Implementations of the required functions should go above
*******************************************************************************
*******************************************************************************
******************************************************************************/

/*************************************************************************
** You should define your own test functions below
*************************************************************************/

// Example: a test function for Task One
void TestPrintArray(void)
{
	int map1[MAP_SIZE][MAP_SIZE] = {0};
	printf("Map 1: \n");
	PrintArray(map1);

	int map2[MAP_SIZE][MAP_SIZE] = {0};
	for (int i = 0; i < MAP_SIZE; i++) {
		map2[MAP_SIZE-i-1][i] = i;
	}
	printf("\nMap 2:\n");
	PrintArray(map2);
}

// Example: a test function for Task Two
void TestInitialiseMap(void)
{
	int map1[MAP_SIZE][MAP_SIZE] = {0};
	InitialiseMap(map1);
	printf("\nMap: \n");
	PrintArray(map1);
}

// Example: a test function for Task Three
void TestAddRandomShip(void)
{
	int map1[MAP_SIZE][MAP_SIZE] = {0};
	int map2[MAP_SIZE][MAP_SIZE] = {0};

	AddRandomShip(5, map1);

	printf("\nMap: \n");
	PrintArray(map1);

	AddRandomShip(2, map2);
	AddRandomShip(3, map2);
	AddRandomShip(4, map2);
	AddRandomShip(5, map2);

	printf("\nMap: \n");
	PrintArray(map2);
}

// test count values
void TestCountValues(void)
{
     int map[MAP_SIZE][MAP_SIZE] = {0};
     int count, shipSize;
     InitialiseMap(map);
	 printf("\n");
     PrintArray(map);
     for (shipSize = 2; shipSize <= 5; shipSize++) {
          count = CountValues(shipSize, map);
          printf("The value %d appears %d times\n", shipSize, count);
	 }
}	 	  

// test top left
void TestTopLeftPosition(void)
{
     int map[MAP_SIZE][MAP_SIZE] = {0};
     int row, col, direction, shipSize;
     InitialiseMap(map);
     PrintArray(map);
	for (shipSize = 2; shipSize <= 5; shipSize++) {
		direction = TopLeftPosition(shipSize, &row, &col, map); 
		printf("Ship %d is at (%d, %d) facing %d\n", shipSize, row, col, direction);
	}
}

// test ship valid
void TestIsShipValid(void)
{
    int map[MAP_SIZE][MAP_SIZE] = {0};
    int valid, shipSize;
    InitialiseMap(map);
    PrintArray(map);
    for (shipSize = 2; shipSize <= 5; shipSize++) {
        valid = IsShipValid(shipSize, map);
        printf("Is ship %d valid? %d\n", shipSize, valid);
	}

    // Move Ship 3 to an invalid position
    map[2][3] = 0;
    

    // Move Ship 4 to an invalid position
    map[9][0] = 0;
    map[9][1] = 0;
    map[9][2] = 0;
    map[9][3] = 0;
	map[4][3] = 4;
    map[4][4] = 4;
    map[4][5] = 4;
    map[4][6] = 4;

    PrintArray(map);
    for (shipSize = 2; shipSize <= 5; shipSize++) {
          valid = IsShipValid(shipSize, map);
          printf("Is ship %d valid? %d\n", shipSize, valid);
	}
}	

// test random initialise
void TestInitialiseRandomMap(void)
{
     int map[MAP_SIZE][MAP_SIZE] = {0};
     InitialiseRandomMap(map);
     PrintArray(map);
}

// test fire shot
void TestFireShot(void)
{
     int map[MAP_SIZE][MAP_SIZE] = {0};
     int shots[MAP_SIZE][MAP_SIZE] = {0};
     InitialiseMap(map);
     printf("Map:\n");
     PrintArray(map);
     printf("Shots:\n");
     PrintArray(shots);
     FireShot(shots, map, 2, 0);
     printf("Shots:\n");
     PrintArray(shots);
     FireShot(shots, map, 2, 1);
     printf("Shots:\n");
     PrintArray(shots);
     FireShot(shots, map, 2, 2);
     printf("Shots:\n");
     PrintArray(shots);
     FireShot(shots, map, 2, 3);
     printf("Shots:\n");
     PrintArray(shots);
     FireShot(shots, map, 0, 0);
     FireShot(shots, map, 1, 0);
     FireShot(shots, map, 2, 0);
     FireShot(shots, map, 3, 0);
     FireShot(shots, map, 4, 0);
     FireShot(shots, map, 5, 0);
     printf("Shots:\n");
     PrintArray(shots);
}

// test end game
void TestCheckGameOver(void)
{
    int map[MAP_SIZE][MAP_SIZE] = {0};
    int shots[MAP_SIZE][MAP_SIZE] = {0};

    InitialiseMap(map);
    printf("Map:\n");
    PrintArray(map);
    printf("Shots:\n");
    PrintArray(shots);

	while (!CheckGameOver(shots, map)) {
		FireShot(shots, map, rand()%MAP_SIZE, rand()%MAP_SIZE);
	}

    PrintArray(shots);
}

int main(void)
{
	// Initialise the seed for the random number generator
	srand((unsigned int)time(NULL));

	// TestPrintArray();
	// TestInitialiseMap();
	// TestAddRandomShip();
	// TestCountValues();
	// TestTopLeftPosition();
	// TestIsShipValid();
	TestInitialiseRandomMap();
	// TestFireShot();
	// TestCheckGameOver();

	return 0;
}


