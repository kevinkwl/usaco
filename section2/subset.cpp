/*
ID: kevinli7
PROG: subset
LANG: C++11
*/
#include <iostream>
#include <fstream>
using namespace std;
#define N_MAX 40
int N;
long long sum;
long long ways[N_MAX][N_MAX*(N_MAX+1)/4 + 1];
        
void solve()
{
    for (int i = 0; i <= N; ++i)
        ways[i][0] = 1;
    ways[1][1] = 1;
    for (long long i = 2; i <= sum; ++i)
        ways[1][i] = 0;
    for (int i = 2; i <= N; ++i)
        for (long long j = 1; j <= sum; ++j)
        {
            ways[i][j] = ways[i-1][j];
            if (j >= i)
                ways[i][j] += ways[i-1][j-i];
        }
}
int main()
{
    bool flag = false;
    ifstream fin("subset.in");
    fin >> N;
    fin.close();
    
    ofstream fout("subset.out");
    sum = N*(N+1)/2;
    if (sum % 2 == 0)
    {
        sum /= 2;
        solve();
    }
    fout << ways[N][sum]/2 << endl;

    fout.close();
    return 0;
}
