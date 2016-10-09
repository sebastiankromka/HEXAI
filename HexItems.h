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

void addDisjointStep(int *board[], int boardSize, int x, int y, int depth, int items[maxDepth][numberOfItemsTypes]) {
	int checkedID = 0;
	int joint = 0;
	/*// stones map
	//   1 2
	// 6 c 3
	// 5 4
	// 1
	if (getNodeState(board, boardSize, x - 1, y) == player1) {
		return;
	}
	// 2
	if (getNodeState(board, boardSize, x - 1, y + 1) == player1) {
		return;
	}
	// 3
	if (getNodeState(board, boardSize, x, y + 1) == player1) {
		return;
	}
	// 4
	if (getNodeState(board, boardSize, x + 1, y) == player1) {
		return;
	}
	// 5
	if (getNodeState(board, boardSize, x + 1, y - 1) == player1) {
		return;
	}
	// 6
	if (getNodeState(board, boardSize, x, y - 1) == player1) {
		return;
	}*/


	// stones map
	//      1 2 3
	//   12 0 0 4
	// 11 0 c 0 5
	// 10 0 0 6
	//  9 8 7
	// 1
	if (getNodeState(board, boardSize, x - 2, y) == player1 && getNodeState(board, boardSize, x - 1, y) == freeNode) {
		joint++;
		checkedID = 1;
	}
	// 2
	if (checkedID != 1 && getNodeState(board, boardSize, x - 2, y + 1) == player1 && (getNodeState(board, boardSize, x - 1, y) == freeNode || getNodeState(board, boardSize, x - 1, y + 1) == freeNode)) {
		joint++;
		checkedID = 2;
	}
	// 3
	if (checkedID != 2 && getNodeState(board, boardSize, x - 2, y + 2) == player1 && getNodeState(board, boardSize, x - 1, y + 1) == freeNode) {
		joint++;
		checkedID = 3;
	}
	// 4
	if (checkedID != 3 && getNodeState(board, boardSize, x - 1, y + 2) == player1 && (getNodeState(board, boardSize, x - 1, y + 1) == freeNode || getNodeState(board, boardSize, x, y + 1) == freeNode)) {
		joint++;
		checkedID = 4;
	}
	// 5
	if (checkedID != 4 && getNodeState(board, boardSize, x, y + 2) == player1 && getNodeState(board, boardSize, x, y + 1) == freeNode) {
		joint++;
		checkedID = 5;
	}
	// 6
	if (checkedID != 5 && getNodeState(board, boardSize, x + 1, y + 1) == player1 && (getNodeState(board, boardSize, x, y + 1) == freeNode || getNodeState(board, boardSize, x + 1, y) == freeNode)) {
		joint++;
		checkedID = 6;
	}
	// 7
	if (checkedID != 6 && getNodeState(board, boardSize, x + 2, y) == player1 && getNodeState(board, boardSize, x + 1, y) == freeNode) {
		joint++;
		checkedID = 7;
	}
	// 8
	if (checkedID != 7 && getNodeState(board, boardSize, x + 2, y - 1) == player1 && (getNodeState(board, boardSize, x + 1, y) == freeNode || getNodeState(board, boardSize, x + 1, y - 1) == freeNode)) {
		joint++;
		checkedID = 8;
	}
	// 9
	if (checkedID != 8 && getNodeState(board, boardSize, x + 2, y - 2) == player1 && getNodeState(board, boardSize, x + 1, y - 1) == freeNode) {
		joint++;
		checkedID = 9;
	}
	// 10
	if (checkedID != 9 && getNodeState(board, boardSize, x + 1, y - 2) == player1 && (getNodeState(board, boardSize, x + 1, y - 1) == freeNode || getNodeState(board, boardSize, x, y - 1) == freeNode)) {
		joint++;
		checkedID = 10;
	}
	// 11
	if (checkedID != 10 && getNodeState(board, boardSize, x, y - 2) == player1 && getNodeState(board, boardSize, x, y - 1) == freeNode) {
		joint++;

		checkedID = 11;
	}
	// 12
	if (checkedID != 11 && checkedID != 1 && getNodeState(board, boardSize, x - 1, y - 1) == player1 && (getNodeState(board, boardSize, x, y - 1) == freeNode || getNodeState(board, boardSize, x - 1, y) == freeNode)) {
		joint++;
	}
	if (joint > 1) {
		items[depth][disjointStep] = 1;
	}
}

void addBridges(int *board[], int boardSize, int x, int y, int depth, int items[maxDepth][numberOfItemsTypes]) {
	// bridge A1
	if (getNodeState(board, boardSize, x - 2, y + 1) == player1 && getNodeState(board, boardSize, x - 1, y) == freeNode && getNodeState(board, boardSize, x - 1, y + 1) == freeNode) {
		items[depth][bridgeA] = 1;
	}
	// bridge A1 wall
	if (x == 1 && getNodeState(board, boardSize, 0, y) == freeNode && getNodeState(board, boardSize, 0, y + 1) == freeNode) {
		items[depth][bridgeAwall] = 1;
	}
	// bridge A2
	if (getNodeState(board, boardSize, x + 2, y - 1) == player1 && getNodeState(board, boardSize, x + 1, y) == freeNode && getNodeState(board, boardSize, x + 1, y - 1) == freeNode) {
		items[depth][bridgeA] = 1;
	}
	// bridge A2 wall
	if (x == boardSize - 2 && getNodeState(board, boardSize, boardSize - 1, y - 1) == freeNode && getNodeState(board, boardSize, boardSize - 1, y) == freeNode) {
		items[depth][bridgeAwall] = 1;
	}
	// bridge B1
	if (getNodeState(board, boardSize, x - 1, y + 2) == player1 && getNodeState(board, boardSize, x - 1, y + 1) == freeNode && getNodeState(board, boardSize, x, y + 1) == freeNode) {
		items[depth][bridgeB] = 1;
	}
	// bridge B2
	if (getNodeState(board, boardSize, x + 1, y - 2) == player1 && getNodeState(board, boardSize, x, y - 1) == freeNode && getNodeState(board, boardSize, x + 1, y - 1) == freeNode) {
		items[depth][bridgeB] = 1;
	}
	// bridge C1
	if (getNodeState(board, boardSize, x + 1, y + 1) == player1 && getNodeState(board, boardSize, x, y + 1) == freeNode && getNodeState(board, boardSize, x + 1, y) == freeNode) {
		items[depth][bridgeC] = 1;
	}
	// bridge C2
	if (getNodeState(board, boardSize, x - 1, y - 1) == player1 && getNodeState(board, boardSize, x, y - 1) == freeNode && getNodeState(board, boardSize, x - 1, y) == freeNode) {
		items[depth][bridgeC] = 1;
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
		tmpScore = items[d][levelsInBestChain] * points[levelsInBestChain] - items[d][stonesInBestChain] * points[stonesInBestChain];
		if (tmpScore < 0) {
			tmpScore = 0;
		}
		for (i = 2; i < numberOfItemsTypes - 2; i++) { // 0 stonesInBestChain 1 levelsInBestChain // -2 xPosition, yPosition)
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