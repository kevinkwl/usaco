/*
ID: kevinli7
PROG: pprime
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;
int a,b;
int da, db;
vector<int> ans;
ofstream fout("pprime.out");
int d[10];
int tens[]={1,10,100,1000,10000,100000,1000000,10000000,100000000};
vector<int> nums;
bool isPrime(int i)
{
    if (i%2 == 0)
        return false;
    int len = sqrt(i*1.0);
    for (int k = 3; k <= len; ++k)
        if (i%k == 0)
            return false;
    return true;
}
void find(int pos, int dgs)
{
    if (pos > (dgs-1)/2)
        return;
    if (pos == (dgs-1)/2)
    {
        int number = 0;
        for (int i = 0; i < dgs; ++i)
        {  
            number += d[i]*tens[i];
        }
        if (isPrime(number) )//&& number <= b && number >= a)
            nums.push_back(number);
            //fout << number << endl;;
        return;
    }
    else
        for (int i = 0; i <= 9; ++i)
        {
            d[pos+1] = d[dgs-1-pos-1] = i;
            find(pos+1, dgs);
        }
    return;
}

int main()
{
    ifstream fin("pprime.in");
    fin >> a >> b;
    fin.close();

    for (int i = 1; i <= 8; ++i)
    {
        for (int j = 1; j < 10; j+=2)
        {
            d[i-1] = d[0] = j;
            find(0, i);   
        }   
    }
    for (auto & n : nums)
        if (n >= a && n <= b)
            fout << n << endl;
    fout.close();
}
