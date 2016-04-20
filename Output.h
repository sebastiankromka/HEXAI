#ifndef _OUTPUT_H_
#define _OUTPUT_H_

void printDepth(int depth) {
	printf("\n");
	for (int i = 0; i < depth; i++) {
		printf("   ");
	}
}

void drawBoard(int board[board_size][board_size], int depth) {
	printf("\n");
	for (int x = 0; x < board_size; x++) {
		for (int y = 0; y < board_size; y++) {
			if (y == 0) {
				for (int i = 0; i < depth; i++) {
					printf("   ");
				}
			}
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
				if (y == 0) {
					for (int i = 0; i < depth; i++) {
						printf("   ");
					}
				}
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