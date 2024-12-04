/* ENGGEN131 C Project 2023 - Battleships */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAP_SIZE 10

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
		return -1;
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

int main(void) 
{
    // FOR THIS TEST, MAP_SIZE WILL BE 10

    int map[MAP_SIZE][MAP_SIZE];

    int histogram[MAP_SIZE][MAP_SIZE];
    for (int i = 0; i < MAP_SIZE; i++) {
        for (int j = 0; j < MAP_SIZE; j++) {
            histogram[i][j] = 0;
        }
    }

    for (int i = 0; i < 10000; i++) {

        int r, c;
        for (r = 0; r < MAP_SIZE; r++) {
            for (c = 0; c < MAP_SIZE; c++) {
                map[r][c] = 0;
            }
        }

        InitialiseRandomMap(map);

        for (r = 0; r < MAP_SIZE; r++) {
            for (c = 0; c < MAP_SIZE; c++) {
                if (map[r][c] > 0) {
                    histogram[r][c]++;
                }
            }     
        }
    }

    // Check that map is covered
    int i, j;
    int covered = 1;
    for (i = 0; i < MAP_SIZE; i++) {
        for (j = 0; j < MAP_SIZE; j++) {
            if (histogram[i][j] == 0) {
                covered = 0;
            }
        }
    }

    if (covered) {
    printf("Test 3 passed\n");
    } else {
    printf("Test 3 failed - not all squares of map are covered\n");
    PrintArray(histogram);
    }

    return 0;
}