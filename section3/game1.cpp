/*
ID: kevinli7
PROG: game1
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
const int NMAX = 101;
int best[NMAX][NMAX];
int N, n[NMAX];
int max1,max2,tmax;
int sum[NMAX][NMAX];
int main()
{
    ifstream fin("game1.in");
    fin >> N;
    for (int i = 1; i <= N; ++i)
    {
        fin >> n[i];
        best[i][i] = n[i];
        sum[i][i]= n[i];
    }
    fin.close();
    for (int i = 2; i <= N; ++i)
        for (int s = 1; s <= N - i + 1; ++s)
        {
            if (i == 2)
            {
                best[s][s+1] = max(n[s],n[s+1]);
                sum[s][s+1] = n[s] + n[s+1];
            }
            else
            {
                max1 = n[s] + sum[s+1][s+i-1] - best[s+1][s+i-1];
                max2 = n[s+i-1] + sum[s][s+i-2] - best[s][s+i-2];
                best[s][s+i-1] = max(max1,max2);
                sum[s][s+i-1] =sum[s+1][s+i-1] + n[s];
            }
        }
    ofstream fout("game1.out");
    fout << best[1][N] << ' ' << sum[1][N] - best[1][N] << endl;
    fout.close();
}
