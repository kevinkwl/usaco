/*
ID: kevinli7
PROG: bigbrn
LANG: C++11
*/
#include <iostream>
#include <fstream>
using namespace std;
const int NMAX = 1001;
int dp[NMAX][NMAX];
int biggest,N,T;
bool grid[NMAX][NMAX];

int main()
{
    ifstream fin("bigbrn.in");
    fin >> N >> T;
    int r,c;
    for (int i = 1; i <= T; ++i)
    {
        fin >> r >> c;
        grid[r][c] = true;
    }
    fin.close();
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= N; ++j)
        {
            if (grid[i][j])
                dp[i][j] = 0;
            else
            {
                dp[i][j] = min(dp[i-1][j],min(dp[i-1][j-1],dp[i][j-1]))
                            + 1;
            }
            if (dp[i][j] > biggest)
                biggest = dp[i][j];
        }

    ofstream fout("bigbrn.out");
    fout << biggest << endl;
    fout.close();

}
