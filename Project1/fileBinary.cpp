#include"fileBinary.h"
#include<iostream>
#include<string>
#include<cstring>
#include<fstream>
#include<iomanip>
void writeFile(string& fileName, Player player) {
	ofstream ofile(fileName, ios::binary | ios::app);
	if (!ofile.is_open()) {
		return;
	}
	ofile.write((char*)&player, sizeof(Player));
	ofile.close();
}

int bestScore(string fileName) {
	ifstream ifile(fileName, ios::binary);
	Player _player;
	ifile.read((char*)&_player, sizeof(Player));
	ifile.close();
	return _player.gameScore;
}

bool checkName(string fileName, Player player) {
	ifstream ifile(fileName, ios::binary);
	Player _player;
	while (ifile.read((char*)&_player, sizeof(Player))) {
		if (strcmp(_player.name, player.name) == 0) {
			ifile.close();
			return false;
		}
	}
	ifile.close();
	return true;
}

void sortArray(Player*& players, int size) {
	for (int i = 0; i < size - 1; i++) {
		for (int j = i + 1; j < size; j++) {
			if (players[i].gameScore < players[j].gameScore) {
				swap(players[i], players[j]);
			}
		}
	}
}

void sortFile(string& fileName) {
	ifstream ifile(fileName, ios::binary);
	Player _player;
	int size = 0;
	while (ifile.read((char*)&_player, sizeof(Player))) {
		size++;
	}
	ifile.clear();
	Player* players = new Player[size];
	ifile.seekg(0, ios::beg);
	int i = 0;
	while (ifile.read((char*)&_player, sizeof(Player)) && i < size) {
		players[i++] = _player;
	}
	sortArray(players, size);
	ifile.close();
	ofstream ofile(fileName, ios::binary | ios::trunc);
	for (int i = 0; i < size; i++) {
		ofile.write((char*)&players[i], sizeof(Player));
	}
	ofile.close();
	delete[] players;
}

void printTop20(string fileName) {
	ifstream ifile(fileName, ios::binary);
	if (!ifile.is_open()) {
		return;
	}
	Player _player;
	int count = 0;
	bool isEmpty = true;
	cout << left << setw(30) << "Player Name" << "Score" << endl;
	cout << string(40, '-') << endl;
	while (ifile.read((char*)&_player, sizeof(Player)) && count < 20) {
		isEmpty = false;
		cout << left << setw(30) << _player.name << _player.gameScore << endl;
		count++;
	}
	ifile.close();
	if (isEmpty) {
		cout << "No player yet!\n";
	}
}