/*
ID: kevinli7
PROG: milk6
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>
#include <cstring>
#include <set>
using namespace std;
const int NMAX = 33;
const int MMAX = 1001;
struct Edge
{
    int id;
    long long c;
    int u,v;
};
long long g[NMAX][NMAX],c;
long long f[NMAX][NMAX];
int u,v,M,N;
Edge e[MMAX];
bool vis[NMAX];
int pre[NMAX];
int dist[NMAX];
bool bfs()
{
    queue<int> q;
    q.push(1);
    memset(dist,-1,sizeof(dist));
    dist[1] = 0;
    while (!q.empty())
    {
        u = q.front(); q.pop();
        for (int i = 1; i <= N; ++i)
            if (dist[i] == -1 && f[u][i])
            {
                dist[i] = dist[u] + 1;
                q.push(i);
            }
    }
    return dist[N] != -1;

}
long long find(int x, long long m)
{
    long long a = 0;
    if (x == N)
        return m;
    for (int i = 1; i <= N; ++i)
        if (f[x][i] && dist[i] == dist[x] + 1 && 
                (a = find(i,min(m,f[x][i]))))
        {
            f[x][i] -= a;
            f[i][x] += a;
            return a;
        }
    return 0;
}

long long dinic()
{
    long long flow = 0;
    long long m = 0;
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= N; ++j)
            f[i][j] = g[i][j];
    while (bfs())
    {
        while ((m = find(1,0x7fffffff)))
            flow += m;
    }
    return flow;
}

int main()
{
    ifstream fin("milk6.in");
    fin >> N >> M;
    for (int i = 1; i <= M; ++i)
    {
        fin >> e[i].u >> e[i].v >> c;
        e[i].id = i;
        e[i].c = c*1001+1;
        g[e[i].u][e[i].v] += c*1001+1;
    }
    fin.close();
    long long flow = dinic();
    ofstream fout("milk6.out");
    fout << flow/1001 << ' ' << flow%1001 << endl;
    long long del = 0;
    long long cur = flow;
    set<int> ans;
    sort(&e[1], &e[M+1],[](const Edge& a,const Edge& b)
            {
                if (a.c > b.c)
                    return true;
                else if (a.c == b.c)
                    return a.id < b.id;
                return false;
            });
    for (int i = 1; i <= M; ++i)
    {
        if (e[i].c > cur)
            continue;
        g[e[i].u][e[i].v] -= e[i].c;
        del = dinic();
       // cout << del/1001 << ' ' << e[i].c/1001 << endl;
        if (cur - del == e[i].c)
        {
            ans.insert(e[i].id);
            cur = del;
        }
        else
        {
            g[e[i].u][e[i].v] += e[i].c;
            del = 0;
        }
        if (cur <= 0)
            break;
    }
        //if (vis[e[i].u] && !vis[e[i].v]) 
          //  fout << i << endl;
    for (auto iter = ans.begin(); iter != ans.end(); ++iter)
        fout << *iter << endl;
    fout.close();
    
}

