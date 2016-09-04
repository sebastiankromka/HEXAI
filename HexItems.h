#ifndef _HEXITEMS_H_
#define _HEXITEMS_H_

int getNodeState(int *board[], int boardSize, int x, int y) {
	if (x < 0 || y < 0 || x > boardSize - 1 || y > boardSize - 1) {
		return outOfBoardNode;
	}
	else {
		return board[x][y];
	}
}

void addNewLevel(int *board[], int boardSize, int x, int depth, int items[maxDepth][numberOfItemsTypes]) {
	int y, xCount = 0;
	for (y = 0; y < boardSize; y++) {
		if (board[x][y] == player1) {
			xCount++;
		}
	}
	if (xCount == 1) {
		items[depth][newLevel] = 1;
	}
}

int getDisjointStepWaysNumber(int *board[], int boardSize, int x, int y) {
	int number = 0;


	return number;
}

void addDisjointStep(int *board[], int boardSize, int x, int y, int depth, int items[maxDepth][numberOfItemsTypes]) {
	// check ways

	// if > 2 add and return

	// if 1 then check neighbor
}

void addBridges(int *board[], int boardSize, int x, int y, int depth, int items[maxDepth][numberOfItemsTypes]) {
	// bridge A1
	if (getNodeState(board, boardSize, x - 2, y + 1) == player1 && getNodeState(board, boardSize, x - 1, y) == freeNode && getNodeState(board, boardSize, x - 1, y + 1) == freeNode) {
		items[depth][bridgeA1] = 1;
	}
	// bridge A1 wall
	if (x == 1 && getNodeState(board, boardSize, 0, y) == freeNode && getNodeState(board, boardSize, 0, y + 1) == freeNode) {
		items[depth][bridgeA1wall] = 1;
	}
	// bridge A2
	if (getNodeState(board, boardSize, x + 2, y - 1) == player1 && getNodeState(board, boardSize, x + 1, y) == freeNode && getNodeState(board, boardSize, x + 1, y - 1) == freeNode) {
		items[depth][bridgeA2] = 1;
	}
	// bridge A2 wall
	if (x == boardSize - 2 && getNodeState(board, boardSize, boardSize - 1, y - 1) == freeNode && getNodeState(board, boardSize, boardSize - 1, y) == freeNode) {
		items[depth][bridgeA2wall] = 1;
	}
	// bridge B1
	if (getNodeState(board, boardSize, x - 1, y + 2) == player1 && getNodeState(board, boardSize, x - 1, y + 1) == freeNode && getNodeState(board, boardSize, x, y + 1) == freeNode) {
		items[depth][bridgeB1] = 1;
	}
	// bridge B2
	if (getNodeState(board, boardSize, x + 1, y - 2) == player1 && getNodeState(board, boardSize, x, y - 1) == freeNode && getNodeState(board, boardSize, x + 1, y - 1) == freeNode) {
		items[depth][bridgeB2] = 1;
	}
	// bridge C1
	if (getNodeState(board, boardSize, x + 1, y + 1) == player1 && getNodeState(board, boardSize, x, y + 1) == freeNode && getNodeState(board, boardSize, x + 1, y) == freeNode) {
		items[depth][bridgeC1] = 1;
	}
	// bridge C2
	if (getNodeState(board, boardSize, x - 1, y - 1) == player1 && getNodeState(board, boardSize, x, y - 1) == freeNode && getNodeState(board, boardSize, x - 1, y) == freeNode) {
		items[depth][bridgeC2] = 1;
	}
}

void addItems(int *board[], int boardSize, int x, int y, int depth, int items[maxDepth][numberOfItemsTypes]){
	addBridges(board, boardSize, x, y, depth, items);
	//addDisjointStep(board, boardSize, x, y, depth, items);
	addNewLevel(board, boardSize, x, depth, items);
}

int getScore(int items[maxDepth][numberOfItemsTypes], int points[numberOfPointsTypes]) {
	int score = 0, tmpScore, d, i;
	for (d = 0; d < maxDepth && items[d][stonesInBestChain] > 0; d++) {
		tmpScore = -items[d][stonesInBestChain] * points[stonesInBestChain];
		for (i = 1; i < numberOfItemsTypes - 2; i++) { // 1 stonesInBestChain // -2 xPosition, yPosition)
			tmpScore += items[d][i] * points[i];
		}
		tmpScore = tmpScore * (100 - points[lossOfPointsForDepthInPercent] * d) / 100;
		if (d % 2 == 1) { // AI2 best move
			tmpScore = -tmpScore;
		}
		score += tmpScore;
	}
	return score;
}

#endif