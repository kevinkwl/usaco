/*
ID: kevinli7
PROG: job
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
const int MMAX = 31;
const int NMAX = 1001;
int mA[MMAX],mB[MMAX];
int dA[MMAX],dB[MMAX];
int costA[NMAX],costB[NMAX],cost[NMAX];
int N,M1,M2,ans1,ans2;
int main()
{
    ifstream fin("job.in");
    fin >> N >> M1 >> M2;
    for (int i = 1; i <= M1; ++i)
        fin >> mA[i];
    for (int i = 1; i <= M2; ++i)
        fin >> mB[i];
    fin.close();
    int minloc = 0,cur;
    for (int i = 1; i <= N; ++i)
    {
        cur = 0x7fffffff;
        for (int j = 1; j <= M1; ++j)
            if (dA[j] + mA[j] < cur)   
            {
                minloc = j;
                cur = dA[j] + mA[j];
            }
        costA[i] = dA[minloc] + mA[minloc];
        dA[minloc] += mA[minloc];
        if (costA[i] > ans1)
            ans1 = costA[i];
    }
    sort(costA + 1, costA + N + 1);
    for (int i = 1; i <= N; ++i)
    {
        cur = 0x7fffffff;
        for (int j = 1; j <= M2; ++j)
            if (dB[j] + mB[j] < cur)   
            {
                minloc = j;
                cur = dB[j] + mB[j];
            }
        costB[i] = dB[minloc] + mB[minloc];
        dB[minloc] += mB[minloc];
    }
    sort(costB + 1, costB + N + 1);
    for (int i = 1; i <= N; ++i)
        cost[i] = costA[i] + costB[N-i+1];
    for (int i = 1; i <= N; ++i)
        if (cost[i] > ans2)
            ans2 = cost[i];
    ofstream fout("job.out");
    fout << ans1 << ' ' << ans2 << endl;
    fout.close();
}
