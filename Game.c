#include <stdio.h>
#include "ConstValues.h"
#include "Configuration.h"
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

int main() {
	printf("start game");

	int currentPlayer = firstPlayer;
	int state = 0;

	// game loop
	state = checkState(board);
	drawBoard(board,0);
	while (state == 0) {
		if (currentPlayer == player_1) {
			move_player_1(board);
			currentPlayer = player_2;
		}
		else {
			move_player_2(board);
			currentPlayer = player_1;
		}
		state = checkState(board);
		drawBoard(board,0);
	}

	printf("\nEND GAME state = %d\n", state);
	printf("Press enter to continue...\n");
	getchar();
	getchar();
	return 0;
}