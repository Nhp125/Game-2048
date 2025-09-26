#pragma once
#include<iostream>
#include<string>
#include"_stack.h"
using namespace std;
// clear old file
void clearFile(const string&);
// write information to be saved into file
void writeFileResume(string&, int**, int, Player);
// read information from file
void readFileResume(string, int**&, int& n, Player&);
// check if file is empty
bool isFileEmpty(string);
// read account names
void readName(string, int);
// update score in file
void updateScoreResume(string&, Player);
// play resumed game
void playgameResume(string&, int**&, int&, Player&, _stack&, _stack&, string&, bool&);
// resume game
void resumeGame(string&, int**&, int&, Player&, _stack&, _stack&, bool&, string&, string&, string&, string&, string&);