/*
ID: kevinli7
PROG: friday
LANG: C++11
*/

#include <iostream>
#include <fstream>
using namespace std;
int days[2][13]={{0,31,28,31,30,31,30,31,31,30,31,30,31},
			 {0,31,29,31,30,31,30,31,31,30,31,30,31}};
bool isLeap(int year)
{
	return (year%4==0 && year%100 !=0) || (year%400 == 0);
}

int main()
{
	ifstream input("friday.in");
	int N;
	int current_year = 1900;
	int current_month = 1;
	int current_day = 0;  // 0 means Saturday;
	int previous_day = 1;  // the previous date.
	int freq[7] = {0,0,0,0,0,0,0};
	int days_between = 0;
	input >> N;
	for (; current_year <= 1900 + N - 1; ++current_year)
	{
		bool leap = isLeap(current_year);
		for (current_month = 1; current_month <= 12; ++current_month)
		{
			freq[current_day]++;
			current_day = (current_day + days[leap][current_month])%7;
		}

	}
	ofstream output("friday.out");
	output << freq[0];
	for (int i = 1; i < 7; ++i)
		output <<' '<< freq[i];
	output << endl;
	input.close();
	output.close();
}