//============================================================================
// Name        : Modular_Fibonacci_UVa_10229.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <cstdio>
#include <iostream>
#include <vector>
using namespace std;

int main()
{
	unsigned long n, m;
	//freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	while(cin >> n >> m)
	{
		n++;
		cout << "n = " << n << " m = " << m << endl;

		vector<long> table;
		long target = 1 << m;
		if(m > 0)
		{
			table.push_back(0);
			table.push_back(1);
		}else{
			cout << m << endl;
			continue;
		}
		unsigned long i = 2;
		for(; i < n; i++)
		{
			long temp = (table[i - 1] + table[i - 2]) % target;
			table.push_back(temp);
			printf("i = %d, temp = %d\n", i, temp);
			if(temp == 0 && table[i - 1] == 1) break;
		}
		printf("table[i] = %d, table[i - 1] = %d\n", table[i], table[i - 1]);
		i --;
		cout << "i = " << i << " n % i = " << n % i << " n = " << n << endl;
		printf("table = %d\n", table[n % i]);
		if(i + 1 == n) cout << table[i] << endl;
		else cout << table[n % ++i] << endl;rs
	}
	return 0;
}
