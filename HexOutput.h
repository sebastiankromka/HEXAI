#ifndef _HEXOUTPUT_C_
#define _HEXOUTPUT_C_

void printBoard(int *board[], int boardSize) {
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

void printItems(int tmpItems[maxDepth][numberOfItemsTypes]) {
	int d, i;
	for (d = 0; d < maxDepth; d++) {
		for (i = 0; i < numberOfItemsTypes; i++) {
			printf("%d, ", tmpItems[d][i]);
		}
		printf("\n");
	}
}

void printMinMaxResult(int tmpItems[maxDepth][numberOfItemsTypes], int minMaxPlayer, int boardSize) {
	int d, i;
	for (d = 0; d < maxDepth && tmpItems[d][stonesInBestChain] > 0; d++) {
		if (minMaxPlayer == player1) {
			printf("D%d player%d [%d][%d] ", d, (minMaxPlayer + d + 1) % 2 + 1, tmpItems[d][xPosition], tmpItems[d][yPosition]);
		}
		else {
			printf("D%d player%d [%d][%d] ", d, (minMaxPlayer + d + 1) % 2 + 1, boardSize - 1 - tmpItems[d][yPosition], boardSize - 1 - tmpItems[d][xPosition]);
		}
		printf("L=%d S=%d ", tmpItems[d][levelsInBestChain], tmpItems[d][stonesInBestChain]);
		for (i = 2; i < numberOfItemsTypes - 2; i++) {
			if (tmpItems[d][i] != 0) {
				printf(namesOfItems[i]);
				printf(" ");
			}
		}
		printf("\n");
	}
}

void saveResults(int *population[], int *rivals[], int populationSize, int rivalsSize, FILE *pf, FILE *rf) {
	for (int p = 0; p < populationSize; p++) {
		for (int a = 0; a < numberOfPointsTypes; a++) {
			fprintf(pf, "%d ", population[p][a]);
		}
		fprintf(pf, "\n");
	}
	for (int p = 0; p < rivalsSize; p++) {
		for (int a = 0; a < numberOfPointsTypes; a++) {
			fprintf(rf, "%d ", rivals[p][a]);
		}
		fprintf(rf, "\n");
	}
}

void saveBestUnits(int *population[], int populationSize, FILE *bf) {
	for (int p = 0; p < populationSize / 2; p++) {
		for (int a = 0; a < numberOfPointsTypes; a++) {
			fprintf(bf, "%d ", population[p][a]);
		}
		fprintf(bf, "\n");
	}
}

void printPopulation(int *array[], int arraySizeA, int arraySizeB, int highlightLast, FILE *f) {
	for (int x = 0; x < arraySizeA; x++) {
		for (int y = 0; y < arraySizeB; y++) {
			if (highlightLast == 1 && y == arraySizeB - 1) {
				fprintf(f, "(%d)", array[x][y]);
				printf("(%d)", array[x][y]);
			}
			else {
				fprintf(f, "%d ", array[x][y]);
				printf("%d ", array[x][y]);
			}
		}
		fprintf(f, "\n");
		printf("\n");
	}
	fprintf(f, "\n");
	printf("\n");
}

#endif