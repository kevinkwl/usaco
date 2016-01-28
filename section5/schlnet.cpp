/*
ID: kevinli7
PROG: schlnet
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;
const int NMAX = 101;

int adj[NMAX][NMAX],tran[NMAX][NMAX];
bool vis[NMAX];
int size,comp[NMAX];
int indeg[NMAX],outdeg[NMAX];
int N;
void dfs(int i)
{
    vis[i] = true;
    int v;
    for (int j = 1; j <= adj[i][0]; ++j)
    {
        v = adj[i][j];
        if (!vis[v])
            dfs(v);
    }
}
void tdfs(int i)
{
    int v;
    comp[i] = size;
    for (int j = 1; j <= tran[i][0]; ++j)
    {
        v = tran[i][j];
        if (!comp[v] && vis[v])
            tdfs(v);
    }
}

int main()
{
    ifstream fin("schlnet.in");
    fin >> N;
    int v;
    for (int i = 1; i <= N; ++i)
    {
        fin >> v;
        while (v)
        {
            adj[i][++adj[i][0]] = v;
            tran[v][++tran[v][0]] = i;
            fin >> v;
        }
    }
    fin.close();

    
    for (int i = 1; i <= N; ++i)
    {
        if (!comp[i])
        {
            dfs(i);
            ++size;
            tdfs(i);
            memset(vis,false,sizeof(vis));
        }
    }
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= adj[i][0]; ++j)
        {
            v = adj[i][j];
            if (comp[v] != comp[i])
            {
                ++indeg[comp[v]];
                ++outdeg[comp[i]];
            }

        }
    int ans1=0,ans2=0;
    for (int i = 1; i <= size; ++i)
    {
        if (indeg[i] == 0)
            ++ans1;
        if (outdeg[i] == 0)
            ++ans2;
    }
    ofstream fout("schlnet.out");
    fout << ans1 << endl;
    fout << (size == 1 ? 0 : max(ans1,ans2)) << endl;
    fout.close(); 
 }
