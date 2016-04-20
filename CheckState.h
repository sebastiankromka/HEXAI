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
	if (y != 0 && x != board_size - 1 && board[x + 1][y - 1] == player) {
		state = checkLineFromPoint(x + 1, y - 1, board, player);
	}
	//c
	if (x != board_size - 1 && board[x + 1][y] == player) {
		state = checkLineFromPoint(x + 1, y, board, player);
	}
	//d
	if (x != 0 && board[x - 1][y] == player) {
		state = checkLineFromPoint(x - 1, y, board, player);
	}
	//e
	if (y != board_size - 1 && x != 0 && board[x - 1][y + 1] == player) {
		state = checkLineFromPoint(x - 1, y + 1, board, player);
	}
	//f
	if (y != board_size - 1 && board[x][y + 1] == player) {
		state = checkLineFromPoint(x, y + 1, board, player);
	}
	board[x][y] = player;
	return state; // no winner
}

// check borders. if player have pawn on 1 site then check 2 site.
// if both exists then check connection (function checkLineFromPoint)
// returns 0, player_1 or player_2
int checkState(int board[board_size][board_size]) {
	int state = 0;
	for (int y = 0; y < board_size; y++) {
		// if have 1 site
		if (board[board_size - 1][y] == player_2) {
			for (int y = 0; y < board_size; y++) {
				// if have 2 site
				if (board[0][y] == player_2) {
					// check connection 1 to 2 site
					state = checkLineFromPoint(0, y, board, player_2);
					if (state != 0) {
						return state;
					}
				}
			}
			break;
		}
	}
	for (int x = 0; x < board_size; x++) {
		// if have 1 site
		if (board[x][board_size - 1] == player_1) {
			for (int x = 0; x < board_size; x++) {
				// if have 2 site
				if (board[x][0] == player_1) {
					// check connection 1 to 2 site
					state = checkLineFromPoint(x, 0, board, player_1);
					if (state != 0) {
						return state;
					}
				}
			}
			break;
		}
	}
	return 0;
}

int getPoints(board, winner, depth) {
	int score = 0;
	if (winner != 0) {
		return winScore - depth * lossOfPointsForDepth;
	}
	// bridge points etc
	return score;
}

#endif