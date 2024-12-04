/* ENGGEN131 C Project 2023 - Battleships */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAP_SIZE 6
#define HIT 1000

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
		return 1;
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

int main(void) 
{
    // FOR THIS TEST, MAP_SIZE WILL BE 7

    int valid, shipSize;
    int map[6][6] = {
        {0, 3, 3, 3, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 5, 5, 2, 5, 5},
        {0, 0, 0, 2, 0, 0},
        {0, 4, 4, 4, 4, 0},
    };

    for (shipSize = 2; shipSize <= 5; shipSize++) {
        valid = IsShipValid(shipSize, map);
        printf("Is ship %d valid? %d\n", shipSize, valid);
    }

    return 0;
}