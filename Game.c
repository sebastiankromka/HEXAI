#include <time.h>
#include <stdio.h>
#include "Configuration.h"
#include "Output.h"
#include "OperationsOnArrays.h"
#include "HEX.h"
#include "CheckState.h"
#include "MinMax.h"
#include "geneticAlgorithm.h"

int main() {

	int awards[numberOfAwards] = { 999, 100, 200, 100, 200, 30, 20, 10 };
	gameAI1vsHuman(awards, AI1, 1);

	//geneticAlgorithm();

	getchar();
	getchar();
	return 0;
}