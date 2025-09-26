#pragma once
#include<iostream>
using namespace std;
// copy the current state
int** checkBoard(int**, int);
// check for a valid move
bool checkMove(int**, int**, int n);
// check if there are any empty cells
bool checkZero(int**, int);
// check if the game is over
bool checkGameOver(int**, int);
// check if the game is won
bool isWinGame(int**, int);