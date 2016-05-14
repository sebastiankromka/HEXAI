#ifndef _CHECKSTATE_H_
#define _CHECKSTATE_H_

int calcPoints(int award, int loss, int depth) {
	return award * (100 - loss * depth) / 100;
}

// check connection and returns 0, player_1 or player_2
// for single point on border
int checkLineFromPoint(int x, int y, int board[boardSize][boardSize], int player) {
	if (player == AI1 && x == boardSize - 1) {
		return AI1; // winner AI1
	}
	else if (player == AI2 && y == boardSize - 1) {
		return AI2; // winner AI1
	}
	int state = noWinner; // no winner

	board[x][y] = checked;
	//   a b
	// d # c
	// e f
	//a
	if (state == noWinner && y != 0 && board[x][y - 1] == player) {
		state = checkLineFromPoint(x, y - 1, board, player);
	}
	//b
	if (state == noWinner && y != 0 && x != boardSize - 1 && board[x + 1][y - 1] == player) {
		state = checkLineFromPoint(x + 1, y - 1, board, player);
	}
	//c
	if (state == noWinner && x != boardSize - 1 && board[x + 1][y] == player) {
		state = checkLineFromPoint(x + 1, y, board, player);
	}
	//d
	if (state == noWinner && x != 0 && board[x - 1][y] == player) {
		state = checkLineFromPoint(x - 1, y, board, player);
	}
	//e
	if (state == noWinner && y != boardSize - 1 && x != 0 && board[x - 1][y + 1] == player) {
		state = checkLineFromPoint(x - 1, y + 1, board, player);
	}
	//f
	if (state == noWinner && y != boardSize - 1 && board[x][y + 1] == player) {
		state = checkLineFromPoint(x, y + 1, board, player);
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

int getPointsFromBridges(int maximizedPlayer, int board[boardSize][boardSize], int x, int y, int depth, int awards[numberOfAwards]) {
	int score = 0;
	
	if (board[x][y] == AI1) {
		// bridge A1
		if (x - 2 >= 0 && y + 1 < boardSize && board[x - 2][y + 1] == AI1 && board[x - 1][y] == free && board[x - 1][y + 1] == free) {
			score += awards[awardForBridgeA];
		}
		// bridge A2
		if (x + 2 < boardSize && y - 1 >= 0 && board[x + 2][y - 1] == AI1 && board[x + 1][y] == free && board[x + 1][y - 1] == free) {
			score += awards[awardForBridgeA];
		}
		// bridge B1
		if (x - 1 >= 0 && y + 2 < boardSize && board[x - 1][y + 2] == AI1 && board[x - 1][y + 1] == free && board[x][y + 1] == free) {
			score += awards[awardForBridgeB];
		}
		// bridge B2
		if (x + 1 < boardSize && y - 2 >= 0 && board[x + 1][y - 2] == AI1 && board[x + 1][y - 1] == free && board[x][y - 1] == free) {
			score += awards[awardForBridgeB];
		}
		// bridge C1
		if (x == 1 && y + 1 < boardSize && board[0][y] == free && board[0][y + 1] == free) {
			score += awards[awardForBridgeC];
		}
		// bridge C2
		if (x == boardSize - 2 && y > 0 && board[boardSize - 1][y - 1] == free && board[boardSize - 1][y] == free) {
			score += awards[awardForBridgeC];
		}
		if (maximizedPlayer != AI1) {
			score = -score;
		}
	}
	else if (board[x][y] == AI2) {
		// bridge B1
		if (x - 2 >= 0 && y + 1 < boardSize && board[x - 2][y + 1] == AI2 && board[x - 1][y] == free && board[x - 1][y + 1] == free) {
			score += awards[awardForBridgeB];
		}
		// bridge B2
		if (x + 2 < boardSize && y - 1 >= 0 && board[x + 2][y - 1] == AI2 && board[x + 1][y] == free && board[x + 1][y - 1] == free) {
			score += awards[awardForBridgeB];
		}
		// bridge A1
		if (x - 1 >= 0 && y + 2 < boardSize && board[x - 1][y + 2] == AI2 && board[x - 1][y + 1] == free && board[x][y + 1] == free) {
			score += awards[awardForBridgeA];
		}
		// bridge A2
		if (x + 1 < boardSize && y - 2 >= 0 && board[x + 1][y - 2] == AI2 && board[x + 1][y - 1] == free && board[x][y - 1] == free) {
			score += awards[awardForBridgeA];
		}
		// bridge C1
		if (x > 0 && y == boardSize - 2 && board[x - 1][boardSize - 1] == free && board[x][boardSize - 1] == free) {
			score += awards[awardForBridgeC];
		}
		// bridge C1
		if (x + 1 < boardSize && y == 1 && board[x][0] == free && board[x + 1][0] == free) {
			score += awards[awardForBridgeC];
		}
		score = calcPoints(score, awards[lossOfAwardForDepthInPercent], depth);
		if (maximizedPlayer != AI2) {
			score = -score;
		}
	}
	return score;
}
int getPointsFromNeighbors(int maximizedPlayer, int board[boardSize][boardSize], int x, int y, int depth, int awards[numberOfAwards]) {
	int score = 0;

	if (board[x][y] == AI1) {
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
		score = calcPoints(score, awards[lossOfAwardForDepthInPercent], depth);
		if (maximizedPlayer != AI1) {
			score = -score;
		}
	}
	else {
		// neighbor C1
		if (x - 1 >= 0 && board[x - 1][y] == AI2) {
			score += awards[awardForNeighborC];
		}
		// neighbor C2
		if (x + 1 < boardSize && board[x + 1][y] == AI2) {
			score += awards[awardForNeighborC];
		}
		// neighbor B1
		if (x - 1 >= 0 && y + 1 < boardSize && board[x - 1][y + 1] == AI2) {
			score += awards[awardForNeighborB];
		}
		// neighbor B2
		if (x + 1 < boardSize && y - 1 >= 0 && board[x + 1][y - 1] == AI2) {
			score += awards[awardForNeighborB];
		}
		// neighbor A1
		if (y + 1 < boardSize && board[x][y + 1] == AI2) {
			score += awards[awardForNeighborA];
		}
		// neighbor A2
		if (y - 1 >= 0 && board[x][y - 1] == AI2) {
			score += awards[awardForNeighborA];
		}
		score = calcPoints(score, awards[lossOfAwardForDepthInPercent], depth);
		if (maximizedPlayer != AI2) {
			score = -score;
		}
	}
	return score;
}

int getPoints(int maximizedPlayer, int board[boardSize][boardSize], int x, int y, int depth, int awards[numberOfAwards]) {
	int score = getPointsFromBridges(maximizedPlayer, board, x, y, depth, awards);
	score += getPointsFromNeighbors(maximizedPlayer, board, x, y, depth, awards);
	return score;
}

int getWinnerPoints (int maximizedPlayer, int depth, int player, int awards[numberOfAwards]){
	int score = awards[awardForWin] * (100 - awards[lossOfAwardForDepthInPercent] * depth) / 100;
	if (player == maximizedPlayer) { // -score for maximizedPlayer because function is called from opponent turn in minmax
		return -score;
	}
	else {
		return score;
	}
}

#endif