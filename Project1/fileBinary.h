#pragma once
#include<iostream>
#include"_stack.h"
#include<string>
using namespace std;
// write player information to file
void writeFile(string&, Player);
// output the highest score
int bestScore(string);
// check for duplicate names
bool checkName(string, Player);
// sort the file in descending order of scores
void sortFile(string&);
// print the top 20
void printTop20(string);