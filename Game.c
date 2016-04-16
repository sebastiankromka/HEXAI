#include <stdio.h>
#include "ConstValues.h"
#include "Output.h"
#include "CheckState.h"
#include "MinMax.h"


// human move
void move_player_1(int board[board_size][board_size]) {
	int x;
	int y;
	do {
		scanf("%d", &x);
		scanf("%d", &y);
	} while (x >= board_size || y >= board_size || board[x][y] != free);
	board[x][y] = player_1;
}

// player_2 is also a human, but temporary
void move_player_2_human(int board[board_size][board_size]) {
	int x;
	int y;
	do {
		scanf("%d", &x);
		scanf("%d", &y);
	} while (x >= board_size || y >= board_size || board[x][y] != free);
	board[x][y] = player_2;
}

int main() {
	int currentPlayer = player_1;
	int state = 0;
	// board initialization
	int board[board_size][board_size] = { { 1, 1, 2, 0 },
										  { 0, 1, 1, 0 },
										  { 0, 0, 0, 0 },
										  { 2, 0, 0, 2 } };

	// game loop
	state = checkState(board);
	while (state == 0) {
		DrawBoard(board);
		if (currentPlayer == player_1) {
			move_player_1(board);
			currentPlayer = player_2;
		}
		else {
			move_player_2_human(board); // player_2 is also a human, but temporary
			currentPlayer = player_1;
		}
		state = checkState(board);
	}

	printf("END GAME state = %d\n", state);
	printf("Press enter to continue...\n");
	getchar();
	getchar();
	return 0;
}