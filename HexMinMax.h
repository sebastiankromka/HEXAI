#ifndef _HEXMINMAX_H_
#define _HEXMINMAX_H_

void minimax(int *board[], int boardSize, int *arrayOfPaths[], int minMaxPlayer, int depth, int points[numberOfPointsTypes], int items[maxDepth][numberOfItemsTypes]) {

	// SWAP
	swapPlayer1andPlayer2(board, boardSize);

	// VARIABLES
	depth++;
	int state, score, bestScore, i, x, y, d, tmpItems[maxDepth][numberOfItemsTypes];
	if (minMaxPlayer == player1) {
		bestScore = -1000000;
	}
	else {
		bestScore = 1000000;
	}

	// COPY ITEMS FROM PREVIUS DEPTH
	for (d = 0; d < maxDepth; d++) {
		for (i = 0; i < numberOfItemsTypes; i++) {
			tmpItems[d][i] = items[d][i];
		}
	}

	// FOR EACH FREE PLACES
	for (x = 0; x < boardSize; x++) {
		for (y = 0; y < boardSize; y++) {
			if (board[x][y] == freeNode) {

				// CLEAR ITEMS FROM PREVIOUS LOOP STEP
				for (d = depth; d < maxDepth; d++) {
					for (i = 0; i < numberOfItemsTypes; i++) {
						tmpItems[d][i] = 0;
					}
				}

				// SET PLAYER
				board[x][y] = player1;
				if (minMaxPlayer == player1) {
					tmpItems[depth][xPosition] = x;
					tmpItems[depth][yPosition] = y;
				}
				else {
					tmpItems[depth][xPosition] = boardSize - 1 - y;
					tmpItems[depth][yPosition] = boardSize - 1 - x;
				}

				// ADD ITEMS
				addItems(board, boardSize, x, y, depth, tmpItems);

				// GET STATE
				state = checkPartialState(board, boardSize, arrayOfPaths, depth, tmpItems, points);

				// GO DEEPER IF NO WINNER AND NOT MAXDEPTH
				if (depth + 1 < maxDepth && state == noWinner) {
					minimax(board, boardSize, arrayOfPaths, getOpponent(minMaxPlayer), depth, points, tmpItems);
				}

				// SAVE BEST MOVE
				score = getScore(tmpItems, points);
				if ((minMaxPlayer == player2 && score < bestScore) || (minMaxPlayer == player1 && score > bestScore)) {
					bestScore = score;
					for (d = depth; d < maxDepth; d++) {
						for (i = 0; i < numberOfItemsTypes; i++) {
							items[d][i] = tmpItems[d][i];
						}
					}
				}

				// CLEAN
				board[x][y] = freeNode;
			}
		}
	}

	// SWAP
	swapPlayer1andPlayer2(board, boardSize);
}

void moveAI(int *board[], int boardSize, int *arrayOfPaths[], int minMaxPlayer, int points[numberOfPointsTypes], int logLevel) {

	// VARIABLES
	int tmp, state, x, y, bestX, bestY, score, depth = 0, d, i, bestScore = -1000000, tmpItems[maxDepth][numberOfItemsTypes], bestItems[maxDepth][numberOfItemsTypes];

	// SWAP IF IT'S PLAYER2
	if (minMaxPlayer == player2) {
		swapPlayer1andPlayer2(board, boardSize);
	}

	// FOR ALL FREE PLACES
	for (x = 0; x < boardSize; x++) {
		for (y = 0; y < boardSize; y++) {
			if (board[x][y] == freeNode) {

				// CLEAR ITEMS FROM PREVIOUS LOOP STEP
				for (d = 0; d < maxDepth; d++) {
					for (i = 0; i < numberOfItemsTypes; i++) {
						tmpItems[d][i] = 0;
					}
				}

				// SET PLAYER
				board[x][y] = player1;
				tmpItems[depth][xPosition] = x;
				tmpItems[depth][yPosition] = y;

				// ADD ITEMS
				addItems(board, boardSize, x, y, depth, tmpItems);

				// GET STATE
				state = checkPartialState(board, boardSize, arrayOfPaths, depth, tmpItems, points);

				// GO DEEPER IF NO WINNER AND NOT MAXDEPTH
				if (depth + 1 < maxDepth && state == noWinner) {
					minimax(board, boardSize, arrayOfPaths, player2, depth, points, tmpItems);
				}

				// SAVE BEST MOVE
				score = getScore(tmpItems, points, logLevel);
				if (score > bestScore) {
					bestScore = score;
					bestX = x;
					bestY = y;
					for (d = depth; d < maxDepth; d++) {
						for (i = 0; i < numberOfItemsTypes; i++) {
							bestItems[d][i] = tmpItems[d][i];
						}
					}
				}

				// CLEAN
				board[x][y] = freeNode;

				// LOG
				if (logLevel >= 3) {
					if (minMaxPlayer == player1) {
						printf("[%d][%d] score = %d\n", x, y, score);
					}
					else {
						printf("[%d][%d] score = %d\n", boardSize - 1 - y, boardSize - 1 - x, score);
					}
					
					printMinMaxResult(tmpItems, minMaxPlayer, boardSize);
				}
			}
		}
	}

	// SET BEST MOVE
	board[bestX][bestY] = player1;

	// SWAP BACK IF IT'S PLAYER2
	if (minMaxPlayer == player2) {
		swapPlayer1andPlayer2(board, boardSize);
	}

	// LOG
	if (logLevel >= 1) {
		if (minMaxPlayer == player1) {
			printf("player1 has chosen [%d][%d] score = %d\n", bestX, bestY, bestScore);
		}
		else {
			printf("player2 has chosen [%d][%d] score = %d\n", boardSize - 1 - bestY, boardSize - 1 - bestX, bestScore);
		}
		if (logLevel >= 2) {
			printMinMaxResult(bestItems, minMaxPlayer, boardSize);
		}
	}
}

#endif