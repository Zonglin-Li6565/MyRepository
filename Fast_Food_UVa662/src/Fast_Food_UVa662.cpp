//============================================================================
// Name        : Fast_Food_UVa662.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
int* v;			//k x n
int* d;			//k x n
int* l;			//n
int r, c;

int dp(int k, int i);
int print(int k, int i);

int main()
{
	freopen("output.txt", "w", stdout);
	while(scanf("%d%d", &c, &r) && !(c == 0 && r == 0))
	{
		v = new int[r * c];
		d = new int[r * c];
		l = new int[c];
		for(int i = 0; i < c; i++)
		{
			scanf("%d", &l[i]);
		}
		int ans = 1 << 30, count = 0;
		fill(&d[0], &d[r * c - 1], 0);
		for(int i = 0; i < c; i++)
		{
			fill(&v[0], &v[r * c - 1], 0);
			int counter = 0;
			for(int t = 0; t < i; t++)
			{
				counter += l[i] - l[t];
			}
			int temp = dp(r - 1, i) + counter;
			if(ans < temp){
				ans = temp;
				count = i;
			}
		}
		fill(&v[0], &v[r * c - 1], 0);
		printf("%d\n", ans);
	}
	return 0;
}

int dp(int k, int i)
{
	//printf("k = %d, i = %d\n", k, i);
	int& ans = d[k * c + i];
	if(v[k * c + i]) return ans;
	if(k == 0)
	{
		ans = 0;
		for(int t = i; t < c; t++)
		{
			ans += l[t] - l[i];
		}
	}else
	{
		ans = 1 << 30;
		for(int t = i + 1; t < c - k + 1; t++)
		{
			int mid = (l[i] + l[t]) / 2, count = 0;
			for(int f = i + 1; f < t; f++)
			{
				count += (l[f] - l[i]) < mid ? l[f] - l[i] : l[t] - l[f];
			}
			int temp = dp(k - 1, t) + count;
			ans = ans < temp ? ans : temp;
		}
	}
	v[k * c + i] = 1;
	//printf("at k = %d, i = %d, ans = %d\n", k, i, ans);
	return d[k * c + i];
}

int print(int k, int i)
{
	//printf("k = %d, i = %d\n", k, i);
		int& ans = d[k * c + i];
		if(v[k * c + i]) return ans;
		if(k == 0)
		{
			ans = 0;
			for(int t = i; t < c; t++)
			{
				ans += l[t] - l[i];
			}
		}else
		{
			ans = 1 << 30;
			for(int t = i + 1; t < c - k + 1; t++)
			{
				int mid = (l[i] + l[t]) / 2, count = 0;
				for(int f = i + 1; f < t; f++)
				{
					count += (l[f] - l[i]) < mid ? l[f] - l[i] : l[t] - l[f];
				}
				int temp = dp(k - 1, t) + count;
				ans = ans < temp ? ans : temp;
			}
		}
		v[k * c + i] = 1;
		//printf("at k = %d, i = %d, ans = %d\n", k, i, ans);
		return d[k * c + i];
}


