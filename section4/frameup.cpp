/*
ID: kevinli7
PROG: frameup
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <utility>
using namespace std;
struct Frame
{
    int r0,r1,c0,c1;
    Frame() 
    {
        r0 = 0x7fffffff;
        r1 = -1;
        c0 = 0x7fffffff;
        c1 = -1;
    }
    void set(int i, int j)
    {
        r0 = min(i, r0);
        r1 = max(r1, i);
        c0 = min(j, c0);
        c1 = max(c1,j);
    }
} pos[26];
ifstream fin("frameup.in");
ofstream fout("frameup.out");
const int HMAX = 30;
const int WMAX = 30;
bool reg[26], used[26];
int frame[26][26],deg[26];
char b[HMAX][WMAX];
char ans[26];
int H,W,cnt;
void construct()
{
    char t,s;
    for (int i = 0; i < 26; ++i)
    {
        t = 'A' + i;
        if (reg[i])
        {
            for (int j = pos[i].r0; j <= pos[i].r1; ++j)
            {
                if (b[j][pos[i].c0] != t)
                {
                    s = b[j][pos[i].c0];
                    if (frame[i][s-'A'] == 0)
                    {
                        frame[i][s-'A'] = 1;
                        ++deg[s-'A'];
                    }
                }
                if (b[j][pos[i].c1] != t)
                {
                    s = b[j][pos[i].c1];
                    if (frame[i][s-'A'] == 0)
                    {
                        frame[i][s-'A'] = 1;
                        ++deg[s-'A'];
                    }
                }
            }
            for (int j = pos[i].c0 + 1; j < pos[i].c1; ++j)
            {
                if (b[pos[i].r0][j] != t)
                {
                    s = b[pos[i].r0][j];
                    if (frame[i][s-'A'] == 0)
                    {
                        frame[i][s-'A'] = 1;
                        ++deg[s-'A'];
                    }
                }
                if (b[pos[i].r1][j] != t)
                {
                    s = b[pos[i].r1][j];
                    if (frame[i][s-'A'] == 0)
                    {
                        frame[i][s-'A'] = 1;
                        ++deg[s-'A'];
                    }
                }
            }
        }
    }
}
void solve(int p)
{
    if (p == cnt)
    {
        for (int i = 0; i < cnt; ++i)
            fout << ans[i];
        fout << endl;
        return;
    }
    for (int i = 0; i < 26; ++i)
        if (reg[i])
        {
            if (deg[i] == 0 && !used[i])
            {
                ans[p] = 'A' + i;
                used[i] = true;
                for (int j = 0; j < 26; ++j)
                    if (frame[i][j])
                        --deg[j];
                solve(p+1);
                used[i] = false;
                for (int j = 0; j < 26; ++j)
                    if (frame[i][j])
                        ++deg[j];
            }
        }
    
}
int main()
{
    fin >> H >> W;
    for (int i = 0; i < H; ++i)
        for (int j = 0; j < W; ++j)
        {
            fin >> b[i][j];
            char & c = b[i][j];
            if (c != '.')
            {
                pos[c-'A'].set(i,j);
                if (!reg[c-'A'])
                    ++cnt;
                reg[c-'A'] = true;
            }
        }
    construct();
    solve(0);
    fin.close();
    fout.close();
    
}

