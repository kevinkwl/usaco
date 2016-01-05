/*
ID: kevinli7
PROG: range
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;
const int NMAX = 250;
int field[NMAX][NMAX];
int le[NMAX][NMAX];
int up[NMAX][NMAX];
int len[NMAX][NMAX];
int N;
int eat[NMAX+1];
int cur;
void explore(int r, int c) // -1:down 1:right 0:both
{
    int test = 1;
    int i;
    for (i = 1; r + i < N && c + i < N; ++i)
    {
        test = 1;
        for (int m = r; m <= r + i; ++m)
            test &= field[m][c+i];
        for (int m = c; m <= c + i; ++m)
            test &= field[r+i][m];
        if (test)
            ++eat[i+1];
        else
            break;
    }
}

int main()
{
    ifstream fin("range.in");
    fin >> N;
    char ch;
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
        {
            fin >> ch;
            field[i][j] = ch - '0';
        }
    fin.close();

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
        {
            if (field[i][j] == 1)
            {
                le[i][j] = 1;
                up[i][j] = 1;
                if (j > 0)
                    le[i][j] += le[i][j-1];
                if (i > 0)
                    up[i][j] += up[i-1][j];
                len[i][j] = 1;
                if (i == 0 || j == 0)
                    continue;
                cur = min(len[i-1][j-1] + 1, min(le[i][j],up[i][j]));
                len[i][j] = cur;
                if (cur > 1)
                    for (int k = 2; k <= cur; ++k)
                        ++eat[k];
            }
        }

    ofstream fout("range.out");
    for (int i = 2; i <= NMAX; ++i)
        if (eat[i])
            fout << i << ' ' << eat[i] << endl;
    fout.close();
}
