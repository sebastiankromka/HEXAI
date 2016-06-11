#include <time.h>
#include <stdio.h>
#include "Configuration.h"
#include "Output.h"
#include "OperationsOnArrays.h"
#include "MinMax.h"
#include "HEX.h"
#include "CheckState.h"
#include "geneticAlgorithm.h"

int main() {

	//TODO load from file
	int awards1[numberOfAwards] = { 800, 50, 50, 2, 1, 3, 2, 1, 5, 1 };
	int awards2[numberOfAwards] = { 800, 50, 50, 2, 1, 3, 2, 1, 5, 1 };

	printf("--------------------------------------------------\n\n");
	printf("1 - AI vs human log = 2\n\n");
	printf("2 - AI vs human log = 3\n\n");
	printf("3 - AI1 vs AI2 log = 1\n\n");
	printf("4 - AI1 vs AI2 log = 2\n\n");
	printf("5 - AI1 vs AI2 log = 3\n\n");
	printf("6 - genetic algorithm\n\n");
	printf("--------------------------------------------------\n\n");

	int option;
	printf("option: ");
	scanf("%d", &option);

	if (option == 1) {
		gameAIvsHuman(awards1, AI1, 1, 2);
	}
	else if (option == 2) {
		gameAIvsHuman(awards1, AI1, 1, 3);
	}
	else if (option == 3) {		
		gameAI1vsAI2(awards1, awards2, AI1, 1);
	}
	else if (option == 4) {
		gameAI1vsAI2(awards1, awards2, AI1, 2);
	}
	else if (option == 5) {
		gameAI1vsAI2(awards1, awards2, AI1, 3);
	}
	else if (option == 6) {

		printf("\n\n--------------------------------------------------\n\n");
		printf("1 - static rivals\n\n");
		printf("2 - random rivals\n\n");
		printf("3 - 1/2 random and 1/2 static\n\n");
		printf("4 - 1/2 random and 1/2 from optimalized population\n    frequency of overwriting = 5\n\n");
		printf("5 - 2/3 random and 1/3 from optimalized population\n    frequency of overwriting = 3\n\n");
		printf("6 - custom\n\n");
		printf("--------------------------------------------------\n\n");

		printf("option: ");
		scanf("%d", &option);

		if (option == 1) {
			geneticAlgorithm(1000, 0, 1, 0);
		}
		else if (option == 2) {
			geneticAlgorithm(1000, 1, 1, 0);
		}
		else if (option == 3) {
			geneticAlgorithm(1000, 1, 2, 0);
		}
		else if (option == 4) {
			geneticAlgorithm(1000, 1, 2, 5);
		}
		else if (option == 5) {
			geneticAlgorithm(1000, 2, 3, 3);
		}
		else if (option == 6) {

			int numberOfGenerations;
			printf("number of generations: ");
			scanf("%d", &numberOfGenerations);

			int nominator;
			printf("division rivals - nominator: ");
			scanf("%d", &nominator);

			int denominator;
			printf("division rivals - denominator: ");
			scanf("%d", &denominator);

			int frequencyOverwritingFromPopulation;
			printf("frequency overwriting from population: ");
			scanf("%d", &frequencyOverwritingFromPopulation);

			geneticAlgorithm(numberOfGenerations, nominator, denominator, frequencyOverwritingFromPopulation);
		}
	}

	printf("\nPress enter to continue...\n");
	getchar();
	getchar();
	return 0;
}