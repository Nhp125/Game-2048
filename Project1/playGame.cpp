#include<iostream>
#include<conio.h>
#include"playGame.h"
#include"fileBinary.h"
#include"init_gameBoard.h"
#include"showGame.h"
#include"gameCheck.h"
#include"moveGame.h"
#include"addTile.h"
#include"resumeGame.h"
#include"clearScreen.h"
using namespace std;

void playGame(string& fileName, int**& gameBoard, int& n, Player& player, _stack& undoStack, _stack& redoStack, bool& UndoAndRedo, string& fileResume1, string& fileResume2, string& fileResume3, string& fileResume4, string& fileResume5) {
	clearScreen();
	do {
		cout << "Enter name: ";
		cin.getline(player.name, sizeof(player.name));
		if (!checkName(fileName, player)) {
			cout << "Username already exists! Please enter a different one.\n";
		}
	} while (!checkName(fileName, player));
	do {
		cout << "Enter the size of the game board (2-10): ";
		cin >> n;

		if (n < 2 || n > 10) {
			cout << "Invalid input. Please enter a number between 2 and 10." << endl;
		}
	} while (n < 2 || n > 10);
	cin.ignore();
	gameBoard = new int* [n];
	for (int i = 0; i < n; i++) {
		gameBoard[i] = new int[n];
	}
	init_gameBoard(gameBoard, n);
	player.gameScore = 0;
	undoStack.push(gameBoard, player, n);

	bool newGame = false;
	bool undoPerformed = false;
	char key;
	bool winGame = false;
	bool waitting = false;
	while (true) {
		if (newGame == true) {
			init_gameBoard(gameBoard, n);
			player.gameScore = 0;
			undoStack.clear();
			undoStack.push(gameBoard, player, n);
			redoStack.clear();
			newGame = false;
			winGame = false;
		}
		clearScreen();
		if (UndoAndRedo) {
			cout << "Undo Redo: " << "ON\n";
		}
		else cout << "Undo Redo: " << "OFF\n";
		cout << "Score: " << player.gameScore << endl;
		int bestscore = bestScore(fileName);
		if (player.gameScore > bestscore) {
			bestscore = player.gameScore;
		}
		cout << "Best: " << bestscore << endl;
		showGame(gameBoard, n);
		cout << endl;
		if (checkGameOver(gameBoard, n)) {
			cout << endl;
			cout << "GAME OVER !!!\n";
			redoStack.clear();
		}
		if (isWinGame(gameBoard, n) && winGame == false) {
			cout << endl;
			char keyW;
			cout << "CONGRATULATIONS. YOU HAVE WON!!!\n";
			cout << "Do you want to continue playing?\n";
			cout << "   Y: YES        N: NO\n";
			waitting = true;
			do {
				keyW = _getch();
			} while (keyW != 'y' && keyW != 'Y' && keyW != 'n' && keyW != 'N');

			if (waitting) {
				if (keyW == 'y' || keyW == 'Y') {
					winGame = true;
					clearScreen();
					continue;
				}
				else if (keyW == 'n' || keyW == 'N') {
					writeFile(fileName, player);
					sortFile(fileName);
					clearScreen();
					cout << "Do you want to save this account?\n";
					cout << "Y: Yes\n";
					cout << "N: No\n";
					char key;
					do {
						key = _getch();
					} while (key != 'y' && key != 'Y' && key != 'n' && key != 'N');

					if (key == 'n' || key == 'N') {
						clearScreen();
						break;
					}
					else if (key == 'y' || key == 'Y') {
						if (isFileEmpty(fileResume1)) {
							writeFileResume(fileResume1, gameBoard, n, player);
						}
						else if (isFileEmpty(fileResume2)) {
							writeFileResume(fileResume2, gameBoard, n, player);
						}
						else if (isFileEmpty(fileResume3)) {
							writeFileResume(fileResume3, gameBoard, n, player);
						}
						else if (isFileEmpty(fileResume4)) {
							writeFileResume(fileResume4, gameBoard, n, player);
						}
						else if (isFileEmpty(fileResume5)) {
							writeFileResume(fileResume5, gameBoard, n, player);
						}
						else {
							bool validInput = false;
							do {
								cout << "Which account do you want to save to?\n";
								cout << "1: Account 1\n";
								cout << "2: Account 2\n";
								cout << "3: Account 3\n";
								cout << "4: Account 4\n";
								cout << "5: Account 5\n";
								char _key = _getch();
								if (_key == '1' || _key == '2' || _key == '3' || _key == '4' || _key == '5') {
									validInput = true;
									if (_key == '1') {
										writeFileResume(fileResume1, gameBoard, n, player);
									}
									else if (_key == '2') {
										writeFileResume(fileResume2, gameBoard, n, player);
									}
									else if (_key == '3') {
										writeFileResume(fileResume3, gameBoard, n, player);
									}
									else if (_key == '4') {
										writeFileResume(fileResume4, gameBoard, n, player);
									}
									else if (_key == '5') {
										writeFileResume(fileResume5, gameBoard, n, player);
									}
								}
								else {
									clearScreen();
									cout << "Invalid input. Please choose again\n";
								}
							} while (!validInput);
						}
						break;
					}
				}
			}
		}

		key = _getch();
		int** checkboard = checkBoard(gameBoard, n);
		if (key == 'w' || key == 'W') {
			goUp(gameBoard, n, player.gameScore);
		}
		else if (key == 's' || key == 'S') {
			goDown(gameBoard, n, player.gameScore);
		}
		else if (key == 'a' || key == 'A') {
			turnLeft(gameBoard, n, player.gameScore);
		}
		else if (key == 'd' || key == 'D') {
			turnRight(gameBoard, n, player.gameScore);
		}
		else if (key == 'p' || key == 'P') {
			newGame = true;
		}
		else if (key == 'e' || key == 'E') {
			clearScreen();
			cout << "Are you sure you want to exit?\n";
			cout << "Y: Yes\n";
			cout << "N: No\n";
			char keyy;
			do {
				keyy = _getch();
			} while (keyy != 'y' && keyy != 'Y' && keyy != 'n' && keyy != 'N');

			if (keyy == 'n' || keyy == 'N') {
				continue;
			}
			else if (keyy == 'y' || keyy == 'Y') {
				writeFile(fileName, player);
				sortFile(fileName);
				clearScreen();
				cout << "Do you want to save this account?\n";
				cout << "Y: Yes\n";
				cout << "N: No\n";
				char key;
				do {
					key = _getch();
				} while (key != 'y' && key != 'Y' && key != 'n' && key != 'N');

				if (key == 'n' || key == 'N') {
					clearScreen();
					break;
				}
				else if (key == 'y' || key == 'Y') {
					if (isFileEmpty(fileResume1)) {
						writeFileResume(fileResume1, gameBoard, n, player);
					}
					else if (isFileEmpty(fileResume2)) {
						writeFileResume(fileResume2, gameBoard, n, player);
					}
					else if (isFileEmpty(fileResume3)) {
						writeFileResume(fileResume3, gameBoard, n, player);
					}
					else if (isFileEmpty(fileResume4)) {
						writeFileResume(fileResume4, gameBoard, n, player);
					}
					else if (isFileEmpty(fileResume5)) {
						writeFileResume(fileResume5, gameBoard, n, player);
					}
					else {
						bool validInput = false;
						do {
							cout << "Which account do you want to save to?\n";
							cout << "1: Account 1\n";
							cout << "2: Account 2\n";
							cout << "3: Account 3\n";
							cout << "4: Account 4\n";
							cout << "5: Account 5\n";
							char _key = _getch();
							if (_key == '1' || _key == '2' || _key == '3' || _key == '4' || _key == '5') {
								validInput = true;
								if (_key == '1') {
									writeFileResume(fileResume1, gameBoard, n, player);
								}
								else if (_key == '2') {
									writeFileResume(fileResume2, gameBoard, n, player);
								}
								else if (_key == '3') {
									writeFileResume(fileResume3, gameBoard, n, player);
								}
								else if (_key == '4') {
									writeFileResume(fileResume4, gameBoard, n, player);
								}
								else if (_key == '5') {
									writeFileResume(fileResume5, gameBoard, n, player);
								}
							}
							else {
								clearScreen();
								cout << "Invalid input. Please choose again\n";
							}
						} while (!validInput);
					}
					clearScreen();
					break;
				}
			}
		}
		else if ((key == 'u' || key == 'U') && UndoAndRedo == true) {
			if (undoStack.head != NULL) {
				redoStack.push(gameBoard, player, n);
				undoGame(undoStack, gameBoard, player, n);
				undoPerformed = true;
				continue;
			}
			else {
				undoPerformed = true;
				continue;
			}
		}
		else if ((key == 'r' || key == 'R') && UndoAndRedo == true) {
			if (redoStack.head != NULL) {
				redoGame(redoStack, gameBoard, player, n);
				undoStack.push(gameBoard, player, n);
				redoStack.pop();
				continue;
			}
			else {
				continue;
			}
		}
		else continue;
		if (!undoPerformed && checkMove(checkboard, gameBoard, n)) continue;
		addTile(gameBoard, n);
		undoStack.push(gameBoard, player, n);
		undoPerformed = false;
	}
}