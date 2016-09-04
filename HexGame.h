#ifndef _HEXGAME_H_
#define _HEXGAME_H_

// returns AI1 for AI2 and vice versa
int getOpponent(int player) {
	if (player == player1) {
		return player2;
	}
	return player1;
}

// get x and y from keyboard
void moveHuman(int *board[], int boardSize, int symbol) {
	int x;
	int y;
	do {
		scanf("%d", &x);
		scanf("%d", &y);
	} while (x >= boardSize || y >= boardSize || board[x][y] != freeNode);
	board[x][y] = symbol;
}

// single game AI vs human
void gameAIvsHuman(int AIplayer, int firstPlayer, int logLevel, int boardSize, int *arrayOfPaths[], int points[]) {
	int state, currentPlayer = firstPlayer;

	// create board
	int **board = allocate2D(boardSize, boardSize);

	// print empty board
	if (logLevel > 0) {
		printf("\n");
		printBoard(board, boardSize);
	}

	// game loop
	do {
		if (currentPlayer == AIplayer) {
			moveAI(board, boardSize, arrayOfPaths, AIplayer, points, logLevel, 0);
		}
		else {
			moveHuman(board, boardSize, getOpponent(AIplayer));
		}
		state = checkGameState(board, boardSize, arrayOfPaths, 0);
		if (logLevel > 0) {
			printBoard(board, boardSize);
		}
		currentPlayer = getOpponent(currentPlayer);
	} while (state == noWinner);

	if (logLevel > 0) {
		printf("\nGAME WINNER = PLAYER%d\n", state);
	}
	deallocate2D(board, boardSize);
}

int gameAIvsAI(int firstPlayer, int logLevel, int boardSize, int *arrayOfPaths[], int pointsAI1[], int pointsAI2[]) {
	int state, currentPlayer = firstPlayer, step = 0;
	// create board
	int **board = allocate2D(boardSize, boardSize);

	// print empty board
	if (logLevel > 0) {
		printf("\n");
		printBoard(board, boardSize);
	}

	// game loop
	do {
		if (currentPlayer == player1) {
			moveAI(board, boardSize, arrayOfPaths, currentPlayer, pointsAI1, logLevel);
		}
		else {
			moveAI(board, boardSize, arrayOfPaths, currentPlayer, pointsAI2, logLevel);
		}
		state = checkGameState(board, boardSize, arrayOfPaths);
		if (logLevel > 0) {
			printBoard(board, boardSize);
		}
		currentPlayer = getOpponent(currentPlayer);
		step++;
	} while (state == noWinner);

	if (logLevel > 0) {
		printf("\nGAME WINNER = PLAYER%d\n", state);
	}
	deallocate2D(board, boardSize);

	if (state == player1) {
		return 1000 - step;
	}
	else {
		return -1000 + step;
	}
}

#endif