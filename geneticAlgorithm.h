#ifndef _GENETICALGORITHM_H_
#define _GENETICALGORITHM_H_

void selection(int *population[], int populationSize) {
	int **tempArrayOfArrays = allocate2D(populationSize, numberOfPointsTypes + 1);
	int bestUnit = 0;
	int unit1, unit2;
	for (int i = 0; i < populationSize; i++) {
		overwriteArray(population[i], tempArrayOfArrays[i]);
	}
	for (int i = 1; i < populationSize; i++) {
		if (population[i][numberOfPointsTypes] > population[bestUnit][numberOfPointsTypes]) {
			bestUnit = i;
		}
	}
	// first is the best unit
	overwriteArray(population[bestUnit], population[0]);
	for (int i = 1; i < populationSize; i++) {
		unit1 = rand() % populationSize;
		do {
			unit2 = rand() % populationSize;
		} while (unit1 == unit2);
		if (tempArrayOfArrays[unit1][numberOfPointsTypes] > tempArrayOfArrays[unit2][numberOfPointsTypes]) {
			overwriteArray(tempArrayOfArrays[unit1], population[i]);
		}
		else {
			overwriteArray(tempArrayOfArrays[unit2], population[i]);
		}
	}
	deallocate2D(tempArrayOfArrays, populationSize);
}

void crossover(int *population[], int populationSize) {
	int **tempArrayOfArrays = allocate2D(populationSize, numberOfPointsTypes + 1);
	int k, tmp;
	for (int i = 1; i < populationSize; i++) {
		swapArrays(population[i], population[(rand() % (populationSize - 1)) + 1]);
	}
	for (int i = 1; i < populationSize - 1; i = i + 2) {
		k = (rand() % (numberOfPointsTypes - 2)) + 1;
		for (int j = k; j < numberOfPointsTypes; j++) {
			tmp = population[i][j];
			population[i][j] = population[i + 1][j];
			population[i + 1][j] = tmp;
		}
	}
	deallocate2D(tempArrayOfArrays, populationSize);
}

void mutation(int *population[], int populationSize, FILE *f, FILE *f2) {
	int tmp = 0;

	for (int tested = 0; tested < populationSize; tested++) {

		for (int compared = tested + 1; compared < populationSize; compared++) {

			int needMutation = 1;

			for (int a = 0; a < numberOfPointsTypes; a++) {
				if (population[tested][a] != population[compared][a]) {
					needMutation = 0;
					break;
				}
			}

			if (needMutation == 1) {
				tmp++;
				int randomPoint = rand() % numberOfPointsTypes;
				int randomValue;

				if (randomPoint == stonesInBestChain) {
					randomValue = rand() % maxPointValueStonesInBestChain;
				}
				else if (randomPoint == lossOfPointsForDepthInPercent) {
					randomValue = (rand() % (maxPointValueLossOfPointsForDepthInPercent - minPointValueLossOfPointsForDepthInPercent)) - minPointValueLossOfPointsForDepthInPercent;
				}
				else {
					randomValue = rand() % maxPointValue;
				}

				population[tested][randomPoint] = randomValue;

				fprintf(f, "mutation: genotype %d, gene %d\n", tested + 1, randomPoint + 1);
				printf("mutation: genotype %d, gene %d\n", tested + 1, randomPoint + 1);
				for (int y = 0; y < numberOfPointsTypes; y++) {
					if (y == randomPoint) {
						fprintf(f, "(%d) ", population[tested][y]);
						printf("(%d) ", population[tested][y]);
					}
					else {
						fprintf(f, "%d ", population[tested][y]);
						printf("%d ", population[tested][y]);
					}
				}
				fprintf(f, "\n\n");
				printf("\n\n");

				break;
			}
		}
	}
	if (tmp != 0) {
		fprintf(f2, "mutations:%d\n", tmp);
	}
}

void addTheBestFromPopulationToRivals(int *population[], int *rivals[], int populationSize, int rivalNumber) {
	int theBestFromPopulation = 0;
	for (int p = 1; p < populationSize; p++) {
		if (population[p][numberOfPointsTypes] > population[theBestFromPopulation][numberOfPointsTypes]) {
			theBestFromPopulation = p;
		}
	}
	overwriteArray(population[theBestFromPopulation], rivals[rivalNumber]);
}

void randomizeRivalsOrder(int *rivalsOrder, int rivalsSize) {
	int tmp1, tmp2;
	for (int r = 0; r < rivalsSize; r++) {
		tmp1 = rivalsOrder[r];
		tmp2 = rand() % rivalsSize;
		rivalsOrder[r] = rivalsOrder[tmp2];
		rivalsOrder[tmp2] = tmp1;
	}
}

