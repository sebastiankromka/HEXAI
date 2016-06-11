#ifndef _MINMAX_H_
#define _MINMAX_H_

int minimax(int board[boardSize][boardSize], int minMaxPlayer, int depth, int previousPoints, FILE *f, int logLevel, int awards[numberOfAwards]) {

	depth++;

	// VARIABLES
	int state;
	int forwardPoints;
	int backPoints;
	int bestScore;
	if (minMaxPlayer == AI1) {
		bestScore = -1000000;
	}
	else {
		bestScore = 1000000;
	}

	//printf("\ndepth %d, player %d\n", depth, minMaxPlayer);
	//drawBoard(board);

	// FOR ALL FREE PLACES
	for (int x = 0; x < boardSize; x++) {
		for (int y = 0; y < boardSize; y++) {
			if (board[x][y] == free) {

				// LOG
				if (logLevel > 2) {
					printDepth(depth, f);
					fprintf(f, "[%d][%d] player:%d", x, y, minMaxPlayer);
				}

				// SET PLAYER
				board[x][y] = minMaxPlayer;
				
				if (minMaxPlayer == AI2) {
					// CHANGE PLAYER AI2 TO AI1
					swapAI1andAI2(board);
					// ADD POINTS
					forwardPoints = previousPoints - getPoints(board, (boardSize - 1 - y), (boardSize - 1 - x), depth, awards);
				}
				else {
					// ADD POINTS
					forwardPoints = previousPoints + getPoints(board, x, y, depth, awards);
				}

				// GET STATE
				state = checkState(board);

				if (minMaxPlayer == AI2) {
					// BACK PLAYER AI2 TO AI2
					swapAI1andAI2(board);
				}

				// IF WIN AI1 -> ADD WIN POINTS (ALWAYS AI1 OR NO WIN BECAUSE OF BOARD ROTATE)
				if (state != noWinner) {
					if (state == minMaxPlayer) {
						backPoints = forwardPoints + getWinnerPoints(depth, awards);
					}
					else if (state != minMaxPlayer) {
						backPoints = forwardPoints - getWinnerPoints(depth, awards);
					}
				}

				// IF DEPTH IS MAX -> STOP ALGORITHM
				else if (depth >= maxDepth) {
					backPoints = forwardPoints;
				}
				// ELSE -> MINMAX
				else {
					backPoints = minimax(board, getOpponent(minMaxPlayer), depth, forwardPoints, f, logLevel, awards);
				}

				// LOG
				if (logLevel > 2) {
					printDepth(depth, f);
					fprintf(f, "%d", backPoints);
				}

				// FIND BEST MOVE
				if ((minMaxPlayer == AI2 && backPoints < bestScore) || (minMaxPlayer == AI1 && backPoints > bestScore)) {
					bestScore = backPoints;
				}

				// CLEAN
				board[x][y] = free;
			}
		}
	}

	return bestScore;
}

void moveAI(int minMaxPlayer, int board[boardSize][boardSize], int awards[numberOfAwards], int logLevel) {
	
	// LOG
	FILE *f;
	if (logLevel > 2) {
		time_t now;
		now = time(NULL);
		struct tm *t = localtime(&now);
		char date_time[30];
		strftime(date_time, sizeof(date_time), "%d%m%y_%H%M%S.log", t);
		f = fopen(date_time, "w");
		drawBoardToFile(board, f);
	}

	// VARIABLES
	int state;
	int bestX;
	int bestY;
	int forwardPoints;
	int backPoints;
	int bestScore = -1000000;

	if (minMaxPlayer == AI2) {
		// CHANGE PLAYER AI2 TO AI1
		swapAI1andAI2(board);
	}

	// FOR ALL FREE PLACES
	for (int x = 0; x < boardSize; x++) {
		for (int y = 0; y < boardSize; y++) {
			if (board[x][y] == free) {

				// LOG
				if (logLevel > 1) {
					printf("[%d][%d] = ", x, y);
					if (logLevel > 2) {
						fprintf(f, "\nm[%d][%d]", x, y);
					}
				}

				// SET PLAYER
				board[x][y] = AI1;

				// ADD POINTS
				forwardPoints = getPoints(board, x, y, 0, awards);

				// IF WIN AI1 -> ADD WIN POINTS (ALWAYS AI1 OR NO WIN BECAUSE OF BOARD ROTATE)
				int state = checkState(board);
				if (state == AI1) {
					backPoints = forwardPoints + getWinnerPoints(0, awards);
				}
				else if (state == AI2) {
					backPoints = forwardPoints - getWinnerPoints(0, awards);
				}
				else if (0 >= maxDepth) {
					backPoints = forwardPoints;
				}
				// ELSE -> MINMAX
				else {
					backPoints = minimax(board, AI2, 0, forwardPoints, f, logLevel, awards);
				}

				// LOG
				if (logLevel > 1) {
					printf("%d\n", backPoints);
					if (logLevel > 2) {
						fprintf(f, "\n%d", backPoints);
					}
				}

				// FIND BEST MOVE
				if (backPoints > bestScore) {
					bestScore = backPoints;
					bestX = x;
					bestY = y;
				}

				// CLEAN
				board[x][y] = free;
			}
		}
	}

	// LOG
	if (logLevel > 1) {
		printf("\nchosen [%d][%d] - score: %d", bestX, bestY, bestScore);
		if (logLevel > 2) {
			fprintf(f, "\nchosen [%d][%d] - score: %d", bestX, bestY, bestScore);
			fclose(f);
		}
	}
	
	// SET BEST MOVE
	board[bestX][bestY] = AI1;

	if (minMaxPlayer == AI2) {
		// BACK PLAYER AI2 TO AI2
		swapAI1andAI2(board);
	}
}

#endif