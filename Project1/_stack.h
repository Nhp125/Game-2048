#pragma once
#include<iostream>
#include<string>
#include<cstring>
using namespace std;

// Define player data type
struct Player {
	char name[50];
	int gameScore;
	Player& operator = (const Player& other){
		strcpy_s(this->name,sizeof(this->name), other.name);
		this->gameScore = other.gameScore;
		return *this;
	}
};

// Define information in node
struct Node {
	int** arr;
	Player player;
	int size;
	Node* next;
};

// Define stack
struct _stack {
	Node* head = NULL;
	// add node
	void push(int**, Player, int); 
	// remove node
	void pop();
	// return top node of stack
	Node* top();
	// clear stack
	void clear();
};
// undo game
void undoGame(_stack&, int**&, Player&, int);
// redo game
void redoGame(_stack&, int**&, Player&, int);