void geneticAlgorithm(int numberOfGenerations, int boardSize, int gamesInOneGeneration, int populationSize, int rivalsSize, int copyToRivals, int frequencyCopyToRivals, int randomRivals, int *arrayOfPaths[]) {

	// basic validation
	if (boardSize < 4 || boardSize > 8 || copyToRivals > populationSize || copyToRivals + randomRivals > rivalsSize || (copyToRivals != 0 && frequencyCopyToRivals == 0) || (copyToRivals == 0 && frequencyCopyToRivals != 0)) {
		printf("check conditions: boardSize < 4 || boardSize > 6 || copyToRivals > populationSize || copyToRivals + randomRivals > rivalsSize || (copyToRivals != 0 && frequencyCopyToRivals == 0) || (copyToRivals == 0 && frequencyCopyToRivals != 0)");
		return;
	}

	// LOG
	int resultsSum;
	char resultsLogPath[] = "results.txt";
	FILE *resultsLogFile;
	resultsLogFile = fopen(resultsLogPath, "w");
	fprintf(resultsLogFile, "board size: %d, population size: %d, rivals size: %d, copy to rivals: %d, frequency of copying to rivals: %d, random rivals: %d\n", boardSize, populationSize, rivalsSize, copyToRivals, frequencyCopyToRivals, randomRivals);
	fclose(resultsLogFile);
	char bestUnitsPath[] = "bestUnits.txt";
	FILE *bestUnitsFile;
	char defaultLogPath[] = "geneticAlgorithm.log";
	FILE *defaultLogFile = fopen(defaultLogPath, "r");
	if (defaultLogFile != NULL)
	{
		printf("log file exists");
		fclose(defaultLogFile);
		return;
	}
	defaultLogFile = fopen(defaultLogPath, "w");
	srand(time(NULL));

	// INITIALIZTION POPULATION
	int **population = allocate2D(populationSize, numberOfPointsTypes + 1); // + 1 for results
	char populationPath[] = "population.txt";
	FILE *populationFile = fopen(populationPath, "r");
	// randomize
	for (int p = 0; p < populationSize; p++) {
		population[p][stonesInBestChain] = rand() % maxPointValueStonesInBestChain;
		for (int a = 1; a < numberOfPointsTypes - 1; a++) {
			population[p][a] = rand() % maxPointValue;
		}
		population[p][lossOfPointsForDepthInPercent] = (rand() % (maxPointValueLossOfPointsForDepthInPercent - minPointValueLossOfPointsForDepthInPercent)) - minPointValueLossOfPointsForDepthInPercent;
	}
	// load from file if exists
	if (populationFile != NULL) {
		for (int p = 0; p < populationSize; p++) {
			for (int a = 0; a < numberOfPointsTypes; a++) {
				fscanf(populationFile, "%d ", &population[p][a]);
			}
		}
		fclose(populationFile);
	}

	// INITIALIZTION RIVALS
	int **rivals = allocate2D(rivalsSize, numberOfPointsTypes + 1);
	char rivalsPath[] = "rivals.txt";
	FILE *rivalsFile = fopen(rivalsPath, "r");
	for (int r = 0; r < rivalsSize; r++) {
		rivals[r][stonesInBestChain] = rand() % maxPointValueStonesInBestChain;
		for (int a = 1; a < numberOfPointsTypes - 1; a++) {
			rivals[r][a] = rand() % maxPointValue;
		}
		rivals[r][lossOfPointsForDepthInPercent] = (rand() % (maxPointValueLossOfPointsForDepthInPercent - minPointValueLossOfPointsForDepthInPercent)) - minPointValueLossOfPointsForDepthInPercent;
	}
	if (rivalsFile != NULL) {
		for (int p = 0; p < rivalsSize; p++) {
			for (int a = 0; a < numberOfPointsTypes; a++) {
				fscanf(rivalsFile, "%d ", &rivals[p][a]);
			}
		}
		fclose(rivalsFile);
	}
	int *rivalsOrder = malloc(rivalsSize * sizeof(int));
	for (int r = 0; r < rivalsSize; r++) {
		rivalsOrder[r] = r;
	}

	// LOG
	fprintf(defaultLogFile, "------------------------------------------------------\n");
	printf("------------------------------------------------------\n");
	fprintf(defaultLogFile, "starting values\n\n");
	printf("starting values\n\n");
	fprintf(defaultLogFile, "population:\n");
	printf("population:\n");
	printPopulation(population, populationSize, numberOfPointsTypes, 0, defaultLogFile);
	fprintf(defaultLogFile, "rivals:\n");
	printf("rivals:\n");
	printPopulation(rivals, rivalsSize, numberOfPointsTypes, 0, defaultLogFile);
	fclose(defaultLogFile);

	for (int generation = 1; generation <= numberOfGenerations; generation++) {

		// LOG
		defaultLogFile = fopen(defaultLogPath, "a");
		fprintf(defaultLogFile, "------------------------------------------------------\n");
		fprintf(defaultLogFile, "generation %d\n\nresults\n", generation);
		printf("--------------------------------------------------\n");
		printf("generation %d\n\nresults\n", generation);

		for (int r = 0; r < rivalsSize; r++) { // clean previous results
			rivals[r][numberOfPointsTypes] = 0;
		}
		resultsSum = 0;
		randomizeRivalsOrder(rivalsOrder, rivalsSize);

		for (int p = 0; p < populationSize; p++) {

			population[p][numberOfPointsTypes] = 0; // clean previous result

			for (int r = 0; r < gamesInOneGeneration; r++) {

				// 1) GAME
				int result = gameAIvsAI(player1, 0, boardSize, arrayOfPaths, population[p], rivals[rivalsOrder[r]]); // plus result
				result -= gameAIvsAI(player1, 0, boardSize, arrayOfPaths, rivals[rivalsOrder[r]], population[p]); // minus rieval result 
				resultsSum += result;

				 // LOG
				fprintf(defaultLogFile, "p%d vs r%d %d, ", p + 1, rivalsOrder[r] + 1, result);
				printf("p%d vs r%d %d, ", p + 1, rivalsOrder[r] + 1, result);

				// UPDATE RESULTS
				population[p][numberOfPointsTypes] += result; // add result
				rivals[r][numberOfPointsTypes] -= result; // minus because it's rival
			}

			// LOG
			fprintf(defaultLogFile, "\n");
			printf("\n");
		}

		// LOG
		resultsLogFile = fopen(resultsLogPath, "a");
		fprintf(defaultLogFile, "\nresults sum: %d\n\npopulation results\n", resultsSum);
		printf("\nresults sum: %d\n\npopulation results\n", resultsSum);
		fprintf(resultsLogFile, "\ngeneration:%d\nresult:%d\n", generation, resultsSum);
		printPopulation(population, populationSize, numberOfPointsTypes + 1, 1, defaultLogFile);

		// 2) SELECTION
		printf("selection\n");
		fprintf(defaultLogFile, "selection\n");
		selection(population, populationSize);
		printPopulation(population, populationSize, numberOfPointsTypes + 1, 1, defaultLogFile);

		// UPDATE RIVALS
		if (copyToRivals != 0 && generation % frequencyCopyToRivals == 0) {
			printf("copy from population to rivals: ");
			fprintf(defaultLogFile, "copy from population to rivals: ");
			fprintf(resultsLogFile, "copy\n");
			for (int p = 0; p < copyToRivals; p++) {
				printf("%d ", p + 1);
				fprintf(defaultLogFile, "%d ", p + 1);
				overwriteArray(population[p], rivals[p]);
			}
			printf("\n\n");
			fprintf(defaultLogFile, "\n\n");
		}

		// 3) CROSSOVER
		printf("crossover\n");
		fprintf(defaultLogFile, "crossover\n");
		crossover(population, populationSize);
		printPopulation(population, populationSize, numberOfPointsTypes, 0, defaultLogFile);

		// 4) MUTATION
		mutation(population, populationSize, defaultLogFile, resultsLogFile);

		// SAVE RESULTS TO FILE
		populationFile = fopen(populationPath, "w");
		rivalsFile = fopen(rivalsPath, "w");
		saveResults(population, rivals, populationSize, rivalsSize, populationFile, rivalsFile);
		fclose(populationFile);
		fclose(rivalsFile);

		// UPDATE RIVALS
		if (randomRivals > 0) {
			printf("randomize rivals: ");
			fprintf(defaultLogFile, "randomize rivals: ");
			for (int p = copyToRivals; p < copyToRivals + randomRivals; p++) {
				printf("%d ", p + 1);
				fprintf(defaultLogFile, "%d ", p + 1);
				rivals[p][stonesInBestChain] = rand() % maxPointValueStonesInBestChain;
				for (int a = 1; a < numberOfPointsTypes - 1; a++) {
					rivals[p][a] = rand() % maxPointValue;
				}
				rivals[p][lossOfPointsForDepthInPercent] = rand() % maxPointValueLossOfPointsForDepthInPercent;
			}
			printf("\n\n");
			fprintf(defaultLogFile, "\n\n");
		}
		printf("rivals\n");
		fprintf(defaultLogFile, "rivals\n");
		printPopulation(rivals, rivalsSize, numberOfPointsTypes, 0, defaultLogFile);

		// LOG
		fclose(resultsLogFile);
		fclose(defaultLogFile);
	}

	deallocate2D(population, populationSize);
	deallocate2D(rivals, rivalsSize);
	free(rivalsOrder);
}

#endif