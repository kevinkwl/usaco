/*
ID: kevinli7
PROG: fence
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <set>
using namespace std;
struct Intsec
{
    Intsec():deg(0){}
    int deg;
    multiset<int> adj;  
};
int path[2048];
int pathsize, F, a, b;
int start;
Intsec g[505]; 

void dfs(int n)
{
    while (!g[n].adj.empty())
    {
        int next = *(g[n].adj.begin());
        g[n].adj.erase(g[n].adj.begin());
        g[next].adj.erase(g[next].adj.find(n));
        dfs(next);
    }
    path[pathsize] = n;
    ++pathsize;
}

int main()
{
    ifstream fin("fence.in");
    fin >> F;
    for (int i = 0; i < F; ++i)
    {
        fin >> a >> b;
        ++g[a].deg;
        ++g[b].deg;
        g[a].adj.insert(b);
        g[b].adj.insert(a);
    }
    fin.close();
    for (int i = 1; i <= 500; ++i)
    {
        if (start == 0 && g[i].deg != 0)
            start = i;
        if (g[i].deg & 1)
        {
            start = i;
            break;
        }
    }
    dfs(start);
    ofstream fout("fence.out");
    for (int i = pathsize - 1; i >= 0; --i)
        fout << path[i] << endl;
    fout.close();
}
