/*
ID: kevinli7
PROG: latin
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
const int NMAX = 8;
int N;
long long fac[] = {0,1,1,2,6,24,120,720};
long long sol;
int square[NMAX][NMAX];
bool row[NMAX][NMAX],col[NMAX][NMAX];
long long h[NMAX][NMAX*NMAX];
bool v[NMAX];

long long solve(int r, int c)
{
    if (r >= N)
        return 1;
    if (r == 3 && c == 2) 
    {
        memset(v,0,sizeof(v));
        int i=0,j=1;
        for (int k = 1;k <= N; ++k)
        {
            if (v[k]) continue;
            v[k] = 1;
            int n = 1;
            for (int l = square[2][k];l != k; l = square[2][l])
            {
                v[l] = 1;
                ++n;
            }
            ++i;
            j*=n;
        }
        if (h[i][j] != -1)  return h[i][j];
        int res = 0;
        for (int k = 1; k <= N; ++k)
            if (!col[c][k] && !row[r][k])
            {
                row[r][k] = 1;
                col[c][k] = 1;
                square[r][c] = k;
                if (c < N)
                    res += solve(r,c+1);
                else
                    res += solve(r+1,2);
                square[r][c] = 0;
                col[c][k] = 0; 
                row[r][k] = 0;
            }
        return h[i][j] = res;
    }
    int i,res = 0;
    for (i = 1; i <= N; ++i)
        if (!col[c][i] && !row[r][i])
        {
            row[r][i] = 1;
            col[c][i] = 1;
            square[r][c] = i;
            if (c < N)
                res += solve(r,c+1);
            else
                res += solve(r+1,2);
            square[r][c] = 0;
            col[c][i] = 0; 
            row[r][i] = 0;
        }
    return res;
}

int main()
{
    ifstream fin("latin.in");
    fin >> N;
    fin.close();
    memset(h,-1,sizeof(h));
    for (int i = 1; i <= N; ++i)
    {
        square[1][i] = i;
        row[1][i] = 1;
        col[i][i] = 1;
        row[i][i] = 1;
        square[i][1] = i;
    }
    sol = solve(2,2);
    ofstream fout("latin.out");
    fout << sol*fac[N] << endl;
    fout.close();
}
