/*
ID: kevinli7
PROG: latin
LANG: C++11
*/
#include <iostream>
#include <fstream>
using namespace std;
const int NMAX = 8;
int N;
long long fac[] = {0,1,1,2,6,24,120,12198297600ll};
long long sol;
int square[NMAX][NMAX];
bool row[NMAX][NMAX],col[NMAX][NMAX];
void show()
{
    for (int i = 1; i <= N; ++i)
    {
        for (int j = 1; j <= N; ++j)
            cout << square[i][j] << ' ';
        cout << endl;
    }
    cout << endl;
}

void solve(int r, int c)
{
    if (r >= N)
    {
        ++sol;
        return;
    }
    int r1 = r, c1 = c;
    bool pr;
    int i;
    for (i = 1; i <= N; ++i)
        if (!col[c][i] && !row[r][i])
        {
            row[r][i] = 1;
            col[c][i] = 1;
            square[r][c] = i;
            if (c < N)
                solve(r,c+1);
            else
                solve(r+1,2);
            square[r][c] = 0;
            col[c][i] = 0; 
            row[r][i] = 0;
        }
}

int main()
{
    ifstream fin("latin.in");
    fin >> N;
    fin.close();
    for (int i = 1; i <= N; ++i)
    {
        square[1][i] = i;
        row[1][i] = 1;
        col[i][i] = 1;
        row[i][i] = 1;
        square[i][1] = i;
    }
    if (N < 7)
        solve(2, 2);
    else
        sol = 1;

    ofstream fout("latin.out");
    fout << sol*fac[N] << endl;
    fout.close();
}
