/*
ID: kevinli7
PROG: rectbarn
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
const int MAX = 3002;
int h[MAX],l[MAX],r[MAX];
int tl[MAX],tr[MAX];
bool dmg[MAX][MAX];
int R,C,P;

int main()
{
    ifstream fin("rectbarn.in");
    fin >> R >> C >> P;
    int x,y;
    while (P--)
    {
        fin >> x >> y;
        dmg[x][y] = 1;
    }
    fin.close();
    int k;
    int ans = 0;
    for (int i = 1; i <= R; ++i)
    {
        for (int j = 1; j <= C; ++j)
            if (dmg[i][j]) 
                tl[j] = 0;
            else
                tl[j] = tl[j-1]+1;
        for (int j = C; j >= 0; --j)
            if (dmg[i][j])
                tr[j] = 0;
            else
                tr[j] = tr[j+1]+1;
        for (int j = 1; j <= C; ++j)
        {
            if (dmg[i][j])
                h[j] = tl[j] = tr[j] = l[j] = r[j] = 0;
            else
            {
                ++h[j];
                if (h[j] == 1)
                {
                    l[j] = tl[j];
                    r[j] = tr[j];
                }
                else
                {
                    l[j] = min(l[j], tl[j]);
                    r[j] = min(r[j], tr[j]);
                }
                if ((l[j]+r[j]-1)*h[j] > ans)
                    ans = (l[j]+r[j]-1)*h[j];
            }
        }
    }
    ofstream fout("rectbarn.out");
    fout << ans << endl;
    fout.close();
}

