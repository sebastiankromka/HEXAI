#ifndef _GENETICALGORITHM_H_
#define _GENETICALGORITHM_H_

int selection(int population[populationSize][numberOfAwards + 1]) {
	for (int belowIndex = populationSize / 2; belowIndex < populationSize; belowIndex++) {
		for (int aboveIndex = 0; aboveIndex < populationSize / 2; aboveIndex++) {
			if (population[belowIndex][numberOfAwards] > population[aboveIndex][numberOfAwards]) {
				swapArrays(population[belowIndex], population[aboveIndex]);
				aboveIndex = 0;
			}
		}
	}
}

int crossover(int population[populationSize][numberOfAwards + 1]) {
	int tempArrayOfArrays[populationSize / 2][numberOfAwards + 1];
	for (int test = 0; test < populationSize / 2; test++) {
		overwriteArray(population[test], tempArrayOfArrays[test]);
	}
	int parrent2;
	for (int parrent1 = 0; parrent1 < populationSize / 2; parrent1++) {
		do {
			parrent2 = rand() % (populationSize / 2);
		} while (parrent1 == parrent2);
		for (int award = 0; award < numberOfAwards; award++) {
			if (rand() % 2 == 0) {
				population[parrent1 + populationSize / 2][award] = tempArrayOfArrays[parrent1][award];
				population[parrent1][award] = tempArrayOfArrays[parrent1][award];
			}
			else {
				population[parrent1 + populationSize / 2][award] = tempArrayOfArrays[parrent1][award];
				population[parrent1][award] = tempArrayOfArrays[parrent2][award];
			}
		}
	}
}

int mutation(int population[populationSize][numberOfAwards + 1]) {

	for (int tested = 0; tested < populationSize; tested++) {
		
		for (int compared = tested + 1; compared < populationSize; compared++) {

			int needMutation = 1;

			for (int a = 0; a < numberOfAwards; a++) {
				if (population[tested][a] != population[compared][a]) {
					needMutation = 0;
					break;
				}
			}

			if (needMutation == 1) {
				int randomAward = rand() % numberOfAwards;
				int randomValue = rand() % maxAwardValue;
				population[tested][randomAward] = randomValue;
				break;
			}
		}
	}
}

void addTheBestFromPopulationToRivals(int population[populationSize][numberOfAwards + 1], int rivals[rivalsSize][numberOfAwards + 1], int rivalNumber) {
	int theBestFromPopulation = 0;
	for (int p = 1; p < populationSize; p++) {
		if (population[p][numberOfAwards] > population[theBestFromPopulation][numberOfAwards]) {
			theBestFromPopulation = p;
		}
	}
	overwriteArray(population[theBestFromPopulation], rivals[rivalNumber]);
}

