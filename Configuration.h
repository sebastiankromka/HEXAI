#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_

#define free 0
#define AI1 1
#define AI2 2

#define noWinner 0
#define checked 4

#define boardSize 5
#define longestPathBoardSize 100000
int longestPathArray[longestPathBoardSize][boardSize + 1] = { { 0 } };
int currentPath;

#define populationSize 10
#define rivalsSize 10

#define maxDepth 2

#define numberOfAwards 10
#define maxAwardValue 1000

#define awardForWin 0
#define lossOfAwardForDepthInPercent 1
#define awardForBridgeA 2
#define awardForBridgeB 3
#define awardForBridgeC 4
#define awardForNeighborA 5
#define awardForNeighborB 6
#define awardForNeighborC 7

#define awardForLevel 8
#define lossOfAwardForPawns 9



#endif