/*
ID: kevinli7
PROG: milk2
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#define Nmax 5000
using namespace std;
using pa = pair<int, int>;
int main()
{
	ifstream fin("milk2.in");
	ofstream fout("milk2.out");
	int N;
	fin >> N;
	int start,end;
	int thisMax = 0;
	int thisMin = 0;
	int max = 0, min = 0;
	vector<pa> farmer;
	farmer.reserve(Nmax);
	while (N--)
	{
		fin >>start >> end;
		farmer.push_back(make_pair(start, end));
	}
	sort(farmer.begin(), farmer.end(), [](const pa &lhs, const pa &rhs)
				{
					return lhs.first < rhs.first;
				});
	vector<pa>::iterator prev = farmer.begin();
	auto iter = farmer.begin();
	max = thisMax = iter->second - iter->first;
	//cout << iter->first << ' ' << iter->second << endl;
	for (++iter; iter != farmer.end(); ++iter)
	{
		//cout << iter->first << ' ' << iter->second << endl;
		if (iter->first <= prev->second)
		{
			if (iter->second > prev->second)
			{
				thisMax += iter->second - prev->second;
				prev = iter;
			}
		}
		else 
		{
			if (thisMax > max)
				max = thisMax;
			thisMax = iter->second - iter->first;
			thisMin = iter->first - prev->second;
			//cout << thisMin << endl;
			if (thisMin > min)
				min = thisMin;
			prev = iter;
		}

	}
	fout << max << ' ' << min << endl;
	
	fin.close();
	fout.close();
}