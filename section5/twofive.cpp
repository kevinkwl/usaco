/*
ID: kevinli7
PROG: twofive
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
int maxrow[5],maxcol[5];
long f[6][6][6][6][6];
bool used[25];
string W;
int N;

long dp(int a,int b,int c,int d,int e,int ch)
{
    long& p = f[a][b][c][d][e];
    if (p)
        return p;
    if (used[ch])
        return p = dp(a,b,c,d,e,ch+1);
    if (a < 5 && ch > maxrow[0] && ch > maxcol[a])
        p += dp(a+1,b,c,d,e,ch+1);
    if (b < a && ch > maxrow[1] && ch > maxcol[b])
        p += dp(a,b+1,c,d,e,ch+1);
    if (c < b && ch > maxrow[2] && ch > maxcol[c])
        p += dp(a,b,c+1,d,e,ch+1);
    if (d < c && ch > maxrow[3] && ch > maxcol[d])
        p += dp(a,b,c,d+1,e,ch+1);
    if (e < d && ch > maxrow[4] && ch > maxcol[e])
        p += dp(a,b,c,d,e+1,ch+1);
    return p;
}
void init(int ch, int row, int col)
{
    used[ch] = 1;
    maxrow[row] = ch;
    maxcol[col] = ch;
    memset(f,0,sizeof(f));
    f[5][5][5][5][5] = 1;
}
void solve_N()
{
    int input[5] = {0};
    long t = 0;
    int ch;
    memset(used,0,sizeof(used));
    for (int i = 0; i < 5; ++i)
        maxrow[i] = maxcol[i] = -1;
    for (int pos = 0; pos < 25; ++pos)
    {
        ++input[pos/5];
        for (ch = 0; ch < 25; ++ch)
            if (!used[ch] && ch > maxrow[pos/5] && ch > maxcol[pos%5])
            {
                init(ch,pos/5,pos%5);
                t = dp(input[0],input[1],input[2],input[3],
                        input[4],0);
                if (t < N)  N -= t;
                else        break;
                used[ch] = 0;
            }
        W += 'A' + ch;
    }
}
void solve_W()
{
    int input[5] = {0};
    int p,ch;
    memset(used,0,sizeof(used));
    for (int i = 0; i < 5; ++i)
        maxrow[i] = maxcol[i] = -1;
    for (p = 0; p < 25; ++p)
    {
        ++input[p/5];
        for (ch = 0; ch < W[p] - 'A'; ++ch)
            if (!used[ch] && ch > maxrow[p/5] && ch > maxcol[p%5])
            {
                init(ch,p/5,p%5);
                N += dp(input[0],input[1],input[2],input[3],
                        input[4],0);
                used[ch] = 0;
            }
        used[W[p] - 'A'] = 1;
        maxrow[p/5] = maxcol[p%5] = W[p] - 'A';
    }
    ++N;
}
int main()
{
    ifstream fin("twofive.in");
    ofstream fout("twofive.out");
    char ch;
    fin >> ch;
    if (ch == 'N')
    {
        fin >> N;
        solve_N();
        fout << W << endl;
    }
    else
    {
        fin >> W;
        solve_W();
        fout << N << endl;
    }
    fin.close();
    fout.close();
}
