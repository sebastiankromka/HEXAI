#ifndef _GENETICALGORITHM_H_
#define _GENETICALGORITHM_H_

void selection(int *population[], int populationSize) {
	for (int belowIndex = populationSize / 2; belowIndex < populationSize; belowIndex++) {
		for (int aboveIndex = 0; aboveIndex < populationSize / 2; aboveIndex++) {
			if (population[belowIndex][numberOfPointsTypes] > population[aboveIndex][numberOfPointsTypes]) {
				swapArrays(population[belowIndex], population[aboveIndex]);
				aboveIndex = -1;
			}
		}
	}
}

void crossover(int *population[], int populationSize) {
	int **tempArrayOfArrays = allocate2D(populationSize / 2, numberOfPointsTypes + 1);
	for (int test = 0; test < populationSize / 2; test++) {
		overwriteArray(population[test], tempArrayOfArrays[test]);
	}
	int parrent2;
	for (int parrent1 = 0; parrent1 < populationSize / 2; parrent1++) {
		do {
			parrent2 = rand() % (populationSize / 2);
		} while (parrent1 == parrent2);
		for (int point = 0; point < numberOfPointsTypes; point++) {
			if (rand() % 2 == 0) {
				population[parrent1 + populationSize / 2][point] = tempArrayOfArrays[parrent1][point];
				population[parrent1][point] = tempArrayOfArrays[parrent1][point];
			}
			else {
				population[parrent1 + populationSize / 2][point] = tempArrayOfArrays[parrent1][point];
				population[parrent1][point] = tempArrayOfArrays[parrent2][point];
			}
			population[parrent1 + populationSize / 2][numberOfPointsTypes] = population[parrent1][numberOfPointsTypes] = 0;
		}
	}
	deallocate2D(tempArrayOfArrays, populationSize / 2);
}

void mutation(int *population[], int populationSize) {

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
				int randomAward = rand() % numberOfPointsTypes;
				int randomValue = rand() % maxPointValue;
				population[tested][randomAward] = randomValue;
				population[tested][numberOfPointsTypes] = randomAward + 1;
				break;
			}
		}
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

