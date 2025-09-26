#include<iostream>
#include"setColor.h"
using namespace std;
void setColor(int color) {
	cout << "\033[" << color << "m";
}