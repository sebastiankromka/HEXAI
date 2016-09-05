#ifndef _CONFIG_H_
#define _CONFIG_H_

#define outOfBoardNode -1
#define freeNode 0
#define player1 1
#define player2 2
#define noWinner 0

#define arrayOfPathsSize 1000000

#define maxDepth 4

#define maxPointValue 100
#define maxPointValueStonesInBestChain 40
#define maxPointValueLossOfPointsForDepthInPercent 25

#define numberOfPointsTypes 9
#define stonesInBestChain 0
#define levelsInBestChain 1
#define win 2
#define newLevel 3
#define bridgeA 4
#define bridgeAwall 5
#define bridgeB 6
#define bridgeC 7
#define lossOfPointsForDepthInPercent 8

#define numberOfItemsTypes 10
char *namesOfItems[numberOfItemsTypes - 2] = {
	"stonesInBestChain",
	"levelsInBestChain",
	"win",
	"newLevel",
	"bridgeA",
	"bridgeAwall",
	"bridgeB",
	"bridgeC",
};
#define xPosition 8
#define yPosition 9

#endif