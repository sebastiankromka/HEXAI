#ifndef _MINMAX_H_
#define _MINMAX_H_

int minimax(int maximizedPlayer, int board[boardSize][boardSize], int newX, int newY, int currentPlayer, int depth, int currentScore, FILE *f, int logLevel, int awards[numberOfAwards]) {

	int bestMinMaxScore = 0;
	currentScore += getPoints(maximizedPlayer, board, newX, newY, depth, awards);

	if (currentPlayer == maximizedPlayer) {
		bestMinMaxScore = -800000;
	}
	else {
		bestMinMaxScore = 800000;
	}

	if (checkState(board) != 0) {
		return currentScore + getWinnerPoints(maximizedPlayer, depth, currentPlayer, awards);
	}

	depth++;
	if (depth == maxDepth) {
		return currentScore;
	}

	for (int x = 0; x < boardSize; x++) {
		for (int y = 0; y < boardSize; y++) {
			if (board[x][y] == free) {
				board[x][y] = currentPlayer;

				if (logLevel > 2) {
					printDepth(depth, f);
					fprintf(f, "[%d][%d] p%d", x, y, currentPlayer);
				}

				int thisScore = minimax(maximizedPlayer, board, x, y, getOponent(currentPlayer), depth, currentScore, f, logLevel, awards);

				if (logLevel > 2) {
					printDepth(depth, f);
					fprintf(f, "%d", thisScore);
				}

				if ((currentPlayer != maximizedPlayer && thisScore < bestMinMaxScore) || (currentPlayer == maximizedPlayer && thisScore > bestMinMaxScore)) {
					bestMinMaxScore = thisScore;
				}
				board[x][y] = free;
			}
		}
	}

	return bestMinMaxScore;
}

void moveAI(int maximizedPlayer, int board[boardSize][boardSize], int awards[numberOfAwards], int logLevel) {

	// LOG
	FILE *f;
	if (logLevel > 1) {
		time_t now;
		now = time(NULL);
		struct tm *t = localtime(&now);
		char date_time[30];
		strftime(date_time, sizeof(date_time), "%d%m%y_%H%M%S.log", t);
		f = fopen(date_time, "w");
		drawBoardToFile(board, f);
	}

	int depth = 0;
	int bestX = -1;
	int bestY = -1;
	int bestScore = -1000000;
	int currentScore = 0;

	// FOR ALL FREE PLACES
	for (int x = 0; x < boardSize; x++) {
		for (int y = 0; y < boardSize; y++) {
			if (board[x][y] == free) {
				board[x][y] = AI1;
				
				// LOG
				if (logLevel > 0) {
					printf("\n[%d][%d]", x, y);
					if (logLevel > 1) {
						fprintf(f, "\n[%d][%d]", x, y);
					}
				}

				// MINMAX
				currentScore = minimax(maximizedPlayer, board, x, y, getOponent(maximizedPlayer), depth, 0, f, logLevel, awards);

				// LOG
				if (logLevel > 0) {
					printf("\n%d", currentScore);
					if (logLevel > 1) {
						fprintf(f, "\n%d", currentScore);
					}
				}

				// FIND BEST MOVE
				if (currentScore > bestScore) {
					bestScore = currentScore;
					bestX = x;
					bestY = y;
				}
				board[x][y] = free;
			}
		}
	}

	// LOG
	if (logLevel > 0) {
		printf("\nchosen [%d][%d] - score: %d", bestX, bestY, bestScore);
		if (logLevel > 1) {
			fprintf(f, "\nchosen [%d][%d] - score: %d", bestX, bestY, bestScore);
			fclose(f);
		}
	}
	
	// SET BEST MOVE
	board[bestX][bestY] = AI1;
}

#endif