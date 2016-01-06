/*
ID: kevinli7
PROG: rockers
LANG: C++11
*/
#include <iostream>
#include <fstream>
using namespace std;
const int NMAX = 20;
int N,T,M;
int song[NMAX];
int disk[NMAX];
int ans;
void tryit(int d, int s, int t)
{
    if (d >= M || s >= N)
    {
        if (t > ans)
            ans = t;
        return;
    }
    for (int i = s; s < N; ++s)
    {
        if (disk[d] + song[s] <= T)
        {
            disk[d] += song[s];
            tryit(d, s+1, t+1);
            disk[d] -= song[s];
        }
        else
            tryit(d+1, s, t);
    }
}
int main()
{
    ifstream fin("rockers.in");
    fin >> N >> T >> M;
    for (int i = 0; i < N; ++i)
        fin >> song[i];
    fin.close();
    tryit(0,0,0);
    ofstream fout("rockers.out");
    fout << ans << endl;
    fout.close();
}
