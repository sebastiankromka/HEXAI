#ifndef _OPERATIONSONARRAYS_H_
#define _OPERATIONSONARRAYS_H_


int overwriteArray(int destination[numberOfAwards + 1], int source[numberOfAwards + 1]) {
	for (int a = 0; a <= numberOfAwards; a++) {
		destination[a] = source[a];
	}
}

int swapArrays(int array1[numberOfAwards + 1], int array2[numberOfAwards + 1]) {
	int arraytmp[numberOfAwards + 1];
	overwriteArray(arraytmp, array1);
	overwriteArray(array1, array2);
	overwriteArray(array2, arraytmp);
}

#endif