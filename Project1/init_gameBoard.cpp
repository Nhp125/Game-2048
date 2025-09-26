#include<iostream>
#include"init_gameBoard.h"
#include<ctime>
#include<stdlib.h>
using namespace std;
void init_gameBoard(int**& gameBoard, int& n) {
	srand(time(NULL));
	for (int i = 0; i < n; i++) {
		gameBoard[i] = new int[n];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			gameBoard[i][j] = 0;
		}
	}
	for (int i = 0; i < 2; i++) {
		int x, y;
		do {
			x = rand() % n;
			y = rand() % n;
		} while (gameBoard[x][y] != 0);
		gameBoard[x][y] = 2;
	}
}