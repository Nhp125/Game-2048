#include<iostream>
#include"moveGame.h"
using namespace std;
void goUp(int**& gameBoard, int n, int& gameScore) {
	// Move elements upwards
	for (int j = 0; j < n; j++) {
		int k = 0;
		for (int i = 0; i < n; i++) {
			if (gameBoard[i][j] != 0) {
				gameBoard[k][j] = gameBoard[i][j];
				k++;
			}
		}
		for (int i = k; i < n; i++) {
			gameBoard[i][j] = 0;
		}
	}

	// Merge identical elements
	for (int j = 0; j < n; j++) {
		for (int i = 0; i < n - 1; i++) {
			if (gameBoard[i][j] == gameBoard[i + 1][j]) {
				gameScore += gameBoard[i][j];
				gameBoard[i][j] = 2 * gameBoard[i][j];
				gameBoard[i + 1][j] = 0;
				i++;
			}
		}
	}

	// Move elements upwards after merging
	for (int j = 0; j < n; j++) {
		int k = 0;
		for (int i = 0; i < n; i++) {
			if (gameBoard[i][j] != 0) {
				gameBoard[k][j] = gameBoard[i][j];
				k++;
			}
		}
		for (int i = k; i < n; i++) {
			gameBoard[i][j] = 0;
		}
	}
}

void goDown(int**& gameBoard, int n, int& gameScore) {
	// Move elements downwards
	for (int j = 0; j < n; j++) {
		int k = n - 1;
		for (int i = n - 1; i >= 0; i--) {
			if (gameBoard[i][j] != 0) {
				gameBoard[k][j] = gameBoard[i][j];
				k--;
			}
		}
		for (int i = k; i >= 0; i--) {
			gameBoard[i][j] = 0;
		}
	}

	// Merge identical elements
	for (int j = 0; j < n; j++) {
		for (int i = n - 1; i > 0; i--) {
			if (gameBoard[i][j] == gameBoard[i - 1][j]) {
				gameScore += gameBoard[i][j];
				gameBoard[i][j] = 2 * gameBoard[i][j];
				gameBoard[i - 1][j] = 0;
				i--;
			}
		}
	}

	// Move elements downwards after merging
	for (int j = 0; j < n; j++) {
		int k = n - 1;
		for (int i = n - 1; i >= 0; i--) {
			if (gameBoard[i][j] != 0) {
				gameBoard[k][j] = gameBoard[i][j];
				k--;
			}
		}
		for (int i = k; i >= 0; i--) {
			gameBoard[i][j] = 0;
		}
	}
}

void turnLeft(int**& gameBoard, int n, int& gameScore) {
	// Move elements to the left
	for (int i = 0; i < n; i++) {
		int k = 0;
		for (int j = 0; j < n; j++) {
			if (gameBoard[i][j] != 0) {
				gameBoard[i][k] = gameBoard[i][j];
				k++;
			}
		}
		for (int j = k; j < n; j++) {
			gameBoard[i][j] = 0;
		}
	}

	// Merge identical elements
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - 1; j++) {
			if (gameBoard[i][j] == gameBoard[i][j + 1]) {
				gameScore += gameBoard[i][j];
				gameBoard[i][j] = 2 * gameBoard[i][j];
				gameBoard[i][j + 1] = 0;
				j++;
			}
		}
	}

	// Move elements to the left after merging
	for (int i = 0; i < n; i++) {
		int k = 0;
		for (int j = 0; j < n; j++) {
			if (gameBoard[i][j] != 0) {
				gameBoard[i][k] = gameBoard[i][j];
				k++;
			}
		}
		for (int j = k; j < n; j++) {
			gameBoard[i][j] = 0;
		}
	}
}

void turnRight(int**& gameBoard, int n, int& gameScore) {
	// Move elements to the right
	for (int i = 0; i < n; i++) {
		int k = n - 1;
		for (int j = n - 1; j >= 0; j--) {
			if (gameBoard[i][j] != 0) {
				gameBoard[i][k] = gameBoard[i][j];
				k--;
			}
		}
		for (int j = k; j >= 0; j--) {
			gameBoard[i][j] = 0;
		}
	}

	// Merge identical elements
	for (int i = 0; i < n; i++) {
		for (int j = n - 1; j > 0; j--) {
			if (gameBoard[i][j] == gameBoard[i][j - 1]) {
				gameScore += gameBoard[i][j];
				gameBoard[i][j] = 2 * gameBoard[i][j];
				gameBoard[i][j - 1] = 0;
				j--;
			}
		}
	}

	// Move elements to the right after merging
	for (int i = 0; i < n; i++) {
		int k = n - 1;
		for (int j = n - 1; j >= 0; j--) {
			if (gameBoard[i][j] != 0) {
				gameBoard[i][k] = gameBoard[i][j];
				k--;
			}
		}
		for (int j = k; j >= 0; j--) {
			gameBoard[i][j] = 0;
		}
	}
}