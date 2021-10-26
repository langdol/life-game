
#include <stdio.h>
#define GRIDSIZE 18

// Reset the two-dimensional array
void clearGrid(int(*grid)[GRIDSIZE]) {
	for (int i = 0; i < GRIDSIZE; i++)
	{
		for (int j = 0; j < GRIDSIZE; j++)
			grid[i][j] = 0;
	}
}

void setup(int(*board)[GRIDSIZE], char which) {

	clearGrid(board);

	if (which == 'q') {
		board[5][1] = 1;
		board[5][2] = 1;
		board[6][3] = 1;
		board[7][4] = 1;
		board[8][4] = 1;
		board[9][4] = 1;
		board[10][3] = 1;
		board[11][2] = 1;
		board[11][1] = 1;
	}
	else {
		board[17][0] = 1;
		board[16][1] = 1;
		board[15][1] = 1;
		board[16][2] = 1;
		board[17][2] = 1;
	}
}

int get_value(int board[GRIDSIZE][GRIDSIZE], int row, int col) {

	if (row < 0 || row >= GRIDSIZE

		|| col < 0 || col >= GRIDSIZE

		|| board[row][col] != 1) {

		return 0;

	}
	else {

		return 1;

	}

}

void displayGrid(int(*grid)[GRIDSIZE]) {
	int x, r, c;

	printf("     ");
	for (x = 1; x <= GRIDSIZE; x++) {
		if ((x / 10) != 0)
			printf("%d", x / 10);
		else
			printf(" ");
	}

	printf("\n");
	printf("     ");

	for (x = 1; x <= GRIDSIZE; x++)
		printf("%d", x % 10);
	printf("\n");

	for (r = 0; r < GRIDSIZE; r++) {
		printf("%d", r + 1);

		if (r + 1 < 10)
			printf("  ");
		else
			printf(" ");
		for (c = 0; c < GRIDSIZE; c++) {
			if (grid[r][c] == 1)
				printf("*");
			else
				printf(" ");
		}
		printf("\n");
	}
}

// Count the number of neighbors
int countNeighbors(int(*grid)[GRIDSIZE], int row, int col) {
	int neighbor = 0;

	if (row == 0 || col == 0 || row == (GRIDSIZE - 1) || col == (GRIDSIZE - 1)) {

		// 가장자리이면 표준적인 방법

		neighbor += get_value(grid, row - 1, col - 1);

		neighbor += get_value(grid, row - 1, col);

		neighbor += get_value(grid, row - 1, col + 1);

		neighbor += get_value(grid, row, col - 1);

		neighbor += get_value(grid, row, col + 1);

		neighbor += get_value(grid, row + 1, col - 1);

		neighbor += get_value(grid, row + 1, col);

		neighbor += get_value(grid, row + 1, col + 1);

	}
	else {

		// 내부이면 빠른 방법

		int *p = &(grid[row][col]);

		neighbor += *(p - GRIDSIZE - 1);

		neighbor += *(p - GRIDSIZE);

		neighbor += *(p - GRIDSIZE + 1);

		neighbor += *(p - 1);

		neighbor += *(p + 1);

		neighbor += *(p + GRIDSIZE - 1);

		neighbor += *(p + GRIDSIZE);

		neighbor += *(p + GRIDSIZE + 1);

	}

	return neighbor;

}

// Generate the next generation of the simulation
void genNextGrid(int(*grid)[GRIDSIZE]) {
	int tmp_board[GRIDSIZE][GRIDSIZE];

	int neighbor, h, w;

	for (h = 0; h < GRIDSIZE; h++) {

		for (w = 0; w < GRIDSIZE; w++) {

			neighbor = countNeighbors(grid, h, w);

			if (neighbor == 3) {

				tmp_board[h][w] = 1;

			}
			else if (neighbor == 2 && grid[h][w] == 1) {

				tmp_board[h][w] = 1;

			}
			else if (neighbor >= 4 && grid[h][w] == 1) {

				tmp_board[h][w] = 0;

			}
			else {

				tmp_board[h][w] = 0;

			}

		}

	}

	for (h = 0; h < GRIDSIZE; h++) {

		for (w = 0; w < GRIDSIZE; w++) {

			grid[h][w] = tmp_board[h][w];

		}

	}

}


void main() {
	int board[GRIDSIZE][GRIDSIZE];
	char choice;
	int x = 1;

	do {
		printf("Start with the (q)ueen bee shuttle or the (g)lider pattern? ");
		scanf_s("%c", &choice);
	} while (choice != 'q' && choice != 'g');

	setup(board, choice);

	do {
		printf("Viewing generation #%d:\n\n", x++);
		displayGrid(board);
		genNextGrid(board);
		printf("\n(q)uit or any other key + ENTER to continue: ");
		fflush(stdin);
		scanf_s("%c", &choice);
	} while (choice != 'q');
}
