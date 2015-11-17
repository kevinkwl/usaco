/*
ID: kevinli7
PROG: milk
LANG: C++11
*/

#include <iostream>
#include <vector>
#include <utility>
#include <fstream>
#include <algorithm>
using namespace std;
int N,M, price=0, amount=0, cost=0;
vector<pair<int,int>> milk;
int main()
{
	ifstream fin("milk.in");
	ofstream fout("milk.out");
	fin >> N >> M;
	while (M--)
	{
		fin >> price >> amount;
		milk.push_back(pair<int,int>(price, amount));
	}
	sort(milk.begin(), milk.end(), [](pair<int,int> a, pair<int, int> b)
		{
			return a.first < b.first;
		});
	for(auto & store : milk)
	{
		if (N == 0)
			break;
		if (N <= store.second)
		{
			cost += N* store.first;	
			N = 0;
		}
		else
		{
			N -= store.second;
			cost += store.second * store.first;			
		}
	}
	fout << cost << endl;
}