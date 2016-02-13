/*
ID: kevinli7
PROG: betsy
LANG: C++11
*/
#include <iostream>
#include <fstream>
using namespace std;
bool vis[9][9];
int cnt, N;
int dr[] = {-1, 0, 1, 0}, dc[] = {0, 1, 0, -1};
inline int getfree(int i, int j)
{
    int m = 0,k,di,dj;
    for (k = 0; k < 4; ++k)
    {
        di = i + dr[k];
        dj = j + dc[k];
        if (!vis[di][dj])
            ++m;
    }
    return m;
}
void dfs(int i, int j, int step)
{
    if (i == N && j == 1)
    {
        if (step == N*N)
            ++cnt;
        return;
    }
    if ((vis[i][j-1] && vis[i][j+1] && !vis[i-1][j] && !vis[i+1][j]) ||
        (vis[i-1][j] && vis[i+1][j] && !vis[i][j-1] && !vis[i][j+1]))
        return;
    int di,dj,k,d = 0,free,ki,kj;
    for (k = 0; k < 4; ++k)
    {
        di = i + dr[k];
        dj = j + dc[k];
        if (vis[di][dj] || (di == N && dj == 1))
            continue;
        free = getfree(di,dj);
        if (free <= 1)
        {
            ++d;
            ki = di;
            kj = dj;
        }
    }
    if (d > 1)  return;
    else if (d == 1)
    {
        vis[ki][kj] = 1;
        dfs(ki, kj, step+1);
        vis[ki][kj] = 0;
    }
    else
        for (k = 0; k < 4; ++k)
        {
            di = i + dr[k];
            dj = j + dc[k];
            if (!vis[di][dj])
            {
                vis[di][dj] = 1;
                dfs(di, dj, step+1);
                vis[di][dj] = 0;
            }
        }
}

int main()
{
    ifstream fin("betsy.in");
    fin >> N; 
    fin.close();
    vis[1][1] = 1;
    for (int i = 0; i <= N+1; ++i)
        vis[0][i] = vis[i][0] = vis[i][N+1] = vis[N+1][i] = 1;

    dfs(1, 1, 1);

    ofstream fout("betsy.out");
    fout << cnt << endl;
    fout.close();
}
