#include<iostream>
#include"gameCheck.h"
using namespace std;
int** checkBoard(int** gameBoard, int n) {
	int** checkBoard = new int* [n];
	for (int i = 0; i < n; i++) {
		checkBoard[i] = new int[n];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			checkBoard[i][j] = gameBoard[i][j];
		}
	}
	return checkBoard;
}

bool checkMove(int** checkBoard, int** gameBoard, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (checkBoard[i][j] != gameBoard[i][j]) return false;
		}
	}
	return true;
}

bool checkZero(int** gameBoard, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (gameBoard[i][j] == 0) return true;
		}
	}
	return false;
}
bool checkGameOver(int** gameBoard, int n) {
	if (!checkZero(gameBoard, n)) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if ((j < n - 1 && gameBoard[i][j] == gameBoard[i][j + 1]) || (i < n - 1 && gameBoard[i][j] == gameBoard[i + 1][j])) {
					return false;
				}
			}
		}
		return true;
	}
	return false;
}
bool isWinGame(int** gameBoard, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (gameBoard[i][j] == 2048) {
				return true;
			}
		}
	}
	return false;
}