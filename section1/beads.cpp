/*
ID: kevinli7
PROG: beads
LANG: C++11
*/
#include <iostream>
#include <fstream>
#define Nmax  350
char beads[Nmax] = {'\0'};
using namespace std;

int main()
{
	ifstream fin("beads.in");
	ofstream fout("beads.out");
	int N;
	fin >> N;
	for (int i = 0 ; i < N; ++i)
		fin >> beads[i];
	int maxBeads = 0;
	for (int i = 0 ; i < N; ++i)
	{
		char previous = beads[i];
		int shift = i;
		int thisBeads = 0;
		bool uninitialize = true;
		bool flag = true;
		while (flag&&(beads[shift] == 'w' || uninitialize ||beads[shift] == previous))
		{
			++thisBeads;
			if (beads[shift] != 'w' && uninitialize)
			{
				previous = beads[shift];
				uninitialize = false;
			}
			if (shift == 0)
				shift = N;
			--shift;
			if (shift == i)
			{
				break;
			}
		}
		int tail;
		if (shift == N - 1)
			tail = 0;
		else
			tail = shift + 1;
		uninitialize = true;
		if (i == N - 1)
			shift = 0;
		else
			shift = i + 1;
		previous = beads[shift];
		while ((beads[shift] == 'w' || uninitialize ||beads[shift] == previous)&&shift != tail)
		{
			++thisBeads;
			if (beads[shift] != 'w' && uninitialize)
			{
				previous = beads[shift];
				uninitialize = false;
			}
			if (shift == N - 1)
				shift = -1;
			++shift;
		}
		//cout << thisBeads << endl;
		if (thisBeads >= maxBeads)
			maxBeads = thisBeads;
	}

	fout << maxBeads << endl;
	fin.close();
	fout.close();
	return 0;
}