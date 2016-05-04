#ifndef _CHECKSTATE_H_
#define _CHECKSTATE_H_

// check connection and returns 0, player_1 or player_2
// for single point on border
int checkLineFromPoint(int x, int y, int board[board_size][board_size], int player) {
	if (player == player_2 && x == board_size - 1) {
		return player_2; // win player_2
	}
	else if (player == player_1 && y == board_size - 1) {
		return player_1;
	}
	board[x][y] = checked; // win player_1
	int state = 0;
	//   a b
	// d # c
	// e f
	//a
	if (y != 0 && board[x][y - 1] == player) {
		state = checkLineFromPoint(x, y - 1, board, player);
	}
	//b
	if (state == 0 && y != 0 && x != board_size - 1 && board[x + 1][y - 1] == player) {
		state = checkLineFromPoint(x + 1, y - 1, board, player);
	}
	//c
	if (state == 0 && x != board_size - 1 && board[x + 1][y] == player) {
		state = checkLineFromPoint(x + 1, y, board, player);
	}
	//d
	if (state == 0 && x != 0 && board[x - 1][y] == player) {
		state = checkLineFromPoint(x - 1, y, board, player);
	}
	//e
	if (state == 0 && y != board_size - 1 && x != 0 && board[x - 1][y + 1] == player) {
		state = checkLineFromPoint(x - 1, y + 1, board, player);
	}
	//f
	if (state == 0 && y != board_size - 1 && board[x][y + 1] == player) {
		state = checkLineFromPoint(x, y + 1, board, player);
	}
	board[x][y] = player;
	return state;
}