void geneticAlgorithm(int numberOfGenerations, int boardSize, int populationSize, int rivalsSize, int copyToRivals, int frequencyCopyToRivals, int randomRivals, int *arrayOfPaths[]) {

	// basic validation
	if (boardSize < 4 || boardSize > 8 || copyToRivals > populationSize || copyToRivals + randomRivals > rivalsSize || (copyToRivals != 0 && frequencyCopyToRivals == 0) || (copyToRivals == 0 && frequencyCopyToRivals != 0)) {
		printf("check conditions: boardSize < 4 || boardSize > 6 || copyToRivals > populationSize || copyToRivals + randomRivals > rivalsSize || (copyToRivals != 0 && frequencyCopyToRivals == 0) || (copyToRivals == 0 && frequencyCopyToRivals != 0)");
		return;
	}

	// LOG
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

	// randomize if file not exists
	if (populationFile == NULL) {
		for (int p = 0; p < populationSize; p++) {
			for (int a = 0; a < numberOfPointsTypes; a++) {
				population[p][a] = rand() % maxPointValue;
			}
		}
	}
	// load from file if exists
	else {
		for (int p = 0; p < populationSize; p++) {
			for (int a = 0; a < numberOfPointsTypes; a++) {
				fscanf(populationFile, "%d", &population[p][a]);
			}
		}
		fclose(populationFile);
	}

	// INITIALIZTION RIVALS
	int **rivals = allocate2D(rivalsSize, numberOfPointsTypes + 1);
	char rivalsPath[] = "rivals.txt";
	FILE *rivalsFile = fopen(rivalsPath, "r");
	if (rivalsFile == NULL) {
		for (int r = 0; r < rivalsSize; r++) {
			for (int a = 0; a < numberOfPointsTypes; a++) {
				rivals[r][a] = rand() % maxPointValue;
			}
		}
	}
	else {
		for (int p = 0; p < populationSize; p++) {
			for (int a = 0; a < numberOfPointsTypes; a++) {
				fscanf(rivalsFile, "%d", &rivals[p][a]);
			}
		}
		fclose(rivalsFile);
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

		for (int p = 0; p < populationSize; p++) {

			population[p][numberOfPointsTypes] = 0; // clean previous result

			for (int r = 0; r < rivalsSize; r++) { // play with all rivals

				// 1) GAME
				int result = gameAIvsAI(player1, 0, boardSize, arrayOfPaths, population[p], rivals[r]); // plus result
				result -= gameAIvsAI(player1, 0, boardSize, arrayOfPaths, rivals[r], population[p]); // minus rieval result 

				 // LOG
				fprintf(defaultLogFile, "%d ", result);
				printf("%d ", result);

				// UPDATE RESULTS
				population[p][numberOfPointsTypes] += result; // add result
				rivals[r][numberOfPointsTypes] -= result; // minus because it's rival
			}

			// LOG
			fprintf(defaultLogFile, "\n");
			printf("\n");

		}

		// LOG
		fprintf(defaultLogFile, "\npopulation results\n");
		printf("\npopulation results\n");
		printPopulation(population, populationSize, numberOfPointsTypes + 1, 1, defaultLogFile);

		// 2) SELECTION
		selection(population, populationSize);

		printf("after selection\n");
		fprintf(defaultLogFile, "after selection\n");
		printPopulation(population, populationSize, numberOfPointsTypes + 1, 1, defaultLogFile);

		// UPDATE RIVALS
		if (copyToRivals != 0 && generation % frequencyCopyToRivals == 0) {
			printf("copy from population to rivals: ");
			fprintf(defaultLogFile, "copy from population to rivals: ");
			for (int p = 0; p < copyToRivals; p++) {
				printf("%d ", p + 1);
				fprintf(defaultLogFile, "%d ", p + 1);
				overwriteArray(population[p], rivals[p]);
			}
			printf("\n\n");
			fprintf(defaultLogFile, "\n\n");
		}
		if (randomRivals > 0) {
			printf("randomize rivals: ");
			fprintf(defaultLogFile, "randomize rivals: ");
			for (int p = copyToRivals; p < copyToRivals + randomRivals; p++) {
				printf("%d ", p + 1);
				fprintf(defaultLogFile, "%d ", p + 1);
				for (int a = 0; a < numberOfPointsTypes; a++) {
					rivals[p][a] = rand() % maxPointValue;
				}
			}
			printf("\n\n");
			fprintf(defaultLogFile, "\n\n");
		}

		// SAVE BEST UNITS
		bestUnitsFile = fopen(bestUnitsPath, "w");
		saveBestUnits(population, populationSize, bestUnitsFile);
		fclose(bestUnitsFile);

		// 3) CROSSOVER
		crossover(population, populationSize);

		printf("after crossover\n");
		fprintf(defaultLogFile, "after crossover\n");
		printPopulation(population, populationSize, numberOfPointsTypes, 0, defaultLogFile);

		// 4) MUTATION
		mutation(population, populationSize);

		printf("after mutation\n");
		fprintf(defaultLogFile, "after mutation\n");
		printPopulation(population, populationSize, numberOfPointsTypes + 1, 1, defaultLogFile);

		// SAVE RESULTS TO FILE
		populationFile = fopen(populationPath, "w");
		rivalsFile = fopen(rivalsPath, "w");
		saveResults(population, rivals, populationSize, rivalsSize, populationFile, rivalsFile);
		fclose(populationFile);
		fclose(rivalsFile);

		// LOG
		printf("rivals\n");
		fprintf(defaultLogFile, "rivals\n");
		printPopulation(rivals, rivalsSize, numberOfPointsTypes, 0, defaultLogFile);
		fclose(defaultLogFile);
	}

	deallocate2D(population, populationSize);
	deallocate2D(rivals, rivalsSize);
}

#endif