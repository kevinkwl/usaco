/*
ID: kevinli7
PROG: telecow
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <queue>
#include <cstring>
using namespace std;
const int NMAX = 101;
int g[2*NMAX][2*NMAX],f[2*NMAX][2*NMAX]; // vertex u -> 2*u-1, 2*u
int N,M,s,t,dist[2*NMAX]; // start : 2*s  end: 2*t-1
bool bfs()
{
    memset(dist,-1,sizeof(dist));
    queue<int> Q;
    Q.push(s);
    dist[s-1] = 0;
    dist[s] = 1;
    int v;
    while (!Q.empty())
    {
        v = Q.front();
        Q.pop();
        for (int i = 1; i <= 2*N; ++i)
            if (dist[i] == -1 && f[v][i])
            {
                dist[i] = dist[v] + 1;
                Q.push(i);
            }
    }
    return dist[t] != -1;
}

int find(int p, int m)
{
    int a = 0;
    if (p == t)
        return m;
    for (int i = 1; i <= 2*N; ++i)
        if (f[p][i] && dist[i] == dist[p] + 1
                && (a = find(i,min(m,f[p][i]))))
        {
            f[p][i] -= a;
            f[i][p] += a;
            return a;
        }
    return 0;

}
int dinic()
{
    int flow = 0,m = 0;
    while (bfs())
        while ((m = find(s,0x7fffffff)))
            flow += m;
    return flow;
}
void reset()
{
    for (int i = 1; i <= 2*N; ++i)
        for (int j = 1; j <= 2*N; ++j)
            f[i][j] = g[i][j];
}
int main()
{
    ifstream fin("telecow.in");
    int u,v,c1,c2;
    fin >> N >> M >> c1 >> c2;
    s = 2*c1;
    t = 2*c2-1;
    for (int i = 1; i <= M; ++i)
    {
        fin >> u >> v;
        g[2*u][2*v-1] = f[2*u][2*v-1] = 1;
        g[2*v][2*u-1] = f[2*v][2*u-1] = 1;
        g[2*u-1][2*u] = f[2*u-1][2*u] = 1;
        g[2*v-1][2*v] = f[2*v-1][2*v] = 1;
    }
    fin.close();
    ofstream fout("telecow.out");
    int flow = dinic();
    int cur = 0;
    fout << flow << endl;
    for (int i = 1; i <= N; ++i)
    {
        if (i == c1 || i == c2)
            continue;
        g[2*i-1][2*i] = 0;
        reset();
        cur = dinic();
        if (cur + 1 == flow)
        {
            flow = cur;
            fout << i;
            if (flow != 0)
                fout << ' ';
        }
        else
        {
            g[2*i-1][2*i] = 1;
        }
    }
    fout << endl;
    fout.close();
}
