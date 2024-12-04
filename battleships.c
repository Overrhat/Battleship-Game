/* ENGGEN131 C Project 2023 - Battleships */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAP_SIZE 6
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

	if (map[(*row + 1)][*col] == size) {
		return 2;
	} else if (map[*row][(*col + 1)] == size) {
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

// Provided functions needed for playing the Battleships game:

// First, prototype declarations for the bots:
void GetMoveBot1(int shots[MAP_SIZE][MAP_SIZE], int *row, int *col);
void GetMoveBot2(int shots[MAP_SIZE][MAP_SIZE], int *row, int *col);

// Gets the input for one move from the human player (an alphabetic row and a numeric column)
// This function converts both inputs to numeric values
void GetMoveHuman(int *row, int *col, int player)
{
	char a = ' ';
	int b = -1;
	printf("Player %d: enter move [row/col]: ", player);
	while (!(a >= 'A' && a <= 'Z')) {
		scanf("%c", &a);
	}
	while (!(b >= 0 && b <= 25)) {
		scanf("%d", &b);
	}
	*row = (int)(a - 'A');
	*col = b;
}

// Takes two "shots" arrays as input (which are the visible parts of the game shown to players) and formats them into a string for printing
// The player currently to move is highlighted
void GetDisplayMapString(int shots1[MAP_SIZE][MAP_SIZE], int shots2[MAP_SIZE][MAP_SIZE], int player, char *boardString)
{
	int i, j;
	char numbers[10];
	// Intialise board string to be empty:
	boardString[0] = '\0';
	strcat(boardString, "  ");

	for (i = 0; i < MAP_SIZE; i++) {
		sprintf(numbers, "%d", i%10);
		strcat(boardString, numbers);
	}
	strcat(boardString, "|");
	for (i = 0; i < MAP_SIZE; i++) {
		sprintf(numbers, "%d", i%10);
		strcat(boardString, numbers);
	}
	strcat(boardString, "\n  ");

	for (i = 0; i < MAP_SIZE; i++) {
		strcat(boardString, "-");
	}
	strcat(boardString, "|");
	for (i = 0; i < MAP_SIZE; i++) {
		strcat(boardString, "-");
	}
	strcat(boardString, "\n");

	for (i = 0; i < MAP_SIZE; i++) {
		int len = strlen(boardString);
		boardString[len] = (char)('A' + i);
		boardString[len+1] = '\0';
		strcat(boardString, "|");
		for (j = 0; j < MAP_SIZE; j++) {
			if (shots1[i][j] / HIT > 0) {
				if (shots1[i][j] / HIT == 1) {
					strcat(boardString, "X");
				} else {
					sprintf(numbers, "%d", shots1[i][j] / HIT);
					strcat(boardString, numbers);
				}
			} else if (shots1[i][j] > 0) {
				strcat(boardString, ".");
			} else {
				strcat(boardString, " ");
			}
		}
		strcat(boardString, "|");
		for (j = 0; j < MAP_SIZE; j++) {
			if (shots2[i][j] / HIT > 0) {
				if (shots2[i][j] / HIT == 1) {
					strcat(boardString, "X");
				} else {
					sprintf(numbers, "%d", shots2[i][j] / HIT);
					strcat(boardString, numbers);
				}
			} else if (shots2[i][j] > 0) {
				strcat(boardString, ".");
			} else {
				strcat(boardString, " ");
			}
		}
		strcat(boardString, "|");
		len = strlen(boardString);
		boardString[len] = (char)('A' + i);
		boardString[len+1] = '\0';
		strcat(boardString, "\n");
	}
	if (player == 1) {
		strcat(boardString, "  P1");
		for (i = 0; i < MAP_SIZE-2; i++) {
			strcat(boardString, "*");
		}
	} else {
		for (i = 0; i < MAP_SIZE; i++) {
			strcat(boardString, " ");
		}
		strcat(boardString, "   P2");
		for (i = 0; i < MAP_SIZE-2; i++) {
			strcat(boardString, "*");
		}
	}
	strcat(boardString, "\n");
}

// Plays one game of Battleships, beginning with the specified starting player
// Game type = 1 (human vs human) or 2 (human vs bot) or 3 (bot vs bot)
int PlayOneGame(int startingPlayer, int gameType)
{
	int row, col, player, gameOver;

	// String to display the boards
	char displayBoardString[(2*MAP_SIZE+5)*(MAP_SIZE+5)];

	// The maps containing the locations of the ships
	int mapPlayer1[MAP_SIZE][MAP_SIZE] = {0};
	int mapPlayer2[MAP_SIZE][MAP_SIZE] = {0};

	// The locations of the shots
	int shotsPlayer1[MAP_SIZE][MAP_SIZE] = {0};
	int shotsPlayer2[MAP_SIZE][MAP_SIZE] = {0};

	player = startingPlayer;
	gameOver = 0;

	// Create random maps for each player
	InitialiseRandomMap(mapPlayer1);
	InitialiseRandomMap(mapPlayer2);

	// Display the board if a human is playing
	if (gameType != 3) {
		GetDisplayMapString(shotsPlayer1, shotsPlayer2, player, displayBoardString);
		printf("%s", displayBoardString);
	}

	// Process one move for the current player
	while (!gameOver) {
		if (gameType == 1) {
			GetMoveHuman(&row, &col, player);
			if (player == 1) {
				FireShot(shotsPlayer1, mapPlayer2, row, col);
				gameOver = CheckGameOver(shotsPlayer1, mapPlayer2);
			} else {
				FireShot(shotsPlayer2, mapPlayer1, row, col);
				gameOver = CheckGameOver(shotsPlayer2, mapPlayer1);
			}
		} else if (gameType == 2) {
			if (player == 1) {
				GetMoveHuman(&row, &col, player);
				FireShot(shotsPlayer1, mapPlayer2, row, col);
				gameOver = CheckGameOver(shotsPlayer1, mapPlayer2);
			} else {
				GetMoveBot1(shotsPlayer2, &row, &col);
				printf("Player 2 (bot) moves: %c%d\n", (char)(row+'A'), col);
				FireShot(shotsPlayer2, mapPlayer1, row, col);
				gameOver = CheckGameOver(shotsPlayer2, mapPlayer1);
			}
		} else {
			if (player == 1) {
				GetMoveBot1(shotsPlayer1, &row, &col);
				FireShot(shotsPlayer1, mapPlayer2, row, col);
				gameOver = CheckGameOver(shotsPlayer1, mapPlayer2);
			} else {
				GetMoveBot2(shotsPlayer2, &row, &col);
				FireShot(shotsPlayer2, mapPlayer1, row, col);
				gameOver = CheckGameOver(shotsPlayer2, mapPlayer1);
			}
		}

		// Swap players
		if (!gameOver) {
			player = 3 - player;
		}
		if (gameType != 3) {
			GetDisplayMapString(shotsPlayer1, shotsPlayer2, player, displayBoardString);
			printf("%s", displayBoardString);
		}
	}
	return player;
}

// Play a Battleships tournament
// If the tournament is between a human and a bot, only one game is played
// If the tournament is between two bots, the number of games is requested
void PlayBattleships(void)
{
	int gameType, numberOfGames, result;
	int i, wins1, wins2, player;

	// Get play options:
	printf("Options:\n");
	printf(" [1] = Human vs. Human\n");
	printf(" [2] = Human vs. Bot1\n");
	printf(" [3] = Bot1 vs. Bot2\n");
	printf("Choose game type: ");
	scanf("%d", &gameType);
	numberOfGames = 1;
	result = 0;

	// If two bots are playing a tournament, let the user choose how many games
	if (gameType == 3) {
		printf("Number of games: ");
		scanf("%d", &numberOfGames);
	}

	// Set win counts to zero
	wins1 = 0;
	wins2 = 0;

	// Player 1 will always start the first game
	// If a tournament is played (between two bots), the starting player alternates
	player = 1;

	for (i = 0; i < numberOfGames; i++) {
		result = PlayOneGame(player, gameType);
		if (result == 1) {
			wins1++;
		} else {
			wins2++;
		}
		// Switch the starting player for the next game
		player = 3 - player;
	}

	// Show the outcome (of a single game or tournament)
	if (numberOfGames == 1) {
		printf("\nGame over! Congratulations! Winner is Player %d\n\n", result);
	} else {
		printf("\nTournament over! Games played = %d\nPlayer 1 wins = %d / Player 2 wins = %d\n\n", numberOfGames, wins1, wins2);
	}
}

// The main function for the Battleships program
int main(void)
{
	// Initialise the seed for the random number generator
	srand((unsigned int)time(NULL));

	printf("ENGGEN131 - C Project 2023\n");
	printf("                          ... presents ...\n");
	printf(" ___    __   _____ _____  _     ____  __   _     _   ___   __  \n");
	printf("| |_)  / /\\   | |   | |  | |   | |_  ( (` | |_| | | | |_) ( (` \n");
	printf("|_|_) /_/--\\  |_|   |_|  |_|__ |_|__ _)_) |_| | |_| |_|   _)_) \n");
	printf("\n                __/___            \n");
	printf("          _____/______|           \n");
	printf("  _______/_____\\_______\\_____     \n");
	printf("  \\              < < <       |    \n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("\n");

	PlayBattleships();

	return 0;
}

/******************************************************************************
*******************************************************************************
*******************************************************************************
// Implementations of the two bots can be provided below
// The existing implementations are naive:
// - Bot 1 simply takes random shots (without checking for repeated shots)
// - Bot 2 also takes random shots (but makes a single test on each turn for a repeated shot)
*******************************************************************************
*******************************************************************************
******************************************************************************/

// Strategy for Bot 1
void GetMoveBot1(int shots[MAP_SIZE][MAP_SIZE], int *row, int *col)
{
	int rand_row;
	int rand_col;

	rand_row = shots[0][0]; // to prevent compiler warning (because otherwise "shots" array is not accessed)
	rand_row = rand() % MAP_SIZE;
	rand_col = rand() % MAP_SIZE;

	*row = rand_row;
	*col = rand_col;
}

// Strategy for Bot 2
void GetMoveBot2(int shots[MAP_SIZE][MAP_SIZE], int *row, int *col)
{
	int rand_row;
	int rand_col;

	rand_row = shots[0][0]; // to prevent compiler warning (because otherwise "shots" array is not accessed)
	rand_row = rand() % MAP_SIZE;
	rand_col = rand() % MAP_SIZE;

	// If the shot has been tried before, try one more time
	if (shots[rand_row][rand_col] > 0) {
		rand_row = rand() % MAP_SIZE;
		rand_col = rand() % MAP_SIZE;
	}

	*row = rand_row;
	*col = rand_col;
}













