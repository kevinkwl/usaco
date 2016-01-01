/*
ID: kevinli7
PROG: fracdec
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
const int MAX = 1000000;
int N,D;
int used[MAX];
int Int;
string decimal;
string repeated;
int pos;
int cur;
string ans;


int main()
{
    ifstream fin("fracdec.in");
    fin >> N >> D;
    fin.close();
    Int = N/D;
    N %= D;
    
    while (N != 0)
    {
        ++pos;
        N *= 10;
        if (used[N])
        {
            repeated = decimal.substr(used[N] - 1, pos - used[N]);
            decimal = decimal.substr(0, used[N] - 1);
            break;
        }
        decimal += to_string(N/D);
        used[N] = pos;
        N %= D;
    }
    ofstream fout("fracdec.out");
    ans = to_string(Int) + '.';
    if (decimal.empty() && repeated.empty())
        ans += '0';
    if (!decimal.empty())
        ans += decimal;
    if (!repeated.empty())
        ans += '(' + repeated +')';
    for (int i = 0; i < ans.size(); ++i)
    {
        fout << ans[i];
        if ((i+1)%76 == 0)
            fout << endl;
    }
    fout << endl;
    fout.close();

}
