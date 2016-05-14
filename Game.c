#include <time.h>
#include <stdio.h>
#include "Configuration.h"
#include "Output.h"
#include "CheckState.h"
#include "MinMax.h"

int getOponent(int player) {
	if (player == AI1) {
		return AI2;
	}
	else {
		return AI1;
	}
}

void moveHuman(int board[boardSize][boardSize]) {
	int x;
	int y;
	do {
		scanf("%d", &x);
		scanf("%d", &y);
	} while (x >= boardSize || y >= boardSize || board[x][y] != free);
	board[x][y] = AI2;
}

void gameAI1vsHuman(int awardsAI1[numberOfAwards], int firstPlayer, int logLevel) {
	printf("start game");

	int currentPlayer = firstPlayer;
	int state;
	int board[boardSize][boardSize] = { { 0, 0, 0, 0, 0 },
										{ 0, 0, 0, 0, 0 },
										{ 0, 0, 0, 0, 0 },
										{ 0, 0, 0, 0, 0 },
										{ 0, 0, 0, 0, 0 } };
	drawBoard(board);

	// game loop
	do {
		if (currentPlayer == AI1) {
			moveAI(AI1, board, awardsAI1, logLevel);
		}
		else {
			moveHuman(board);
		}
		state = checkState(board);
		drawBoard(board);
		currentPlayer = getOponent(currentPlayer);
	} while (state == noWinner);

	printf("\nEND GAME state = %d\nPress enter to continue...\n", state);
	getchar();
	getchar();
}

int main() {
	int awardsAI1[numberOfAwards] = { 1000, 10, 200, 100, 250, 50, 20, 10 };
	gameAI1vsHuman(awardsAI1, AI2, 1);
	return 0;
}