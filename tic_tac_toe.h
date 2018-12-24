#ifndef __TICTACTOE__
#define __TICTACTOE__

#include <stdio.h>
#include <stdlib.h>

void newGame();
void printToScreen();
int getMove();
int updateBoard(int move, int player);
int doTurn();
int playAgain();
int checkBoard();
void playGame();



extern char board[3][3];
extern int turn;


#endif