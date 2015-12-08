//============================================================================
// Name        : Tester.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "./Matrix/matrix.h"
#include <vector>
#include <stdexcept>
#include <cstdio>
using namespace std;

int main() {
	dimension newdim(3, 3);
	matrix* newmat = new matrix(newdim);
	matrix& mynew = *newmat;
	for(int i = 0; i < 3; i ++)
		for(int j = 0; j < 3; j++)
			mynew[i][j] = i + j;
	cout << mynew.tostring();
	mynew.addrows(1, 12);
	cout << mynew.tostring();
}
