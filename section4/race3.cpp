/*
ID: kevinli7
PROG: race3
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
using namespace std;
const int NMAX = 51;
int g[NMAX][NMAX],origin[NMAX][NMAX];
int vis[NMAX];
int N,size, unavoid[NMAX],spl[NMAX],size1;
void remove(int p)
{
    for (int i = 0; i <= N; ++i)
        g[p][i] = g[i][p] = 0;
}
void reset(int p)
{
    for (int i = 0; i <= N; ++i)
    {
        g[p][i] = origin[p][i];
        g[i][p] = origin[i][p];
    }
}
void dfs(int s,int t,bool& flag, int mark)
{
    if (vis[s])
    {
        if (vis[s] != mark)
            flag = true;
        return;
    }
    vis[s] = mark;
    if (s == t)
        return;
    for (int i = 0; i <= N; ++i)
        if (g[s][i] == 1)
            dfs(i,t,flag,mark);
}
void show()
{
    for (int i = 0; i <= N; ++i)
    {
        cout << vis[i] << ' ';
    }
    cout << endl;
}
int main()
{
    ifstream fin("race3.in");
    int to;
    for (N = 0;;++N)
    {
        fin >> to;
        if (to == -1)
            break;
        if (to == -2)
            continue;
        g[N][to] = 1;
        origin[N][to] = 1;
        for (fin >> to; to != -2; fin >> to)
        {
            g[N][to] = 1;
            origin[N][to] = 1;
        }
    }
    fin.close();
    --N;
    bool flag;
    for (int i = 1; i < N; ++i)
    {
        fill_n(vis,N+1,0);
        remove(i);    
        dfs(0,N,flag,1);
        if (!vis[N])
        {
            unavoid[size++] = i;
        }
        reset(i);
    }
    ofstream fout("race3.out");
    fout << size;
    for (int i = 0; i < size; ++i)
        fout <<' ' << unavoid[i];
    fout << endl;

    for (int i = 0; i < size; ++i)
    {
        fill_n(vis,N+1,0);
        flag = false;
        dfs(0, unavoid[i],flag,-1);
        vis[unavoid[i]] = 0;
        dfs(unavoid[i],N,flag,1);
        if (!flag)
            spl[size1++] = unavoid[i];
    }

    fout << size1;
    for (int i = 0; i < size1; ++i)
        fout << ' ' << spl[i];
    fout << endl;
    fout.close();
}
