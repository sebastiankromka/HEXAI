#ifndef _OUTPUT_H_
#define _OUTPUT_H_

void printDepth(int depth, FILE *f) {
	fprintf(f, "\n");
	for (int i = 0; i < depth; i++) {
		fprintf(f, "   ");
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

void drawBoardToFile(int board[board_size][board_size], int depth, FILE *f) {
	fprintf(f, "\n");
	for (int x = 0; x < board_size; x++) {
		for (int y = 0; y < board_size; y++) {
			if (y == 0) {
				for (int i = 0; i < depth; i++) {
					fprintf(f, "   ");
				}
			}
			fprintf(f, "%d", board[x][y]);
			if (y != board_size - 1) {
				fprintf(f, "-");
			}
			else {
				fprintf(f, "\n");
			}
		}
		if (x < board_size - 1) {
			for (int y = 0; ; y++) {
				if (y == 0) {
					for (int i = 0; i < depth; i++) {
						fprintf(f, "   ");
					}
				}
				if (y < board_size - 1) {
					fprintf(f, "|/");
				}
				else {
					fprintf(f, "|\n");
					break;
				}
			}
		}
	}
}

#endif