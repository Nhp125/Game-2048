#pragma once
#include<iostream>
using namespace std;
// go up
void goUp(int**& gameBoard, int n, int& gameScore);
// go down
void goDown(int**& gameBoard, int n, int& gameScore);
// turn left
void turnLeft(int**& gameBoard, int n, int& gameScore);
// turn right
void turnRight(int**& gameBoard, int n, int& gameScore);