#ifndef _HEXPATHS_H_
#define _HEXPATHS_H_

void changeStones(int *board[], int boardSize, int x, int y, int valueToChange, int newValue) {

	// stones map
	//   1 2
	// 6 c 3
	// 5 4

	// current stone
	if (board[x][y] == valueToChange) {
		board[x][y] = newValue;
	}
	// 1
	if (getNodeState(board, boardSize, x - 1, y) == valueToChange) {
		board[x - 1][y] = newValue;
	}
	// 2
	if (getNodeState(board, boardSize, x - 1, y + 1) == valueToChange) {
		board[x - 1][y + 1] = newValue;
	}
	// 3
	if (getNodeState(board, boardSize, x, y + 1) == valueToChange) {
		board[x][y + 1] = newValue;
	}
	// 4
	if (getNodeState(board, boardSize, x + 1, y) == valueToChange) {
		board[x + 1][y] = newValue;
	}
	// 5
	if (getNodeState(board, boardSize, x + 1, y - 1) == valueToChange) {
		board[x + 1][y - 1] = newValue;
	}
	// 6
	if (getNodeState(board, boardSize, x, y - 1) == valueToChange) {
		board[x][y - 1] = newValue;
	}
}

// return -1 if have connected stones on all levels (winning path)
// arrayOfPaths[size][boardSize + 2]
// boardSize for each level. 1 = stone exist, 0 = not
// + 1 number of stones in current path
// + 1 number of levels in current path
int addPath(int *board[], int boardSize, int *arrayOfPaths[], int x, int y, int previousPath, int currentPath) {
	
	int i, myID = currentPath + 4, nextPath = currentPath + 1;
	if (currentPath == arrayOfPathsSize) {
		printf("full longestPathBoard %d [%d][%d]\n", currentPath, x, y);
		printBoard(board, boardSize);
		exit(99); // works too long
	}

	// COPY PREVIOUS LEVELS
	if (previousPath > -1) {
		for (i = 0; i < boardSize + 2; i++) {
			arrayOfPaths[currentPath][i] = arrayOfPaths[previousPath][i];
		}
	}
	else {
		for (i = 0; i < boardSize + 2; i++) {
			arrayOfPaths[currentPath][i] = 0;
		}
	}

	if (arrayOfPaths[currentPath][x] == 0) {

		// SET CURRENT LEVEL
		arrayOfPaths[currentPath][x] = 1;

		// ADD NUMBER OF LEVELS
		arrayOfPaths[currentPath][boardSize + 1]++;
	}

	// ADD NUMBER OF STONES
	arrayOfPaths[currentPath][boardSize]++;

	// RETURN -1 IF HAVE STONES IN ALL LEVELS IN ONE PATH
	if (arrayOfPaths[currentPath][boardSize + 1] == boardSize) {
		return -1;
	}

	// lock
	changeStones(board, boardSize, x, y, player1, myID);

	// add next new row to arrayOfPaths if find stone on stone map
	// stones map:
	//   1 2
	// 6 # 3
	// 5 4

	// 1
	if (getNodeState(board, boardSize, x - 1, y) == myID) {
		nextPath = addPath(board, boardSize, arrayOfPaths, x - 1, y, currentPath, nextPath);
	}
	// 2
	if (nextPath != -1 && getNodeState(board, boardSize, x - 1, y + 1) == myID) {
		nextPath = addPath(board, boardSize, arrayOfPaths, x - 1, y + 1, currentPath, nextPath);
	}
	// 3
	if (nextPath != -1 && getNodeState(board, boardSize, x, y + 1) == myID) {
		nextPath = addPath(board, boardSize, arrayOfPaths, x, y + 1, currentPath, nextPath);
	}
	// 4
	if (nextPath != -1 && getNodeState(board, boardSize, x + 1, y) == myID) {
		nextPath = addPath(board, boardSize, arrayOfPaths, x + 1, y, currentPath, nextPath);
	}
	// 5
	if (nextPath != -1 && getNodeState(board, boardSize, x + 1, y - 1) == myID) {
		nextPath = addPath(board, boardSize, arrayOfPaths, x + 1, y - 1, currentPath, nextPath);
	}
	// 6
	if (nextPath != -1 && getNodeState(board, boardSize, x, y - 1) == myID) {
		nextPath = addPath(board, boardSize, arrayOfPaths, x, y - 1, currentPath, nextPath);
	}

	// unlock
	changeStones(board, boardSize, x, y, myID, player1);

	return nextPath;
}

int checkPartialState(int *board[], int boardSize, int *arrayOfPaths[], int depth, int items[maxDepth][numberOfItemsTypes], int points[numberOfPointsTypes]) {

	// variables
	int x, y, c, currentPath = 0, bestResult = -1;
	
	// check if player1 win
	// for each player1 stones
	for (x = 0; x < boardSize; x++) {
		for (y = 0; y < boardSize; y++) {
			if (board[x][y] == player1) {
				currentPath = addPath(board, boardSize, arrayOfPaths, x, y, -1, currentPath);
				if (currentPath == -1) {
					items[depth][win] = 1;
					items[depth][levelsInBestChain] = boardSize;
					items[depth][stonesInBestChain] = boardSize;
					return player1;
				}
			}
		}
	}

	// add best path to items
	for (c = 0; c < currentPath; c++) {
		if (arrayOfPaths[c][boardSize + 1] * points[levelsInBestChain] - arrayOfPaths[c][boardSize] * points[stonesInBestChain] > items[depth][levelsInBestChain] * points[levelsInBestChain] - items[depth][stonesInBestChain] * points[stonesInBestChain]) {
			items[depth][levelsInBestChain] = arrayOfPaths[c][boardSize + 1];
			items[depth][stonesInBestChain] = arrayOfPaths[c][boardSize];
		}
	}

	return noWinner;
}

// return 1 if each level includes stone
// else -1
int testStonesOnAllLevels(int *board[], int boardSize) {
	int x, y, stone = 1;
	for (x = 0; x < boardSize && stone == 1; x++) {
		stone = -1;
		for (y = 0; y < boardSize; y++) {
			if (board[x][y] == player1) {
				stone = 1;
				break;
			}
		}
	}
	return stone;
}

// check game state. return AI1 or AI2 if have winning path or noWinner if none of them
int checkGameState(int *board[], int boardSize, int *arrayOfPaths[]) {
	// check player1
	int state = noWinner, currentPath = 0, id = 0, y;
	if (testStonesOnAllLevels(board, boardSize) == 1) {

		for (y = 0; y < boardSize; y++) {
			if (board[boardSize - 1][y] == player1) {

				currentPath = addPath(board, boardSize, arrayOfPaths, boardSize - 1, y, -1, currentPath);
				if (currentPath == -1) {
					return player1;
				}
			}
		}
	}

	// check player2
	swapPlayer1andPlayer2(board, boardSize);
	if (testStonesOnAllLevels(board, boardSize) == 1) {

		for (y = 0; y < boardSize; y++) {
			if (board[boardSize - 1][y] == player1) {

				currentPath = addPath(board, boardSize, arrayOfPaths, boardSize - 1, y, -1, currentPath);
				if (currentPath == -1) {
					state = player2;
					break;
				}
			}
		}
	}
	swapPlayer1andPlayer2(board, boardSize);

	return state;
}

#endif