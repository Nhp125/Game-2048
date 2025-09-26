#include<iostream>
#include<ctime>
#include<stdlib.h>
#include"addTile.h"
using namespace std;
int randomNumber() {
	int n = rand() % 100;
	if (n < 80) {
		return 2;
	}
	else return 4;
}

void addTile(int**& gameBoard, int n) {
	srand(time(NULL));
	int x, y;
	do {
		x = rand() % n;
		y = rand() % n;
	} while (gameBoard[x][y] != 0);
	gameBoard[x][y] = randomNumber();
}