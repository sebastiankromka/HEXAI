#ifndef _CHECKSTATE_H_
#define _CHECKSTATE_H_

int calcPoints(int award, int loss, int depth) {
	if (loss != 0) {
		loss /= 10; // because loss is from 0 to 1000
	}
	return award * (100 - loss * depth) / 100;
}

// check connection and returns 0, player_1 or player_2
// for single point on border
int checkLineFromPoint(int x, int y, int board[boardSize][boardSize], int player) {
	if (player == AI1 && x == boardSize - 1) {
		return AI1; // winner AI1
	}
	else if (player == AI2 && y == boardSize - 1) {
		return AI2; // winner AI2
	}
	int state = noWinner; // no winner

	board[x][y] = checked;
	//   a b
	// f # c
	// e d

	//a
	if (state == noWinner && x != 0 && board[x - 1][y] == player) {
		state = checkLineFromPoint(x - 1, y, board, player);
	}
	//b
	if (state == noWinner && y != boardSize - 1 && x != 0 && board[x - 1][y + 1] == player) {
		state = checkLineFromPoint(x - 1, y + 1, board, player);
	}
	//c
	if (state == noWinner && y != boardSize - 1 && board[x][y + 1] == player) {
		state = checkLineFromPoint(x, y + 1, board, player);
	}
	//d
	if (state == noWinner && x != boardSize - 1 && board[x + 1][y] == player) {
		state = checkLineFromPoint(x + 1, y, board, player);
	}
	//e
	if (state == noWinner && y != 0 && x != boardSize - 1 && board[x + 1][y - 1] == player) {
		state = checkLineFromPoint(x + 1, y - 1, board, player);
	}
	//f
	if (state == noWinner && y != 0 && board[x][y - 1] == player) {
		state = checkLineFromPoint(x, y - 1, board, player);
	}
	
	board[x][y] = player;
	return state;
}

// check borders. if player have pawn on 1 site then check 2 site.
// if both exists then check connection (function checkLineFromPoint)
// returns 0, player_1 or player_2
int checkState(int board[boardSize][boardSize]) {
	int state = 0;
	for (int y = 0; y < boardSize; y++) {
		// if have down site
		if (board[boardSize - 1][y] == AI1) {
			for (int y = 0; y < boardSize; y++) {
				// if have up site
				if (board[0][y] == AI1) {
					// check connection 1 to 2 site
					state = checkLineFromPoint(0, y, board, AI1);
					if (state != 0) {
						return state;
					}
				}
			}
			//break;
		}
	}
	for (int x = 0; x < boardSize; x++) {
		// if have right site
		if (board[x][boardSize - 1] == AI2) {
			for (int x = 0; x < boardSize; x++) {
				// if have left site
				if (board[x][0] == AI2) {
					// check connection 1 to 2 site
					state = checkLineFromPoint(x, 0, board, AI2);
					if (state != 0) {
						return state;
					}
				}
			}
			//break;
		}
	}
	return 0;
}

int getPointsFromBridges(int board[boardSize][boardSize], int x, int y, int awards[numberOfAwards]) {
	int score = 0;

	// bridge A1
	if (x - 2 >= 0 && y + 1 < boardSize && board[x - 2][y + 1] == AI1 && board[x - 1][y] == free && board[x - 1][y + 1] == free) {
		score += awards[awardForBridgeA];
	}
	// bridge A2
	if (x + 2 < boardSize && y - 1 >= 0 && board[x + 2][y - 1] == AI1 && board[x + 1][y] == free && board[x + 1][y - 1] == free) {
		score += awards[awardForBridgeA];
	}
	// bridge A1 wall
	if (x == 1 && y + 1 < boardSize && board[0][y] == free && board[0][y + 1] == free) {
		score += awards[awardForBridgeC];
	}
	// bridge A2 wall
	if (x == boardSize - 2 && y > 0 && board[boardSize - 1][y - 1] == free && board[boardSize - 1][y] == free) {
		score += awards[awardForBridgeC];
	}
	// bridge B1
	if (x - 1 >= 0 && y + 2 < boardSize && board[x - 1][y + 2] == AI1 && board[x - 1][y + 1] == free && board[x][y + 1] == free) {
		score += awards[awardForBridgeB];
	}
	// bridge B2
	if (x + 1 < boardSize && y - 2 >= 0 && board[x + 1][y - 2] == AI1 && board[x + 1][y - 1] == free && board[x][y - 1] == free) {
		score += awards[awardForBridgeB];
	}

	return score;
}

