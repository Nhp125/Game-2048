#include<iostream>
#include<conio.h>
#include"gameSettings.h"
#include"clearScreen.h"
using namespace std;
void gameSettings(bool& UndoAndRedo) {
	clearScreen();
	cout << "Do you want to use the undo and redo feature?\n";
	cout << "Y: Yes\n";
	cout << "O: No\n";
	cout << "E: Exit\n";
	char key;
	do {
		key = _getch();
		if (key == 'y' || key == 'Y') {
			clearScreen();
			UndoAndRedo = true;
			break;
		}
		else if (key == 'o' || key == 'O') {
			clearScreen();
			UndoAndRedo = false;
			break;
		}
		else if (key == 'e' || key == 'E') {
			clearScreen();
			break;
		}
		else {
			clearScreen();
			cout << "Invalid input!\n";
			cout << "Do you want to use the undo and redo feature?\n";
			cout << "Y: Yes\n";
			cout << "O: No\n";
			cout << "E: Exit\n";
		}
	} while (true);
}