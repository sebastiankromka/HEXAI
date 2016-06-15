#ifndef _OUTPUT_H_
#define _OUTPUT_H_

void printDepth(int depth, FILE *f) {
	fprintf(f, "\n");
	for (int i = 0; i < depth; i++) {
		fprintf(f, "   ");
	}
}

void printArray(int array[numberOfAwards + 1], FILE *f) {
	for (int x = 0; x <= numberOfAwards; x++) {
		fprintf(f, "%d ", array[x]);
		printf("%d ", array[x]);
	}
	fprintf(f, "\n");
	printf("\n");
}

void printALLAwards(int awards[populationSize][numberOfAwards + 1], FILE *f) {
	for (int x = 0; x < populationSize; x++) {
		printArray(awards[x], f);
	}
}

void printALLRivals(int rivals[rivalsSize][numberOfAwards + 1], FILE *f) {
	for (int x = 0; x < rivalsSize; x++) {
		printArray(rivals[x], f);
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

void saveResults(int population[populationSize][numberOfAwards + 1], int rivals[populationSize][numberOfAwards + 1], FILE *pf, FILE *rf) {
	for (int p = 0; p < populationSize; p++) {
		for (int a = 0; a < numberOfAwards; a++) {
			fprintf(pf, "%d ", population[p][a]);
		}
		fprintf(pf, "\n");
	}
	for (int p = 0; p < rivalsSize; p++) {
		for (int a = 0; a < numberOfAwards; a++) {
			fprintf(rf, "%d ", rivals[p][a]);
		}
		fprintf(rf, "\n");
	}
}

void saveBestUnits(int population[populationSize][numberOfAwards + 1], FILE *bf) {
	for (int p = 0; p < populationSize / 2; p++) {
		for (int a = 0; a <= numberOfAwards; a++) {
			fprintf(bf, "%d ", population[p][a]);
		}
		fprintf(bf, "\n");
	}
}

#endif