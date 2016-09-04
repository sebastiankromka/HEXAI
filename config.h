#ifndef _CONFIG_H_
#define _CONFIG_H_

#define outOfBoardNode -1
#define freeNode 0
#define player1 1
#define player2 2
#define noWinner 0

#define arrayOfPathsSize 1000000

#define maxDepth 4

#define maxPointValue 1000

#define numberOfPointsTypes 13
#define stonesInBestChain 0
#define levelsInBestChain 1
#define win 2
#define newLevel 3
#define bridgeA1 4
#define bridgeA1wall 5
#define bridgeA2 6
#define bridgeA2wall 7
#define bridgeB1 8
#define bridgeB2 9
#define bridgeC1 10
#define bridgeC2 11
#define lossOfPointsForDepthInPercent 12

#define numberOfItemsTypes 14
char *namesOfItems[numberOfItemsTypes - 2] = {
	"stonesInBestChain",
	"levelsInBestChain",
	"win",
	"newLevel",
	"bridgeA1",
	"bridgeA1wall",
	"bridgeA2",
	"bridgeA2wall",
	"bridgeB1",
	"bridgeB2",
	"bridgeC1",
	"bridgeC2"
};
#define xPosition 12
#define yPosition 13

#endif