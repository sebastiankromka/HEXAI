#ifndef _HEX_H_
#define _HEX_H_


int getOpponent(int player) {
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
		currentPlayer = getOpponent(currentPlayer);
	} while (state == noWinner);

	printf("\nEND GAME state = %d\nPress enter to continue...\n", state);
	getchar();
	getchar();
}

int gameAI1vsAI2(int awardsAI1[numberOfAwards], int awardsAI2[numberOfAwards], int firstPlayer) {
	int currentPlayer = firstPlayer;
	int state;
	int result = 40;
	int board[boardSize][boardSize] = { { 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 },
	{ 0, 0, 0, 0, 0 } };
	// game loop
	do {
		result--;
		if (currentPlayer == AI1) {
			moveAI(AI1, board, awardsAI1, 0);
		}
		else {
			moveAI(AI2, board, awardsAI2, 0);
		}
		currentPlayer = getOpponent(currentPlayer);
		state = checkState(board);
	} while (state == noWinner);
	if (state == AI2) {
		result = -result;
	}
	return result;
}

#endif