int geneticAlgorithm(int numberOfGenerations, int nominator, int denominator, int frequencyOverwritingFromPopulation) {

	// basic validation
	if (numberOfGenerations < 1 || nominator < 0 || denominator < 1 || frequencyOverwritingFromPopulation < 0) {
		return;
	}
	
	// LOG
	char bestUnitsPath[] = "bestUnits.txt";
	FILE *bestUnitsFile;
	char defaultLogPath[] = "geneticAlgorithm_n_N_d_D_o_O.log";
	defaultLogPath[19] = nominator + '0';
	defaultLogPath[23] = denominator + '0';
	defaultLogPath[27] = frequencyOverwritingFromPopulation + '0';
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
	int population[populationSize][numberOfAwards + 1] = { 0 }; // + 1 for results
	char populationPath[] = "population.txt";
	FILE *populationFile = fopen(populationPath, "r");
	if (populationFile == NULL) {
		for (int p = 0; p < populationSize; p++) {
			for (int a = 0; a < numberOfAwards; a++) {
				population[p][a] = rand() % maxAwardValue;
			}
		}
	}
	else {
		for (int p = 0; p < populationSize; p++) {
			for (int a = 0; a < numberOfAwards; a++) {
				fscanf(populationFile, "%d", &population[p][a]);
			}
		}
		fclose(populationFile);
	}

	// INITIALIZTION RIVALS
	int rivals[rivalsSize][numberOfAwards + 1] = { 0 };
	char rivalsPath[] = "rivals.txt";
	FILE *rivalsFile = fopen(rivalsPath, "r");
	if (rivalsFile == NULL) {
		for (int r = 0; r < rivalsSize; r++) {
			for (int a = 0; a < numberOfAwards; a++) {
				rivals[r][a] = rand() % maxAwardValue;
			}
		}
	}
	else {
		for (int p = 0; p < populationSize; p++) {
			for (int a = 0; a < numberOfAwards; a++) {
				fscanf(rivalsFile, "%d", &rivals[p][a]);
			}
		}
		fclose(rivalsFile);
	}

	// LOG
	fprintf(defaultLogFile, "------------------------------------------------------\n\nstarting values\n\n");
	printALLAwards(population, defaultLogFile);
	fprintf(defaultLogFile, "\n");
	printf("\n");
	printALLRivals(rivals, defaultLogFile);
	fprintf(defaultLogFile, "\n");
	printf("\n");
	fclose(defaultLogFile);

	for (int generation = 1; generation <= numberOfGenerations; generation++) {

		// LOG
		defaultLogFile = fopen(defaultLogPath, "a");
		fprintf(defaultLogFile, "------------------------------------------------------\n\ngeneration %d\n\n", generation);
		printf("------------------------------------------------------\n\ngeneration %d\n\n", generation);

		for (int r = 0; r < rivalsSize; r++) { // clean previous results
			rivals[r][numberOfAwards] = 0;
		}

		for (int p = 0; p < populationSize; p++) {

			population[p][numberOfAwards] = 0; // clean previous result

			for (int r = 0; r < rivalsSize; r++) { // play with all rivals

				// 1) GAME
				int result = gameAI1vsAI2(population[p], rivals[r], AI1, 0); // plus result
				result -= gameAI1vsAI2(rivals[r], population[p], AI1, 0); // minus rieval result 

				// LOG
				fprintf(defaultLogFile, "%d ", result);
				printf("%d ", result);

				// UPDATE RESULTS
				population[p][numberOfAwards] += result; // add result
				rivals[r][numberOfAwards] -= result; // minus because it's rival
			}

			// LOG
			fprintf(defaultLogFile, "\n");
			printf("\n");

		}

		// LOG
		fprintf(defaultLogFile, "\n");
		printf("\n");
		printALLAwards(population, defaultLogFile);
		fprintf(defaultLogFile, "\n");
		printf("\n");
		printALLRivals(rivals, defaultLogFile);
		fprintf(defaultLogFile, "\n");
		printf("\n");

		// 2) SELECTION
		selection(population);

		// UPDATE RIVALS
		for (int p = 0; p < (rivalsSize + 1) * nominator / denominator; p++) { // random
			for (int a = 0; a < numberOfAwards; a++) {
				rivals[p][a] = rand() % maxAwardValue;
			}
		}
		if (frequencyOverwritingFromPopulation != 0 && generation % frequencyOverwritingFromPopulation == 0) { // from poluation
			for (int p = (rivalsSize + 1) * nominator / denominator; p < rivalsSize; p++) {
				overwriteArray(population[p], rivals[p]);
			}
		}

		// SAVE BEST UNITS
		bestUnitsFile = fopen(bestUnitsPath, "w");
		saveBestUnits(population, bestUnitsFile);
		fclose(bestUnitsFile);

		// 3) CROSSOVER
		crossover(population);

		// 4) MUTATION
		mutation(population);

		// SAVE RESULTS TO FILE
		populationFile = fopen(populationPath, "w");
		rivalsFile = fopen(rivalsPath, "w");
		saveResults(population, rivals, populationFile, rivalsFile);
		fclose(populationFile);
		fclose(rivalsFile);

		// LOG
		fprintf(defaultLogFile, "results are saved\n");
		fclose(defaultLogFile);
	}
}

#endif