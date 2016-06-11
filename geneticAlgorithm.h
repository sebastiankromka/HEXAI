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
	
	char logPath[] = "geneticAlgorithm_n_N_d_D_o_O.log";
	logPath[19] = nominator + '0';
	logPath[23] = denominator + '0';
	logPath[27] = frequencyOverwritingFromPopulation + '0';
	FILE *f = fopen(logPath, "r");
	if (f == NULL)
	{
		printf("log file exists");
		return;
	}
	fclose(f);
	f = fopen(logPath, "w");
	srand(time(NULL));

	// INITIALIZTION
	// TODO load from file
	int population[populationSize][numberOfAwards + 1] = { 0 }; // + 1 for results
	for (int p = 0; p < populationSize; p++) {
		for (int a = 0; a < numberOfAwards; a++) {
			population[p][a] = rand() % maxAwardValue;
		}
	}
	int rivals[rivalsSize][numberOfAwards + 1] = { 0 };
	for (int r = 0; r < rivalsSize; r++) {
		for (int a = 0; a < numberOfAwards; a++) {
			rivals[r][a] = rand() % maxAwardValue;
		}
	}

	// LOG
	fprintf(f, "------------------------------------------------------\n\nstarting values\n\n");
	printALLAwards(population, f);
	fprintf(f, "\n");
	printf("\n");
	printALLRivals(rivals, f);
	fprintf(f, "\n");
	printf("\n");
	fclose(f);

	for (int generation = 1; generation <= numberOfGenerations; generation++) {

		// LOG
		f = fopen(logPath, "a");
		fprintf(f, "------------------------------------------------------\n\ngeneration %d\n\n", generation);
		printf("------------------------------------------------------\n\ngeneration %d\n\n", generation);

		for (int r = 0; r < rivalsSize; r++) { // clean previous results
			rivals[r][numberOfAwards] = 0;
		}

		for (int p = 0; p < populationSize; p++) {

			population[p][numberOfAwards] = 0; // clean previous result

			for (int r = 0; r < rivalsSize; r++) { // play with all rivals

				// GAME
				int result = gameAI1vsAI2(population[p], rivals[r], AI1, 0); // plus result
				result -= gameAI1vsAI2(rivals[r], population[p], AI1, 0); // minus rieval result 

				// LOG
				fprintf(f, "%d ", result);
				printf("%d ", result);

				// UPDATE RESULTS
				population[p][numberOfAwards] += result; // add result
				rivals[r][numberOfAwards] -= result; // minus because it's rival
			}

			// LOG
			fprintf(f, "\n");
			printf("\n");

		}

		// LOG
		fprintf(f, "\n");
		printf("\n");
		printALLAwards(population, f);
		fprintf(f, "\n");
		printf("\n");
		printALLRivals(rivals, f);
		fprintf(f, "\n");
		printf("\n");

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

		crossover(population);

		mutation(population);

		// LOG
		fclose(f);
	}
}

#endif