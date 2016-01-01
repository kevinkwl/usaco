/*
ID: kevinli7
PROG: fact4
LANG: C++11
*/
#include <iostream>
#include <fstream>
using namespace std;
int N;
int twos, fives;
int n[4221];
int res;
int main()
{
    ifstream fin("fact4.in");
    fin >> N;
    fin.close();
    int cur;
    res = 1;
    for (int i = 1; i <= N; ++i)
    {
        cur = i;
        while (cur%2 == 0)
        {
            cur >>=1;
            ++twos;
        }
        while (cur%5 == 0)
        {
            cur /= 5;
            ++fives;
        }
        res = (res*cur)%10;   
    }
    res = (res*(1<<(twos-fives)))%10;
    ofstream fout("fact4.out");
    fout << res << endl;
    fout.close();
}
