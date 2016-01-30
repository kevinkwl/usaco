/*
ID: kevinli7
PROG: tour
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <map>
using namespace std;
const int NMAX = 101;
const int INF = 0x7fffffff;
map<string, int> idx;
bool flight[NMAX][NMAX];
int dp[NMAX][NMAX],N,V;

int main()
{
    ifstream fin("tour.in");
    fin >> N >> V;
    string s1,s2;
    for (int i = 1; i <= N; ++i)
    {
        fin >> s1;
        idx[s1] = i;
    }
    for (int i = 1; i <= V; ++i)
    {
        fin >> s1 >> s2;
        flight[idx[s1]][idx[s2]] = flight[idx[s2]][idx[s1]] = 1;
    }

    dp[1][1] = 1;
    for (int i = 1; i <= N; ++i)
        for (int j = i + 1; j <= N; ++j)
        {
            dp[i][j] = -INF;
            if (i == j)
                continue;
            for (int k = 1; k < j; ++k)
                if (flight[k][j] && dp[i][k] > 0 && dp[i][k] > dp[i][j])
                    dp[i][j] = dp[i][k];
            dp[j][i] = ++dp[i][j];
        }

    int ans = 1;
    for (int i = 1; i <= N; ++i)
        if (flight[i][N])
            ans = max(ans, dp[i][N]);
    ofstream fout("tour.out");
    fout << ans << endl;
    fout.close();
    fin.close();

}
