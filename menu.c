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
	if (argc == 9) {
		arrayOfPaths = allocate2D(arrayOfPathsSize, atoi(argv[2]) + 2);
		geneticAlgorithm(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), atoi(argv[6]), atoi(argv[7]), atoi(argv[8]), arrayOfPaths);
	}
	else {
		int logLevel, firstPlayer, AIplayer, AIlevel1, AIlevel2, boardSize, numberOfGenerations, randomRivals, copyToRivals, frequencyCopyToRivals, populationSize, rivalsSize, gamesInOneGeneration;
		int AI[5][numberOfPointsTypes] = {
		{ 33, 45, 99, 80, 40, 45, 85, 83, 1 },
		{ 3, 35, 99, 10, 20, 15, 15, 13, 20 },
		{ 27, 47, 99, 34, 87, 35, 1, 2, 11 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0, 0, 0, 0, 0 }
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
			printf("AI level (1 - weak, 2 - mean, 3 - good, 4 - custom): ");
			scanf("%d", &AIlevel1);
			if (AIlevel1 == 4) {
				for (int i = 0; i < numberOfPointsTypes; i++) {
					printf("%d = ", i);
					scanf("%d", &AI[3][i]);
				}
			}
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
			printf("AI1 level (1 - weak, 2 - mean, 3 - good, 4 - custom): ");
			scanf("%d", &AIlevel1);
			if (AIlevel1 == 4) {
				for (int i = 0; i < numberOfPointsTypes; i++) {
					printf("%d = ", i);
					scanf("%d", &AI[3][i]);
				}
			}
			printf("AI2 level (1 - weak, 2 - mean, 3 - good, 4 - custom): ");
			scanf("%d", &AIlevel2);
			if (AIlevel2 == 4) {
				AIlevel2 = 5;
				for (int i = 0; i < numberOfPointsTypes; i++) {
					printf("%d = ", i);
					scanf("%d", &AI[4][i]);
				}
			}
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
			printf("games in one generation: ");
			scanf("%d", &gamesInOneGeneration);
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
			geneticAlgorithm(numberOfGenerations, boardSize, gamesInOneGeneration, populationSize, rivalsSize, copyToRivals, frequencyCopyToRivals, randomRivals, arrayOfPaths);
		}
		else if (option == 4) {
			arrayOfPaths = allocate2D(arrayOfPathsSize, 5 + 2);
			geneticAlgorithm(5, 5, 5, 10, 15, 1, 2, 1, arrayOfPaths);
		}
	}
	deallocate2D(arrayOfPaths, arrayOfPathsSize);
	return 0;
}