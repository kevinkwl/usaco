/*
ID: kevinli7
PROG: ditch
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;
using ii = pair<int,int>;
const int MMAX = 201;
int M,N,c[MMAX][MMAX],res[MMAX][MMAX];
int si,ei,ci;
int pre[MMAX], cap, flow,d[MMAX],vis[MMAX];
int bfs()
{
    fill_n(pre,M+1,0);
    fill_n(d,M+1,0x7fffffff);
    fill_n(vis,M+1,0);
    queue<ii> Q;
    d[1] = 0;
    Q.push(ii(1,0));
    while (!Q.empty())
    {
        ii t = Q.front();Q.pop();
        int v = t.first,dis = t.second;
        if (vis[v])
            continue;
        vis[v] = true;
        for (int i = 1; i <= M; ++i)
            if (c[v][i] > 0)
                if (d[i] > dis + 1)
                {
                    pre[i] = v;
                    d[i] = dis + 1;
                    Q.push(ii(i,d[i]));
                }
    }
    if (d[M] == 0x7fffffff)
        return -1;
    return 1;
    
}

int main()
{
    ifstream fin("ditch.in");
    fin >> N >> M;
    for (int i = 1; i <= N; ++i)
    {
        fin >> si >> ei >> ci;
        c[si][ei] += ci;
        res[si][ei] = c[si][ei];
    }
    fin.close();
    
    while (bfs() != -1)
    {
        cap = 0x7fffffff;
        for(int i = M,j = pre[i]; j != 0; i = j,j=pre[i])
        {
            cap = min(cap, c[j][i]);
        }
        flow += cap;
        for(int i = M,j= pre[i]; j != 0; i=j, j = pre[i])
        {
            c[j][i] -= cap;
            c[i][j] += cap;
        }
    }

    ofstream fout("ditch.out");
    fout << flow << endl;
    fout.close();
}
