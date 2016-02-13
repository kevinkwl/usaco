/*
ID: kevinli7
PROG: clocks
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
int Move[10][10] = {
    {0},
    {0,1,1,0,1,1,0},
    {0,1,1,1,0},
    {0,0,1,1,0,1,1,0},
    {0,1,0,0,1,0,0,1,0},
    {0,0,1,0,1,1,1,0,1,0},
    {0,0,0,1,0,0,1,0,0,1},
    {0,0,0,0,1,1,0,1,1,0},
    {0,0,0,0,0,0,0,1,1,1},
    {0,0,0,0,0,1,1,0,1,1},
};
int bit[10];
int clocks[10];
int mov[50];
bool vis[1<<20];
int encode()
{
    int c = 0;
    for (int i = 1; i <= 9; ++i)
        c += clocks[i]*bit[i];
    return c;
}
bool check()
{
    for (int i = 1; i <= 9; ++i)
        if (clocks[i] != 3)
            return false;
    return true;
}
void make_move(int k, int rev)
{
        for (int j = 1; j <= 9; ++j)
        {
            clocks[j] += rev*Move[k][j];
            clocks[j] += 4;
            clocks[j] %= 4;
        }
}
void show()
{
    for (int j = 1; j <= 9; ++j)
        cout << clocks[j] << ' ';
    cout << endl << "---------------" << endl;
}
bool dfsid(int step, int depth, int start)
{
    if (step >= depth)
    {
        if (check())
            return true;
        return false;
    }
    int code;
    int i,j,k;
    for (i = start; i <= 9; ++i)
    {
        mov[step] = i;
        make_move(i,1);
        code = encode();
        if (!vis[code])
        {
            vis[code] = 1;
            if (dfsid(step+1, depth, i))
                return true;
        }
        make_move(i,-1);
    }
    return false;
}
int main()
{
    ifstream fin("clocks.in");
    int c, cnt = 0;
    for (int i = 1; i <= 9; ++i)
    {
        fin >> c;
        clocks[i] = (c-3)/3;       // represent as 0,1,2,3
        if (c == 12)
            ++cnt;
    }
    fin.close();
    ofstream fout("clocks.out");
    if (cnt == 9)
        exit(0);
    bit[1] = 1;
    for (int i = 2; i <= 9; ++i)
        bit[i] = 4*bit[i-1];
    for (int i = 1; i <= 40; ++i)
    {
        memset(vis, 0, sizeof(vis));
        if (dfsid(0,i,1))
        {
            for (int j = 0; j < i; ++j)
                if (j != 0)
                    fout << ' ' << mov[j];
                else
                    fout << mov[j];
            fout << endl;
            fout.close();
            exit(0);
        }
    }
}
