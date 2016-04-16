#ifndef _OUTPUT_H_
#define _OUTPUT_H_

void DrawBoard(int board[board_size][board_size]) {
	printf("\n");
	for (int x = 0; x < board_size; x++) {
		for (int y = 0; y < board_size; y++) {
			printf("%d", board[x][y]);
			if (y != board_size - 1) {
				printf("-");
			}
			else {
				printf("\n");
			}
		}
		if (x < board_size - 1) {
			for (int y = 0; ; y++) {
				if (y < board_size - 1) {
					printf("|/");
				}
				else {
					printf("|\n");
					break;
				}
			}
		}
	}
}

#endif