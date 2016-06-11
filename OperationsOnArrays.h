#ifndef _OPERATIONSONARRAYS_H_
#define _OPERATIONSONARRAYS_H_


void overwriteArray(int source[numberOfAwards + 1], int destination[numberOfAwards + 1]) {
	for (int a = 0; a <= numberOfAwards; a++) {
		destination[a] = source[a];
	}
}

void swapArrays(int array1[numberOfAwards + 1], int array2[numberOfAwards + 1]) {
	int arraytmp[numberOfAwards + 1];
	overwriteArray(array1, arraytmp);
	overwriteArray(array2, array1);
	overwriteArray(arraytmp, array2);
}

void copyBoardWithSwapPlayers(int board[boardSize][boardSize], int tmpBoard[boardSize][boardSize]) {
	for (int x = 0; x < boardSize; x++) {
		for (int y = 0; y < boardSize; y++) {
			if (board[x][y] == AI1) {
				tmpBoard[x][y] = AI2;
			}
			else if (board[x][y] == AI2) {
				tmpBoard[x][y] = AI1;
			}
			else {
				tmpBoard[x][y] = free;
			}
		}
	}
}

void swapAI1andAI2(int board[boardSize][boardSize]) {
	int tmp;
	int borderY = boardSize;
	for (int x = 0; x < boardSize; x++) {
		for (int y = 0; y < borderY; y++) {

			tmp = board[boardSize - 1 - y][boardSize - 1 - x];

			if (board[x][y] == AI1) {
				board[boardSize - 1 - y][boardSize - 1 - x] = AI2;
			}
			else if (board[x][y] == AI2) {
				board[boardSize - 1 - y][boardSize - 1 - x] = AI1;
			}
			else {
				board[boardSize - 1 - y][boardSize - 1 - x] = free;
			}

			if (tmp == AI1) {
				board[x][y] = AI2;
			}
			else if (tmp == AI2) {
				board[x][y] = AI1;
			}
			else {
				board[x][y] = free;
			}
		}
		borderY--;
	}
}

#endif