/*
ID: kevinli7
PROG: fence6
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>
using namespace std;
const int NMAX = 101;
struct Seg
{
    int len;
    set<int> endpt[2];
};
Seg seg[NMAX];
int N,s,Ls,N1s,N2s,n;
int ans,start,dir;
int vis[NMAX];
void dfs(int pos, int prev, int cur)
{
    //cout << pos << ' ' << cur <<  endl;
    if (vis[pos] != -1 && pos == start)
    {
     //   cout << cur << endl;
        if (cur < ans)
            ans = cur;
        return;
    }
    else if (vis[pos] != -1 && vis[pos] < cur)
        return;
    else
    {
        vis[pos] = cur;
        cur += seg[pos].len;
        dir = (seg[pos].endpt[0].count(prev) != 0);
        for (int i : seg[pos].endpt[dir])
        {
            dfs(i,pos,cur);
        }
    }
}

int main()
{
    ifstream fin("fence6.in");
    fin >> N;
    for (int i = 1; i <= N; ++i)
    {
        fin >> s;
        fin >> seg[s].len >> N1s >> N2s;
        for (int j = 1; j <= N1s; ++j)
        {
            fin >> n;
            seg[s].endpt[0].insert(n);
        }
        for (int j = 1; j <= N2s; ++j)
        {
            fin >> n;
            seg[s].endpt[1].insert(n);
        }
    }
    fin.close();
    ans = 0x7fffffff;
    
    for (int i = 1; i <= N; ++i)
    {
       // cout << i << "  >>>>>>>>" << endl;
        fill_n(vis, N+1,-1);
        start = i;
        dfs(i,0,0);
    }

    ofstream fout("fence6.out");
    fout << ans << endl;
    fout.close();
}
