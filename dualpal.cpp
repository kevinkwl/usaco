/*
ID: kevinli7
PROG: dualpal
LANG: C++11
*/
#include <iostream>
#include <fstream>
using namespace std;
string to_base(int num, int base)
{
	int digit, new_num;
	string ret;
	while (num > 0)
	{
		digit = num % base;
		num /= base;
		if (digit < 10)
			ret = to_string(digit) + ret;
		else
		{
			char ch = 'A' + digit - 10;
			ret = ch + ret;
		}
	}
	return ret;
}
bool palindromic(const string &s)
{
	string reverse;
	reverse.assign(s.rbegin(), s.rend());
	if (reverse == s)
		return true;
	return false;
}
int main()
{
	
	ifstream fin("dualpal.in");
	ofstream fout("dualpal.out");
	int N,S;
	int count;
	fin >> N >> S;
	for (int i = S+1; N; ++i)
	{
		count = 0;
		for (int base = 2; base <= 10; ++base)
		{
			if (palindromic(to_base(i, base)))
				++count;
			if (count >= 2)
			{
				fout << i << endl;
				--N;
				break;
			}
		}
	}
}