int getPointsFromNeighbors(int board[boardSize][boardSize], int x, int y, int awards[numberOfAwards]) {
	int score = 0;
	// neighbor A1
	if (x - 1 >= 0 && board[x - 1][y] == AI1) {
		score += awards[awardForNeighborA];
	}
	// neighbor A2
	if (x + 1 < boardSize && board[x + 1][y] == AI1) {
		score += awards[awardForNeighborA];
	}
	// neighbor B1
	if (x - 1 >= 0 && y + 1 < boardSize && board[x - 1][y + 1] == AI1) {
		score += awards[awardForNeighborB];
	}
	// neighbor B2
	if (x + 1 < boardSize && y - 1 >= 0 && board[x + 1][y - 1] == AI1) {
		score += awards[awardForNeighborB];
	}
	// neighbor C1
	if (y + 1 < boardSize && board[x][y + 1] == AI1) {
		score += awards[awardForNeighborC];
	}
	// neighbor C2
	if (y - 1 >= 0 && board[x][y - 1] == AI1) {
		score += awards[awardForNeighborC];
	}
	
	return score;
}

void addPath(int x, int y, int board[boardSize][boardSize], int previousPawn) {
	if (currentPath == longestPathBoardSize) {
		printf("full longestPathBoard %d [%d][%d]\n", currentPath, x, y);
		drawBoard(board);
		return;
	}
	// CLEAN
	for (int i = 0; i < boardSize + 1; i++) {
		longestPathArray[currentPath][i] = longestPathArray[previousPawn][i];
	}
	// ADD CURRENT LEVEL
	longestPathArray[currentPath][x] = 1;
	// ADD NUMBER OF PAWNS + 1
	longestPathArray[currentPath][boardSize]++;
	
	board[x][y] = checked;

	int myID = currentPath;
	currentPath++;

	//   a b
	// f # c
	// e d

	//a
	if (x > 0 && board[x - 1][y] == AI1) {
		addPath(x - 1, y, board, myID);
	}
	//b
	if (x > 0 && y < boardSize - 1 && board[x - 1][y + 1] == AI1) {
		addPath(x - 1, y + 1, board, myID);
	}
	//c
	if (y < boardSize - 1 && board[x][y + 1] == AI1) {
		addPath(x, y + 1, board, myID);
	}
	//d
	if (x < boardSize - 1 && board[x + 1][y] == AI1) {
		addPath(x + 1, y, board, myID);
	}
	//e
	if (x < boardSize - 1 && y > 0 && board[x + 1][y - 1] == AI1) {
		addPath(x + 1, y - 1, board, myID);
	}
	//f
	if (y > 0 && board[x][y - 1] == AI1) {
		addPath(x, y - 1, board, myID);
	}
	board[x][y] = AI1;
}

calcPointsFromPath(int levels, int pawns, int awards[numberOfAwards]) {
	return awards[awardForLevel] * levels - awards[lossOfAwardForPawns] * pawns;
}

int getPointsFromLongestPath(int board[boardSize][boardSize], int x, int y, int awards[numberOfAwards]) {
	currentPath = 0;
	int bestScore = -1000000;

	// CLEAN FIRST
	for (int i = 0; i < boardSize + 1; i++) {
		longestPathArray[currentPath][i] = 0;
	}

	addPath(x, y, board, 0, 0);

	// SINGLE
	for (int p1 = 0; p1 < currentPath; p1++) {
		int levels = 0;
		for (int i = 0; i < boardSize; i++) {
			if (longestPathArray[p1][i] == 1) {
				levels++;
			}
		}
		int currentResult = calcPointsFromPath(levels, longestPathArray[p1][boardSize], awards);
		if (currentResult > bestScore) {
			bestScore = currentResult;
		}
	}

	// PAIRS
	for (int p1 = 1; p1 < currentPath; p1++) {		
		for (int p2 = p1 + 1; p2 < currentPath; p2++) {
			int levels = 0;
			for (int i = 0; i < boardSize; i++) {
				if (longestPathArray[p1][i] == 1 || longestPathArray[p2][i] == 1) {
					levels++;
				}
			}
			int currentResult = calcPointsFromPath(levels, longestPathArray[p1][boardSize] + longestPathArray[p2][boardSize] - 1, awards);
			if (currentResult > bestScore) {
				bestScore = currentResult;
			}
		}
	}
	return bestScore;
}

int getPoints(int board[boardSize][boardSize], int x, int y, int depth, int awards[numberOfAwards]) {
	int score = 0;
	score += getPointsFromBridges(board, x, y, awards);
	score += getPointsFromNeighbors(board, x, y, awards);
	score += getPointsFromLongestPath(board, x, y, awards);
	score = calcPoints(score, awards[lossOfAwardForDepthInPercent], depth);
	return score;
}

int getWinnerPoints (int depth, int awards[numberOfAwards]){
	return calcPoints(awards[awardForWin], awards[lossOfAwardForDepthInPercent], depth);
}

#endif