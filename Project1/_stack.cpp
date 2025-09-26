#include"_stack.h"
#include<iostream>
#include<string>
#include<cstring>
using namespace std;
int** createArray2D(int n) {
	int** arr = new int* [n];
	for (int i = 0; i < n; i++) {
		arr[i] = new int[n];
	}
	return arr;
}

void deleteArray2D(int** arr, int n) {
	for (int i = 0; i < n; i++) {
		delete[] arr[i];
	}
	delete[] arr;
}

Node* createNode(int** gameBoard, Player _player, int n) {
	Node* newNode = new Node;
	int** arr = createArray2D(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			arr[i][j] = gameBoard[i][j];
		}
	}
	newNode->arr = arr;
	newNode->player.gameScore = _player.gameScore;
	strcpy_s(newNode->player.name,sizeof(newNode->player.name),_player.name);
	newNode->size = n;
	newNode->next = NULL;
	return newNode;
}

void _stack::push(int** gameBoard, Player _player, int n) {
	Node* newNode = createNode(gameBoard, _player, n);
	if (head == NULL) {
		head = newNode;
	}
	else {
		newNode->next = head;
		head = newNode;
	}
}

void _stack::pop() {
	if (head == NULL) {
		return;
	}
	else {
		Node* temp = head;
		head = head->next;
		deleteArray2D(temp->arr, temp->size);
		delete temp;
	}
}

Node* _stack::top() {
	return head;
}

void _stack::clear() {
	while (head != NULL) {
		pop();
	}
}

void undoGame(_stack& undoStack, int**& gameBoard, Player& _player, int n) {
	if (undoStack.top() == NULL) {
		return;
	}
	undoStack.pop();
	if (undoStack.top() == NULL) {
		return;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			gameBoard[i][j] = undoStack.top()->arr[i][j];
		}
	}
	_player.gameScore = undoStack.top()->player.gameScore;
	strcpy_s(_player.name, sizeof(_player.name), undoStack.top()->player.name);
}

void redoGame(_stack& redoStack, int**& gameBoard, Player& _player, int n) {
	if (redoStack.top() == NULL) {
		return;
	}
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			gameBoard[i][j] = redoStack.top()->arr[i][j];
		}
	}
	_player.gameScore = redoStack.top()->player.gameScore;
	strcpy_s(_player.name, sizeof(_player.name), redoStack.top()->player.name);
}