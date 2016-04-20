#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_

#define board_size 4
int board[board_size][board_size] = { { 1, 1, 2, 1 },
{ 1, 1, 2, 0 },
{ 1, 1, 0, 0 },
{ 1, 0, 0, 2 } };

#define printFullResult  0

#define firstPlayer player_2

#define maxDepth 6

#define lossOfPointsForDepth 1
#define winScore 50


#endif