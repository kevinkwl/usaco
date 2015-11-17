/*
ID: kevinli7
PROG: palsquare
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
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
	ifstream fin("palsquare.in");
	ofstream fout("palsquare.out");
	int base;
	fin >> base;
	for (int i = 1; i <= 300; ++i)
	{
		int square = i * i;
		if (palindromic(to_base(square, base)))
			fout << to_base(i, base) << ' ' << to_base(square, base) << endl;
	}
}