#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include "HexOutput.h"
#include "operationsOnArrays.h"
#include "HexItems.h"
#include "HexMinMax.h"
#include "HexGame.h"
#include "HexPaths.h"
#include "geneticAlgorithm.h"

int main(int argc, char **argv) {
	int **arrayOfPaths;
	if (argc == 8) {
		arrayOfPaths = allocate2D(arrayOfPathsSize, atoi(argv[2]) + 2);
		geneticAlgorithm(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), atoi(argv[6]), atoi(argv[7]), arrayOfPaths);
	}
	else {
		int logLevel, firstPlayer, AIplayer, AIlevel1, AIlevel2, boardSize, numberOfGenerations, randomRivals, copyToRivals, frequencyCopyToRivals, populationSize, rivalsSize;
		int AI[3][numberOfPointsTypes] = {
		{ 1, 20, 999, 330, 131, 100, 131, 100, 9, 9, 5, 5, 13 },
		{ 40, 300, 999, 130, 131, 100, 131, 100, 9, 9, 5, 5, 13 },
		{ 1, 20, 999, 130, 131, 100, 131, 100, 9, 9, 5, 5, 13 }
		};

		printf("--------------------------------------------------\n");
		printf("1 - Hex AI vs human\n");
		printf("2 - Hex AI vs AI\n");
		printf("3 - genetic algorithm\n");
		printf("--------------------------------------------------\n");

		int option;
		printf("option: ");
		scanf("%d", &option);
		if (option == 1) {
			printf("boardSize (4, 5, 6, 7, 8): ");
			scanf("%d", &boardSize);
			arrayOfPaths = allocate2D(arrayOfPathsSize, boardSize + 2);
			printf("AI level (1 - weak, 2 - mean, 3 - good): ");
			scanf("%d", &AIlevel1);
			printf("human player (1 - top-down, 2 - left-right): ");
			scanf("%d", &AIplayer);
			AIplayer = AIplayer % 2 + 1;
			printf("first player (1 - AI, 2 - human): ");
			scanf("%d", &firstPlayer);
			firstPlayer = (firstPlayer + AIplayer) % 2 + 1;
			printf("logLevel (1, 2, 3): ");
			scanf("%d", &logLevel);
			gameAIvsHuman(AIplayer, firstPlayer, logLevel, boardSize, arrayOfPaths, AI[AIlevel1 - 1]);
			printf("\nPress enter to continue...\n");
			getchar();
			getchar();
		}
		else if (option == 2) {
			printf("boardSize (4, 5, 6, 7, 8): ");
			scanf("%d", &boardSize);
			arrayOfPaths = allocate2D(arrayOfPathsSize, boardSize + 2);
			printf("AI1 level (1 - weak, 2 - mean, 3 - good): ");
			scanf("%d", &AIlevel1);
			printf("AI2 level (1 - weak, 2 - mean, 3 - good): ");
			scanf("%d", &AIlevel2);
			printf("logLevel (1, 2, 3): ");
			scanf("%d", &logLevel);
			gameAIvsAI(player1, logLevel, boardSize, arrayOfPaths, AI[AIlevel1 - 1], AI[AIlevel2 - 1]);
			printf("\nPress enter to continue...\n");
			getchar();
			getchar();
		}
		else if (option == 3) {
			printf("number of generations: ");
			scanf("%d", &numberOfGenerations);
			printf("boardSize (4, 5, 6, 7, 8): ");
			scanf("%d", &boardSize);
			arrayOfPaths = allocate2D(arrayOfPathsSize, boardSize + 2);
			printf("size of population: ");
			scanf("%d", &populationSize);
			printf("size of rivals: ");
			scanf("%d", &rivalsSize);
			printf("copy from population to rivals: ");
			scanf("%d", &copyToRivals);
			printf("frequency of copying from population to rivals: ");
			scanf("%d", &frequencyCopyToRivals);
			printf("random rivals: ");
			scanf("%d", &randomRivals);
			geneticAlgorithm(numberOfGenerations, boardSize, populationSize, rivalsSize, copyToRivals, frequencyCopyToRivals, randomRivals, arrayOfPaths);
		}
		else if (option == 4) {
			arrayOfPaths = allocate2D(arrayOfPathsSize, 5 + 2);
			geneticAlgorithm(5, 5, 6, 6, 1, 2, 1, arrayOfPaths);
		}
	}
	deallocate2D(arrayOfPaths, arrayOfPathsSize);
	return 0;
}