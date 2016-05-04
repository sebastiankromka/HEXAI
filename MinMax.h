#ifndef _MINMAX_H_
#define _MINMAX_H_

int minimax(int board[board_size][board_size], int newX, int newY, int player, int depth, int currentScore) {
	int bestMinMaxScore = 0;
	int oponent;
	currentScore += getPoints(board, newX, newY, depth);

	if (player == player_1) {
		oponent = player_2;
		bestMinMaxScore = 800000;
	}
	else {
		oponent = player_1;
		bestMinMaxScore = -800000;
	}
	if (checkState(board) != 0) {
		return currentScore + getWinnerPoints(depth, player);
	}
	depth++;
	if (depth == maxDepth) {
		return currentScore;
	}

	for (int x = 0; x < board_size; x++) {
		for (int y = 0; y < board_size; y++) {
			if (board[x][y] == free) {
				board[x][y] = player;

				if (infoLevel > 2) {
					printDepth(depth);
					printf("[%d][%d] p%d", x, y, player);
				}

				int thisScore = minimax(board, x, y, oponent, depth, currentScore);

				if (infoLevel > 2) {
					printDepth(depth);
					printf("%d", thisScore);
				}

				if ((player == player_1 && thisScore < bestMinMaxScore) || (player == player_2 && thisScore > bestMinMaxScore)) {
					bestMinMaxScore = thisScore;
				}
				board[x][y] = free;
			}
		}
	}

	return bestMinMaxScore;
}

void move_player_2(int board[board_size][board_size]) {
	int depth = 0;
	int bestX = -1;
	int bestY = -1;
	int score = -1000000;
	int thisScore = 0;
	for (int x = 0; x < board_size; x++) {
		for (int y = 0; y < board_size; y++) {
			if (board[x][y] == free) {
				board[x][y] = player_2;

				if (infoLevel > 1) {
					printf("\n[%d][%d]", x, y);
				}

				thisScore = minimax(board, x, y, player_1, depth, 0);

				if (infoLevel > 1) {
					printf(" - %d",thisScore);
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
	board[bestX][bestY] = player_2;
}

#endif