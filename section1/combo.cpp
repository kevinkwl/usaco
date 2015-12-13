/*
ID: kevinli7
PROG: combo
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <vector>
#define for(i,N,x) for(i = x; i < N; ++i)
using namespace std;
int farmer[3], master[3], ans = 0, N;
// brute force
int distance(int i, int j)
{
	int dis = i - j;
	if (dis < 0)
		dis = -dis;
	if (dis > N/2)
		dis = N - dis;
	return dis;
}
bool valid(int i, int j, int k)
{
	if (distance(i,farmer[0]) < 3)
		if (distance(j, farmer[1]) < 3)
			if (distance(k, farmer[2]) < 3)
				return true;
	if (distance(i,master[0]) < 3)
		if (distance(j, master[1]) < 3)
			if (distance(k, master[2]) < 3)
				return true;
	return false;	
}
int main()
{
	ifstream fin("combo.in");
	ofstream fout("combo.out");
	fin >> N;
	int p,i,j,k;
	for(i,3,0)
	{
		fin >> p;
		farmer[i] = p;
	}
	for(i,3,0)
	{
		fin >>p;
		master[i] = p;
	}
	for(i,N+1,1)
		for(j,N+1,1)
			for(k,N+1,1)
			{
				if (valid(i,j,k))
				{
					++ans;
				}
			}
	fout << ans << endl;
}