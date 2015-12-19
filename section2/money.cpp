/*
ID: kevinli7
PROG: money
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
using namespace std;
const int N_MAX = 10000; 
const int V_MAX = 25;
int V,N;
long long dp[N_MAX + 1][V_MAX + 1];
int coin[26];

int main()
{
    ifstream fin("money.in");
    fin >> V >> N;
    int u;
    for (int i = 1; i <= V; ++i)
    {
        fin >> coin[i];
    }
    for (int i = 0; i <= V; ++i)
        dp[0][i] = 1;
    dp[1][0] = 0;
    for (int i = 1; i <= N; ++i)
    {
        for (int j = 1; j <= V; ++j)
        {
            dp[i][j] += dp[i][j-1];
            if (coin[j] <= i)
                dp[i][j] += dp[i-coin[j]][j];
        }
    }

    ofstream fout("money.out");
    fout << dp[N][V] << endl;

}
