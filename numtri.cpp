/*
ID: kevinli7
PROG: numtri
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
#define R_max 1000
int R, a[R_max+1][R_max+1],d[R_max+1][R_max+1];

int solve(int i, int j)
{
    if (d[i][j] >= 0) return d[i][j];
    return d[i][j] = a[i][j] + (i==R?0:max(solve(i+1,j),solve(i+1,j+1)));
}

int main()
{
    ifstream fin("numtri.in");
    fin >> R;
    memset(a,0,sizeof(a));
    for (int i = 1; i <= R; ++i)
        for (int j = 1; j <= i; ++j)
            fin >> a[i][j];
    fin.close();

    memset(d, -1, sizeof(d));

    ofstream fout("numtri.out");
    fout << solve(1,1) << endl;
    
    fout.close();

}
