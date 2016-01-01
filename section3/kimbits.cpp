/*
ID: kevinli7
PROG: kimbits
LANG: C++
*/
#include <iostream>
#include <fstream>
using namespace std;
const int NMAX = 32;
long long dp[NMAX][NMAX];
int N,L;
long long I;
int main()
{
    ifstream fin("kimbits.in");
    fin >> N >> L >> I;
    fin.close();
    dp[1][0] = 1;
    dp[0][0] = 1;
    for (int i = 1; i <= N; ++i)
    {
        dp[1][i] = 2;
        dp[0][i] = 1;
    }
    for (int i = 2; i <= N; ++i)
    {
        dp[i][0] = 1;
        for (int j = 1; j <= L; ++j)
            dp[i][j] = dp[i-1][j] + dp[i-1][j-1];
    }

    ofstream fout("kimbits.out");
    for (int i = N; i > 0; --i)
    {
        if (I > dp[i-1][L])
        {
            fout << 1;
            I -= dp[i-1][L];
            --L;
        }
        else
        {
            fout << 0;
        }
    }
    fout << endl;
    fout.close();

}
