#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_

#define board_size 4
int board[board_size][board_size] = { { 2, 2, 1, 2 },
									  { 1, 1, 1, 2 },
									  { 2, 2, 1, 1 },
									  { 2, 0, 0, 1 } };

#define infoLevel  3

#define firstPlayer player_2

#define maxDepth 6

#define lossOfPointsForDepth 1
#define winScore 50


#endif