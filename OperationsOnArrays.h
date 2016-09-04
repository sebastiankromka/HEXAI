#ifndef _OPERATIONSONARRAYS_H_
#define _OPERATIONSONARRAYS_H_

int ** allocate2D(int arraySizeA, int arraySizeB) {
	int **array, i, j;
	array = malloc(arraySizeA * sizeof(int *));
	if (array == NULL)
	{
		fprintf(stderr, "out of memory\n");
		return 0;
	}
	for (int i = 0; i < arraySizeA; i++)
	{
		array[i] = malloc(arraySizeB * sizeof(int));
		if (array[i] == NULL)
		{
			fprintf(stderr, "out of memory\n");
			return 0;
		}
	}
	// set zeros
	for (j = 0; j < arraySizeA; j++)
	{
		for (i = 0; i < arraySizeB; i++)
		{
			array[j][i] = 0;
		}
	}
	return array;
}

void deallocate2D(int ** arr2D, int rows) {
	int i;
	for (i = 0; i < rows; i++) {
		free(arr2D[i]);
	}
	free(arr2D);
}

void swapPlayer1andPlayer2(int *board[], int boardSize) {
	int tmp;
	int borderY = boardSize;
	for (int x = 0; x < boardSize; x++) {
		for (int y = 0; y < borderY; y++) {

			tmp = board[boardSize - 1 - y][boardSize - 1 - x];

			if (board[x][y] == player1) {
				board[boardSize - 1 - y][boardSize - 1 - x] = player2;
			}
			else if (board[x][y] == player2) {
				board[boardSize - 1 - y][boardSize - 1 - x] = player1;
			}
			else {
				board[boardSize - 1 - y][boardSize - 1 - x] = freeNode;
			}

			if (tmp == player1) {
				board[x][y] = player2;
			}
			else if (tmp == player2) {
				board[x][y] = player1;
			}
			else {
				board[x][y] = freeNode;
			}
		}
		borderY--;
	}
}

void overwriteArray(int source[numberOfPointsTypes + 1], int destination[numberOfPointsTypes + 1]) {
	for (int a = 0; a <= numberOfPointsTypes; a++) {
		destination[a] = source[a];
	}
}

void swapArrays(int array1[numberOfPointsTypes + 1], int array2[numberOfPointsTypes + 1]) {
	int arraytmp[numberOfPointsTypes + 1];
	overwriteArray(array1, arraytmp);
	overwriteArray(array2, array1);
	overwriteArray(arraytmp, array2);
}

#endif