#include<iostream>
#include<stdlib.h>
#include<ctime>
#include<string>
#include<cstring>
#include<fstream>
#include<conio.h>
#include<iomanip>
#include"introduction.h"
#include"_stack.h"
#include"addTile.h"
#include"init_gameBoard.h"
#include"moveGame.h"
#include"setColor.h"
#include"showGame.h"
#include"gameCheck.h"
#include"fileBinary.h"
#include"gameSettings.h"
#include"playGame.h"
#include"resumeGame.h"
#include"clearScreen.h"
using namespace std;
int main()
{
	bool running = true;
	string fileName = "listPlayer.bin";
	bool UndoAndRedo = false;
	string fileResume1 = "fileResume1.bin";
	string fileResume2 = "fileResume2.bin";
	string fileResume3 = "fileResume3.bin";
	string fileResume4 = "fileResume4.bin";
	string fileResume5 = "fileResume5.bin";
	int n;
	Player player;
	int** gameBoard = NULL;
	while (running) {
		char key1;
		_stack undoStack;
		_stack redoStack;
		introduction();
		key1 = _getch();
		if (key1 == 'n' || key1 == 'N') {
			playGame(fileName, gameBoard, n, player, undoStack, redoStack, UndoAndRedo, fileResume1, fileResume2, fileResume3, fileResume4, fileResume5);
		}
		else if (key1 == 'l' || key1 == 'L') {
			system("cls");
			printTop20(fileName);
			char key;
			do {
				key = _getch();
			} while (key != 'e' && key != 'E');
			clearScreen();
			continue;

		}
		else if (key1 == 's' || key1 == 'S') {
			gameSettings(UndoAndRedo);
		}
		else if (key1 == 'r' || key1 == 'R') {
			resumeGame(fileName, gameBoard, n, player, undoStack, redoStack, UndoAndRedo, fileResume1, fileResume2, fileResume3, fileResume4, fileResume5);
		}
		else if (key1 == 'e' || key1 == 'E') {
			exit(0);
		}
		else {
			clearScreen();
		}
	}
	for (int i = 0; i < n; i++) {
		delete[] gameBoard[i];
	}
	delete[] gameBoard;
	return 0;
}