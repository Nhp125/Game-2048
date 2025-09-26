#include<iostream>
#include"setColor.h"
#include"showGame.h"
#ifdef _WIN32
#include<Windows.h>
#else
#include<ncurses.h>
#endif
using namespace std;

void gotoXY(int x, int y) {
#ifdef _WIN32
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
#else
	move(y, x);
	refresh();
#endif
}
void makeBorder(int n) {
	cout << "+";
	for (int i = 0; i < n; i++) {
		cout << "-------+";
	}
	cout << endl;
}
void showGame(int**& gameBoard, int n) {
#ifndef _WIN32
	initscr();
	noecho();
	cbreak();
#endif
	makeBorder(n);
	for (int i = 0; i < n; i++) {
		int k = 0;
		while (k < 3) {
			if (k == 1) {
				for (int j = 0; j < n; j++) {
					if (gameBoard[i][j] != 0) {
						int number = gameBoard[i][j];
						if (number == 2) {
							cout << "|   ";
							setColor(31);
							cout << number << "   ";
							cout << "\033[0m";
						}
						else if (number == 4) {
							cout << "|   ";
							setColor(32);
							cout << number << "   ";
							cout << "\033[0m";
						}
						else if (number == 8) {
							cout << "|   ";
							setColor(33);
							cout << number << "   ";
							cout << "\033[0m";
						}
						else if (number == 16) {
							cout << "|  ";
							setColor(34);
							cout << number << "   ";
							cout << "\033[0m";
						}
						else if (number == 32) {
							cout << "|  ";
							setColor(35);
							cout << number << "   ";
							cout << "\033[0m";
						}
						else if (number == 64) {
							cout << "|  ";
							setColor(36);
							cout << number << "   ";
							cout << "\033[0m";
						}
						else if (number == 128) {
							cout << "|  ";
							setColor(37);
							cout << number << "  ";
							cout << "\033[0m";
						}
						else if (number == 256) {
							cout << "|  ";
							setColor(90);
							cout << number << "  ";
							cout << "\033[0m";
						}
						else if (number == 512) {
							cout << "|  ";
							setColor(91);
							cout << number << "  ";
							cout << "\033[0m";
						}
						else if (number == 1024) {
							cout << "| ";
							setColor(92);
							cout << number << "  ";
							cout << "\033[0m";
						}
						else if (number == 2048) {
							cout << "| ";
							setColor(93);
							cout << number << "  ";
							cout << "\033[0m";
						}
						else if (number > 2048 && number < 10000) {
							cout << "| ";
							setColor(94);
							cout << number << "  ";
							cout << "\033[0m";
						}
						else if (number > 10000) {
							cout << "| ";
							setColor(95);
							cout << number << " ";
							cout << "\033[0m";
						}
					}
					else {
						cout << "|       ";
					}
				}
				cout << "|" << endl;
			}
			else {
				for (int j = 0; j < n + 1; j++) {
					if (j == 0) cout << "|";
					else cout << "       |";
				}
				cout << endl;
			}
			k++;
		}
		makeBorder(n);
	}
	gotoXY((n * 8)+ 10, 0);
	cout << "Controls: ";
	gotoXY((n * 8)+ 10, 1);
	cout << "A: turn left";
	gotoXY((n * 8) + 10, 2);
	cout << "D: turn right";
	gotoXY((n * 8) + 10, 3);
	cout << "S: go down";
	gotoXY((n * 8) + 10, 4);
	cout << "W: go up";
	gotoXY((n * 8) + 10, 5);
	cout << "P: replay game";
	gotoXY((n * 8) + 10, 6);
	cout << "E: exit";
	gotoXY((n * 8) + 10, 7);
	cout << "U: undo";
	gotoXY((n * 8) + 10, 8);
	cout << "R: redo";
	gotoXY(n * 4.5, n * 4.5);
#ifndef _WIN32
	endwin();
#endif
}