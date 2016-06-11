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

	printf("1 - AI vs human log=2\n1 - AI vs human log=3\n3 - AI1 vs AI2 log=1\n4 - genetic algorithm log=0\n");
	int option;
	scanf("%d", &option);
	//option = 1;
	if (option == 1) {
		int awards1[numberOfAwards] = { 800, 50, 50, 2, 1, 3, 2, 1, 5, 1 };
		gameAIvsHuman(awards1, AI1, 1, 2);
	}
	else if (option == 2) {
		int awards1[numberOfAwards] = { 800, 50, 50, 2, 1, 3, 2, 1, 5, 1 };
		gameAIvsHuman(awards1, AI2, 1, 3);
	}
	else if (option == 3) {
		int awards1[numberOfAwards] = { 800, 300, 100, 50, 10, 35, 20, 10, 10, 1 };
		int awards2[numberOfAwards] = { 800, 300, 100, 50, 10, 35, 20, 10, 10, 1 };
		gameAI1vsAI2(awards1, awards2, AI1, 1);
	}
	else if (option == 4) {
		geneticAlgorithm();
	}

	

	printf("\nPress enter to continue...\n");
	getchar();
	getchar();
	return 0;
}