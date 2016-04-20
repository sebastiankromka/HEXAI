#ifndef _MINMAX_H_
#define _MINMAX_H_

int minimax(int board[board_size][board_size], int player, int depth) {
	depth++;
	int bestX = -1;
	int bestY = -1;
	int score;
	int winner = checkState(board);
	if (winner != 0 || depth == maxDepth) {
		score =  getPoints(board,winner,depth);
		return score;
	}

	if (player == player_2) {
		score = 800000;
		for (int x = 0; x < board_size; x++) {
			for (int y = 0; y < board_size; y++) {
				if (board[x][y] == free) {
					board[x][y] = player;

					if (infoLevel > 2) {
						printDepth(depth);
						printf("[%d][%d] - AI", x, y);
						drawBoard(board, depth);
					}

					int thisScore = minimax(board, player_1, depth);

					if (infoLevel > 2) {
						printDepth(depth);
						printf("(%d)", thisScore);
					}

					if (thisScore < score) {
						score = thisScore;
						bestX = x;
						bestY = y;
					}
					board[x][y] = free;
				}
			}
		}
	}
	else {
		score = -800000;
		for (int x = 0; x < board_size; x++) {
			for (int y = 0; y < board_size; y++) {
				if (board[x][y] == free) {
					board[x][y] = player;

					if (infoLevel > 2) {
						printDepth(depth);
						printf("[%d][%d] - human", x, y);
						drawBoard(board, depth);
					}

					int thisScore = minimax(board, player_2, depth);

					if (infoLevel > 2) {
						printDepth(depth);
						printf("(%d)", thisScore);
					}

					if (thisScore > score) {
						score = thisScore;
						bestX = x;
						bestY = y;
					}
					board[x][y] = free;
				}
			}
		}
	}
	return score;
}

void move_player_2(int board[board_size][board_size]) {
	int bestX = -1;
	int bestY = -1;
	int score = -1000000;
	for (int x = 0; x < board_size; x++) {
		for (int y = 0; y < board_size; y++) {
			if (board[x][y] == free) {
				board[x][y] = player_2;

				if (infoLevel > 2) {
					printf("\n[%d][%d] - AI", x, y);
					drawBoard(board, 0);
				}

				int thisScore = minimax(board, player_1, 0);

				if (infoLevel > 1) {
					printf("\nboard[%d][%d] - player 2 result %d", x, y, thisScore);
				}

				if (thisScore > score) {

					if (infoLevel > 2) {
						printf(" (NEW BEST SCORE)");
					}

					score = thisScore;
					bestX = x;
					bestY = y;
				}
				board[x][y] = player_1;

				if (infoLevel > 2) {
					printf("\n[%d][%d] - human", x, y);
					drawBoard(board, 0);
				}

				thisScore = minimax(board, player_2, 0);

				if (infoLevel > 1) {
					printf("\nboard[%d][%d] - player 1 result %d", x, y, thisScore);
				}

				board[x][y] = free;
				if (thisScore > score) {

					if (infoLevel > 2) {
						printf(" (NEW BEST SCORE)");
					}

					score = thisScore;
					bestX = x;
					bestY = y;
				}
			}
		}
	}
	board[bestX][bestY] = player_2;
}

#endif