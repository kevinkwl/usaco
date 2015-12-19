/*
ID: kevinli7
PROG: concom
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
const int N_MAX = 100;
int origin[N_MAX+1][N_MAX+1];
bool owns[N_MAX+1];
int cnt[N_MAX+1];
int n;
bool visited[N_MAX+1];

void dfs(int master)
{
    if (visited[master])
        return;
    visited[master] = true;
    for (int i = 1; i <= n; ++i)
    {
        cnt[i] += origin[master][i];
        if (cnt[i] > 50)
        {
            owns[i] = true;
            dfs(i);
        }
    }
}
int main()
{
    ifstream fin("concom.in");
    fin >> n;
    int i,j,p,size = 0;;
    for (int k = 0; k < n; ++k)
    {
        fin >> i >> j >> p;
        origin[i][j] = p;
        size = max(size, max(i, j));
    }
    n = size;
    fin.close();
    
    ofstream fout("concom.out");
  
    for (i = 1; i <= n; ++i)
    {
        fill_n(cnt + 1, n, 0);
        fill_n(visited+1, n, false);
        fill_n(owns + 1, n, false);
        dfs(i);

        for (j = 1; j <= n; ++j)
            if (owns[j] && j != i)
                fout << i << ' ' << j << endl;
    }
 
    fout.close();

}
