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
	if (argc == 7) {
		arrayOfPaths = allocate2D(20000, atoi(argv[5]) + 2);
		geneticAlgorithm(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), arrayOfPaths, atoi(argv[6]));
	}
	else {
		int logLevel, firstPlayer, AIplayer, AIlevel1, AIlevel2, boardSize, numberOfGenerations, nominator, denominator, frequencyOverwritingFromPopulation, populationSize, rivalsSize;
		int AI[3][numberOfPointsTypes] = { {1, 10, 10000, 100, 30, 10, 30, 10, 5, 5, 4, 4, 10},
											{ 10, 200, 1000, 200, 30, 20, 30, 20, 10, 10, 8, 8, 10 },
											{ 100, 200, 100, 200, 30, 20, 30, 20, 1000, 1000, 800, 800, 40 } };

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
			arrayOfPaths = allocate2D(20000, boardSize + 2);
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
			gameAIvsHuman(AIplayer, firstPlayer, logLevel, boardSize, arrayOfPaths, AI[AIlevel1]);
		}
		else if (option == 2) {
			printf("boardSize (4, 5, 6, 7, 8): ");
			scanf("%d", &boardSize);
			arrayOfPaths = allocate2D(20000, boardSize + 2);
			printf("AI1 level (1 - weak, 2 - mean, 3 - good): ");
			scanf("%d", &AIlevel1);
			printf("AI2 level (1 - weak, 2 - mean, 3 - good): ");
			scanf("%d", &AIlevel2);
			printf("logLevel (1, 2, 3): ");
			scanf("%d", &logLevel);
			gameAIvsAI(player1, logLevel, boardSize, arrayOfPaths, AI[AIlevel1], AI[AIlevel2]);
		}
		else if (option == 3) {
			printf("boardSize (4, 5, 6, 7, 8): ");
			scanf("%d", &boardSize);
			arrayOfPaths = allocate2D(20000, boardSize + 2);
			printf("number of generations: ");
			scanf("%d", &numberOfGenerations);
			printf("nominator: ");
			scanf("%d", &nominator);
			printf("denominator: ");
			scanf("%d", &denominator);
			printf("frequency overwriting from population: ");
			scanf("%d", &frequencyOverwritingFromPopulation);
			printf("size of population: ");
			scanf("%d", &populationSize);
			geneticAlgorithm(numberOfGenerations, nominator, denominator, frequencyOverwritingFromPopulation, boardSize, arrayOfPaths, populationSize);
		}
	}
	deallocate2D(arrayOfPaths, 20000);
	printf("\nPress enter to continue...\n");
	getchar();
	getchar();
	return 0;
}