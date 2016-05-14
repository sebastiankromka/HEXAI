#ifndef _OUTPUT_H_
#define _OUTPUT_H_

void printDepth(int depth, FILE *f) {
	fprintf(f, "\n");
	for (int i = 0; i < depth; i++) {
		fprintf(f, "   ");
	}
}

void drawBoard(int board[boardSize][boardSize]) {
	printf("\n");
	for (int x = 0; x < boardSize; x++) {
		for (int y = 0; y < boardSize; y++) {
			printf("%d", board[x][y]);
			if (y != boardSize - 1) {
				printf("-");
			}
			else {
				printf("\n");
			}
		}
		if (x < boardSize - 1) {
			for (int y = 0; ; y++) {
				if (y == 0) {
				}
				if (y < boardSize - 1) {
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

void drawBoardToFile(int board[boardSize][boardSize], FILE *f) {
	fprintf(f, "\n");
	for (int x = 0; x < boardSize; x++) {
		for (int y = 0; y < boardSize; y++) {
			fprintf(f, "%d", board[x][y]);
			if (y != boardSize - 1) {
				fprintf(f, "-");
			}
			else {
				fprintf(f, "\n");
			}
		}
		if (x < boardSize - 1) {
			for (int y = 0; ; y++) {
				if (y < boardSize - 1) {
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