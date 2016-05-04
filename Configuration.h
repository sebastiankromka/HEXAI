#ifndef _CONFIGURATION_H_
#define _CONFIGURATION_H_

#define board_size 8

/*int board[board_size][board_size] = { { 0, 1, 0, 0 },
									  { 0, 0, 0, 0 },
									  { 0, 0, 0, 2 },
									  { 0, 2, 0, 1 } };*/


int board[board_size][board_size] = { { 1, 1, 1, 1, 1, 1, 1, 2 },
{ 1, 2, 1, 2, 1, 2, 1, 2 },
{ 1, 2, 1, 3, 1, 2, 1, 0 },
{ 0, 2, 0, 0, 0, 0, 0, 0 },
{ 0, 0, 0, 0, 0, 0, 1, 0 },
{ 0, 2, 0, 0, 1, 0, 0, 0 },
{ 0, 0, 1, 0, 0, 0, 0, 0 },
{ 1, 2, 0, 0, 0, 0, 0, 0 } };
#define infoLevel 2

#define firstPlayer player_2

#define maxDepth 4

#define lossPercentsOfPointsForDepth 10
#define winScore 100
#define bridgeAScore 8
#define bridgeBScore 6


#endif