// check borders. if player have pawn on 1 site then check 2 site.
// if both exists then check connection (function checkLineFromPoint)
// returns 0, player_1 or player_2
int checkState(int board[board_size][board_size]) {
	int state = 0;
	for (int y = 0; y < board_size; y++) {
		// if have down site
		if (board[board_size - 1][y] == player_2) {
			for (int y = 0; y < board_size; y++) {
				// if have up site
				if (board[0][y] == player_2) {
					// check connection 1 to 2 site
					state = checkLineFromPoint(0, y, board, player_2);
					if (state != 0) {
						return state;
					}
				}
			}
			//break;
		}
	}
	for (int x = 0; x < board_size; x++) {
		// if have right site
		if (board[x][board_size - 1] == player_1) {
			for (int x = 0; x < board_size; x++) {
				// if have left site
				if (board[x][0] == player_1) {
					// check connection 1 to 2 site
					state = checkLineFromPoint(x, 0, board, player_1);
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
int getPointsFromBridges(int board[board_size][board_size], int x, int y, int depth) {
	int score = 0;
	
	if (board[x][y] == player_2) {
		// bridge A1
		if (x - 2 >= 0 && y + 1 < board_size && board[x - 2][y + 1] == player_2 && board[x - 1][y] == 0 && board[x - 1][y + 1] == 0) {
			score = bridgeAScore * (100 - lossPercentsOfPointsForDepth * depth) / 100;
		}
		// bridge A2
		if (x + 2 < board_size && y - 1 >= 0 && board[x + 2][y - 1] == player_2 && board[x + 1][y] == 0 && board[x + 1][y - 1] == 0) {
			score = bridgeAScore * (100 - lossPercentsOfPointsForDepth * depth) / 100;
		}
		// bridge B1
		if (x - 1 >= 0 && y + 2 < board_size && board[x - 1][y + 2] == player_2 && board[x - 1][y + 1] == 0 && board[x][y + 1] == 0) {
			score = bridgeBScore * (100 - lossPercentsOfPointsForDepth * depth) / 100;
		}
		// bridge B2
		if (x + 1 < board_size && y - 2 >= 0 && board[x + 1][y - 2] == player_2 && board[x + 1][y - 1] == 0 && board[x][y - 1] == 0) {
			score = bridgeBScore * (100 - lossPercentsOfPointsForDepth * depth) / 100;
		}
	}
	else if (board[x][y] == player_1) {
		// bridge B1
		if (x - 2 >= 0 && y + 1 < board_size && board[x - 2][y + 1] == player_1 && board[x - 1][y] == 0 && board[x - 1][y + 1] == 0) {
			score = -bridgeBScore * (100 - lossPercentsOfPointsForDepth * depth) / 100;
		}
		// bridge B2
		if (x + 2 < board_size && y - 1 >= 0 && board[x + 2][y - 1] == player_1 && board[x + 1][y] == 0 && board[x + 1][y - 1] == 0) {
			score = -bridgeBScore * (100 - lossPercentsOfPointsForDepth * depth) / 100;
		}
		// bridge A1
		if (x - 1 >= 0 && y + 2 < board_size && board[x - 1][y + 2] == player_1 && board[x - 1][y + 1] == 0 && board[x][y + 1] == 0) {
			score = -bridgeAScore * (100 - lossPercentsOfPointsForDepth * depth) / 100;
		}
		// bridge A2
		if (x + 1 < board_size && y - 2 >= 0 && board[x + 1][y - 2] == player_1 && board[x + 1][y - 1] == 0 && board[x][y - 1] == 0) {
			score = -bridgeAScore * (100 - lossPercentsOfPointsForDepth * depth) / 100;
		}
	}
	return score;
}
int getPointsFromNeighbors(int board[board_size][board_size], int x, int y, int depth) {
	int score = 0;

	if (board[x][y] == player_2) {
		// bridge C1
		if (x - 1 >= 0 && board[x - 1][y] == player_2) {
			score = neighborCScore * (100 - lossPercentsOfPointsForDepth * depth) / 100;
		}
		// bridge C2
		if (x + 1 < board_size && board[x + 1][y] == player_2) {
			score = neighborCScore * (100 - lossPercentsOfPointsForDepth * depth) / 100;
		}
		// bridge D1
		if (x - 1 >= 0 && y + 1 < board_size && board[x - 1][y + 1] == player_2) {
			score = neighborDScore * (100 - lossPercentsOfPointsForDepth * depth) / 100;
		}
		// bridge D2
		if (x - 1 < board_size && y + 1 >= 0 && board[x - 1][y + 1] == player_2) {
			score = neighborDScore * (100 - lossPercentsOfPointsForDepth * depth) / 100;
		}
		// bridge E1
		if (y + 1 < board_size && board[x][y + 1] == player_2) {
			score = neighborEScore * (100 - lossPercentsOfPointsForDepth * depth) / 100;
		}
		// bridge E2
		if (y - 1 >= 0 && board[x][y - 1] == player_2) {
			score = neighborEScore * (100 - lossPercentsOfPointsForDepth * depth) / 100;
		}
	}
	else if (board[x][y] == player_1) {
		// bridge E1
		if (x - 1 >= 0 && board[x - 1][y] == player_1) {
			score = -neighborEScore * (100 - lossPercentsOfPointsForDepth * depth) / 100;
		}
		// bridge E2
		if (x + 1 < board_size && board[x + 1][y] == player_1) {
			score = -neighborEScore * (100 - lossPercentsOfPointsForDepth * depth) / 100;
		}
		// bridge D1
		if (x - 1 >= 0 && y + 1 < board_size && board[x - 1][y + 1] == player_1) {
			score = -neighborDScore * (100 - lossPercentsOfPointsForDepth * depth) / 100;
		}
		// bridge D2
		if (x - 1 < board_size && y + 1 >= 0 && board[x - 1][y + 1] == player_1) {
			score = -neighborDScore * (100 - lossPercentsOfPointsForDepth * depth) / 100;
		}
		// bridge C1
		if (y + 1 < board_size && board[x][y + 1] == player_1) {
			score = -neighborCScore * (100 - lossPercentsOfPointsForDepth * depth) / 100;
		}
		// bridge C2
		if (y - 1 >= 0 && board[x][y - 1] == player_1) {
			score = -neighborCScore * (100 - lossPercentsOfPointsForDepth * depth) / 100;
		}
	}
	return score;
}

int getPoints(int board[board_size][board_size], int x, int y, int depth) {
	int score = getPointsFromBridges(board, x, y, depth);
	return score;
}

int getWinnerPoints (int depth, int player){
	int score = winScore * (100 - lossPercentsOfPointsForDepth * depth) / 100;
	if (player == player_2) {
		return -score;
	}
	else {
		return score;
	}
}

#endif