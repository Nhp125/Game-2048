#include<iostream>
#include<conio.h>
#include<cstring>
#include"resumeGame.h"
#include<fstream>
#include"init_gameBoard.h"
#include"fileBinary.h"
#include"showGame.h"
#include"gameCheck.h"
#include"moveGame.h"
#include"addTile.h"
#include"clearScreen.h"
using namespace std;
void clearFile(const string& fileName) {
	ofstream ofs(fileName, ios::trunc);
	ofs.close();
}
void writeFileResume(string& fileName, int** gameBoard, int n, Player player) {
	clearFile(fileName);
	ofstream ofile(fileName, ios::binary);
	ofile.write((char*)&player, sizeof(Player));
	ofile.write((char*)&n, sizeof(int));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			ofile.write((char*)&gameBoard[i][j], sizeof(int));
		}
	}
	ofile.close();
}
void readFileResume(string fileName, int**& gameBoard, int& n, Player& player) {
	ifstream ifile(fileName, ios::binary);
	ifile.read((char*)&player, sizeof(Player));
	ifile.read((char*)&n, sizeof(int));
	gameBoard = new int* [n];
	for (int i = 0; i < n; i++) {
		gameBoard[i] = new int[n];
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			ifile.read((char*)&gameBoard[i][j], sizeof(int));
		}
	}
	ifile.close();
}
bool isFileEmpty(string fileName) {
	ifstream ifile(fileName, ios::binary | ios::ate);
	if (!ifile.is_open()) {
		return true;
	}
	streamsize size = ifile.tellg();
	ifile.close();
	return size == 0;

}
void readName(string fileName, int n) {
	ifstream ifile(fileName, ios::binary);
	if (isFileEmpty(fileName)) {
		cout << "Account " << n << " : " << " does not exist\n";
		return;
	}
	Player player;
	ifile.read((char*)&player, sizeof(Player));
	ifile.close();
	cout << "Account " << n << " : " << player.name << endl;
}
void updateScoreResume(string& fileName, Player player) {
	fstream file(fileName, ios::in | ios::out | ios::binary);
	Player _player;
	bool found = false;
	while (file.read(reinterpret_cast<char*>(&_player), sizeof(Player))) {
		if (strcmp(_player.name, player.name) == 0) {
			found = true;
			file.seekp(-static_cast<int>(sizeof(Player)), ios::cur);
			file.write(reinterpret_cast<const char*>(&player), sizeof(Player));
			break;
		}
	}
	if (!found) {
		return;
	}
	file.close();
}
void playgameResume(string& fileName, int**& gameBoard, int& n, Player& player, _stack& undoStack, _stack& redoStack, string& fileResume1, bool& UndoAndRedo) {
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
		}
		clearScreen();
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
			char keyw;
			do {
				keyW = _getch();
			} while (keyW != 'y' && keyW != 'Y' && keyW != 'n' && keyW != 'N');
			if (keyW == 'y' || keyW == 'Y') {
				winGame = true;
				clearScreen();
				continue;
			}
			else if (keyW == 'n' || keyW == 'N') {
				updateScoreResume(fileName, player);
				sortFile(fileName);
				writeFileResume(fileResume1, gameBoard, n, player);
				clearScreen();
				break;
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
			if (keyy == 'n' || key == 'N') {
				continue;
			}
			else if (keyy == 'y' || keyy == 'Y') {
				updateScoreResume(fileName, player);
				sortFile(fileName);
				writeFileResume(fileResume1, gameBoard, n, player);
				clearScreen();
				break;
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
void resumeGame(string& fileName, int**& gameBoard, int& n, Player& player, _stack& undoStack, _stack& redoStack, bool& UndoAndRedo, string& fileResume1, string& fileResume2, string& fileResume3, string& fileResume4, string& fileResume5) {
	bool validInput = false;
	do {
		clearScreen();
		cout << "Which account do you want to resume\n";
		readName(fileResume1, 1);
		readName(fileResume2, 2);
		readName(fileResume3, 3);
		readName(fileResume4, 4);
		readName(fileResume5, 5);
		char key = _getch();
		if (key == '1') {
			if (!isFileEmpty(fileResume1)) {
				readFileResume(fileResume1, gameBoard, n, player);
				playgameResume(fileName, gameBoard, n, player, undoStack, redoStack, fileResume1, UndoAndRedo);
				validInput = true;
			}
		}
		else if (key == '2') {
			if (!isFileEmpty(fileResume2)) {
				readFileResume(fileResume2, gameBoard, n, player);
				playgameResume(fileName, gameBoard, n, player, undoStack, redoStack, fileResume2, UndoAndRedo);
				validInput = true;
			}
		}
		else if (key == '3') {
			if (!isFileEmpty(fileResume3)) {
				readFileResume(fileResume3, gameBoard, n, player);
				playgameResume(fileName, gameBoard, n, player, undoStack, redoStack, fileResume3, UndoAndRedo);
				validInput = true;
			}
		}
		else if (key == '4') {
			if (!isFileEmpty(fileResume4)) {
				readFileResume(fileResume4, gameBoard, n, player);
				playgameResume(fileName, gameBoard, n, player, undoStack, redoStack, fileResume4, UndoAndRedo);
				validInput = true;
			}
		}
		else if (key == '5') {
			if (!isFileEmpty(fileResume5)) {
				readFileResume(fileResume5, gameBoard, n, player);
				playgameResume(fileName, gameBoard, n, player, undoStack, redoStack, fileResume5, UndoAndRedo);
				validInput = true;
			}
		}
		else if (key == 'e' || key == 'E') {
			clearScreen();
			break;
		}
		else {
			clearScreen();
		}
	} while (!validInput);
}