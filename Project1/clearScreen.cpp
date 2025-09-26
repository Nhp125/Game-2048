#include<iostream>
#include<cstdlib>
#include"clearScreen.h"
using namespace std;
void clearScreen() {
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}