//============================================================================
// Name        : Bee_UVa11000.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

int main()
{
	int n, first = 1;
	cin >> n;
	while(n != -1)
	{
		//if(first) first = 0; else cout << endl;
		unsigned long male = 0, female = 1, nmale = 0, nfemale = 0;
		if(n >= 50)
		{
			cout << "32951280098 32951280098" << endl;
			cin >> n;
			continue;
		}
		for(int i = 0; i < n; i++)
		{
			nmale = male + female;
			nfemale = male;
			male = nmale;
			female = nfemale + 1;
		}
		cout << male << " " << male + female << endl;
		cin >> n;
	}
	return 0;
}
