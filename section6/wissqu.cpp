/*
ID: kevinli7
PROG: wissqu
LANG: C++11
*/
#include <iostream>
#include <fstream>
using namespace std;
ofstream fout("wissqu.out");
char pasture[5][5];
bool used[5][5];
int herd[5];
char mov[16];
int movr[16],movc[16];
int total;
void init()
{
    herd[0] = herd[1] = herd[2] = herd[4] = 3;
    herd[3] = 4;
}
bool ok(int r, int c, char h)
{
    if (used[r][c] || pasture[r][c] == h)
        return false;
    if (pasture[r-1][c-1] == h || pasture[r-1][c] == h
        || pasture[r-1][c+1] == h || pasture[r][c+1] == h
        || pasture[r+1][c+1] == h || pasture[r+1][c] == h
        || pasture[r+1][c-1] == h || pasture[r][c-1] == h)
        return false;
    return true;
}

void dfs(int step)
{
    if (step == 17)   
    {
        if (!total)
        {
            for (int i = 0; i < 16; ++i)
                fout << mov[i] << ' ' << movr[i] << ' ' << movc[i] << endl;
        }
        ++total;
        return;
    }
    int h,r,c;
    char pre;
    for (h = 0; h < 5; ++h)
        if (herd[h])
            for (r = 1; r <= 4; ++r)
                for (c = 1; c <= 4; ++c)
                    if (ok(r, c, 'A'+h))
                    {
                        pre = pasture[r][c];

                        movr[step-1] = r;
                        movc[step-1] = c;
                        --herd[h];
                        used[r][c] = 1;
                        mov[step-1] = 'A'+h;
                        pasture[r][c] = 'A'+h;

                        dfs(step+1);

                        used[r][c] = 0;
                        ++herd[h];
                        pasture[r][c] = pre;
                    }
}

int main()
{
    ifstream fin("wissqu.in");
    char ch;
    for (int i = 1; i <= 4; ++i)
        for (int j = 1; j <= 4; ++j)
        {
            fin >> pasture[i][j];
        }

    fin.close();
    init();
    mov[0] = 'D';
    char pre;
    for (int i = 1; i <= 4; ++i)
        for (int j = 1; j <= 4; ++j)
            if (ok(i, j, 'D'))
            {
                pre = pasture[i][j];
                movr[0] = i;
                movc[0] = j;
                --herd['D'-'A'];
                pasture[i][j] = 'D';
                used[i][j] = 1;
                dfs(2);
                used[i][j] = 0;
                ++herd['D'-'A'];
                pasture[i][j] = pre;
            }
    fout << total << endl;
    fout.close();
}

