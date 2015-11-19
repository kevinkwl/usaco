/*
ID: kevinli7
PROG: barn1
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
int M,S,C;
vector<int> stall;
vector<int> empty_stall;
int no_stall;
int covered;
int main()
{
	ifstream fin("barn1.in");
	ofstream fout("barn1.out");
	fin >> M >> S >> C;
	while (C--)
	{
		fin >> no_stall;
		stall.push_back(no_stall);
	}
	sort(stall.begin(), stall.end());    // sort by stall No.
	C = stall.size();
	covered = (C > 1)? stall[C-1] - stall[0] + 1: stall[0];   // max stalls
	for (int i = 0 ; i < C - 1; ++i)
	{
		empty_stall.push_back(stall[i+1] - stall[i]-1);     // the stalls with no cows
	}
	sort(empty_stall.rbegin(), empty_stall.rend());		// sort the part that we should not cover
	for (int i = 0 ; i < empty_stall.size() && M > 1; ++i, --M)
	{
		covered -= empty_stall[i];					// remove the current longest empty part
	}
	fout << covered << endl;
}