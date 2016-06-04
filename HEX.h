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

void moveHuman(int board[boardSize][boardSize], int symbol) {
	int x;
	int y;
	do {
		scanf("%d", &x);
		scanf("%d", &y);
	} while (x >= boardSize || y >= boardSize || board[x][y] != free);
	board[x][y] = symbol;
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
			moveHuman(board, AI2);
		}
		state = checkState(board);
		drawBoard(board);
		currentPlayer = getOpponent(currentPlayer);
	} while (state == noWinner);

	printf("\nEND GAME state = %d\nPress enter to continue...\n", state);
	getchar();
	getchar();
}

void gameAI2vsHuman(int awardsAI1[numberOfAwards], int firstPlayer, int logLevel) {
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
		if (currentPlayer == AI2) {
			moveAI(AI2, board, awardsAI1, logLevel);
		}
		else {
			moveHuman(board, AI1);
		}
		state = checkState(board);
		drawBoard(board);
		currentPlayer = getOpponent(currentPlayer);
	} while (state == noWinner);

	printf("\nEND GAME state = %d\nPress enter to continue...\n", state);
	getchar();
	getchar();
}

int gameAI1vsAI2(int awardsAI1[numberOfAwards], int awardsAI2[numberOfAwards], int firstPlayer, int logLevel) {
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
			moveAI(AI1, board, awardsAI1, logLevel);
		}
		else {
			moveAI(AI2, board, awardsAI2, logLevel);
		}
		currentPlayer = getOpponent(currentPlayer);
		if (logLevel > 0) {
			drawBoard(board);
		}
		state = checkState(board);
	} while (state == noWinner);
	if (state == AI2) {
		result = -result;
	}
	if (logLevel > 0) {
		printf("\nEND GAME state = %d\n", state);
	}
	return result;
}

#endif