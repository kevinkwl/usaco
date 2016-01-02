/*
ID: kevinli7
PROG: butter
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <algorithm>
#include <queue>
#include <vector>
#include <utility>
using namespace std;
using ii = pair<int, int>;
const int PMAX = 801;
const int NMAX = 501;
const int INF = 300*PMAX;
struct edge
{
    edge *next;
    int v,p;
    int dist;
    bool visit;
};
edge g[PMAX];
int cow[NMAX];
int dist[PMAX];
int N,P,C;
int ans = 0x7fffffff, cur;
struct Greater
{
    bool operator()(const ii &lhs, const ii &rhs)
    {
        return lhs.second > rhs.second;      
    }
};
int main()
{
    ifstream fin("butter.in");
    fin >> N >> P >> C;
    int a,b,c;
    for (int i = 1; i <= N; ++i)
        fin >> cow[i];
    for (int i = 1; i <= C; ++i)
    {
        fin >> a >> b >> c;
        edge* e = new edge;
        e->next = g[a].next;
        e->v = b;
        e->p = c;
        g[a].next = e;
        e = new edge;
        e->next = g[b].next;
        e->v = a;
        e->p = c;
        g[b].next = e;
    }
    fin.close();

    for (int i = 1; i <= P; ++i)
    {
        for (int j = 1; j <= P; ++j)
        {
            g[j].dist = INF;
            g[j].visit = false;
        }
        g[i].dist = 0;
        priority_queue<ii,vector<ii>,Greater> Q;
        Q.push(ii(i,0));
        while (!Q.empty())
        {
            ii top = Q.top(); Q.pop();
            int V = top.first,d = top.second;

            if (!g[V].visit)
            {
                g[V].visit = true;
                for (edge * start = g[V].next;start;start = start->next)
                {
                    int n = start->v, c = start->p;
                    if (g[n].dist > g[V].dist + c)
                    {
                        g[n].dist = g[V].dist + c;
                        Q.push(ii(n,g[n].dist));
                    }
                }
            }
    
        }
        cur = 0;
        for (int i = 1; i <= N; ++i)
            cur += g[cow[i]].dist;
        if (cur < ans)
            ans = cur;
    }
    /*
     * Floyd doesn't work out :(
     *
     *
    for (int i = 1; i <= P; ++i)
        for (int j = 1; j <= P; ++j)
        {
            if (i == j)
                continue;
            dist[i][j] = (p[i][j] == 0) ? INF:p[i][j];
        }

    for (int k = 1; k <= P; ++k)
        for (int i = 1; i <= P; ++i)
            for (int j = 1; j <= P; ++j)
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
    for (int k = 1; k <= P; ++k)
    {
        cur = 0;
        for (int i = 1; i <= N; ++i)
            cur += dist[k][cow[i]];
        if (cur < ans)
            ans = cur;
    }
    */
    ofstream fout("butter.out");
    fout << ans << endl;
    fout.close();
}
