/*
ID: kevinli7
PROG: nocows
LANG: C++11
*/
#include <iostream>
#include <fstream>
using namespace std;
const int N_MAX = 201;
const int K_MAX = 101;
long long dp[N_MAX][K_MAX];
long long total, sum;
int N,K;
int trim;

int main()
{
    ifstream fin("nocows.in");
    fin >> N >> K;
    fin.close();
    dp[1][1] = 1;
    for (int n = 3; n <= N; n += 2)
    {
        for (int k = 1; k <= n && k <= K; ++k)
        {
            total = 0;
            trim = (k&1)?1:0;
            for (int i = k - 1 + trim; i <= n - 2; i += 2)
            {
                sum = 0;
                for (int j = 1; j < n - i && j < k - 1; ++j)
                    sum = (sum + dp[n-i-1][j]%9901)%9901;
                total = (total + dp[i][k-1]*sum)%9901;
            }
            total = (total*2) % 9901;
            for (int i = k - 1 + trim; i <= n - 2; i += 2)
            {
                sum = (dp[i][k-1]*dp[n-i-1][k-1])%9901;
                total = (total + sum) % 9901;
            }
            dp[n][k] = total;
        }
    }

    ofstream fout("nocows.out");
    fout << dp[N][K] << endl;

}
