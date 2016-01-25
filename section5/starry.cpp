/*
ID: kevinli7
PROG: starry
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
using Sky = char[101][101];
const int INF = 0x7fffffff;
struct Cluster
{
    int h,w;
    Sky sky;
} cluster[26];
struct Posi
{
    int r0,c0,r1,c1;
    void reset() {r0 = INF;c0 = INF;r1 = -1;c1 = -1;}
};
int H,W,size,h,w;
Posi pos;
Sky sky, ans, now;
Cluster cur;
int d[8][2] = {{-1,-1},{-1,0},{-1,1},{0,1},{1,1},{1,0},{1,-1},{0,-1}};
void flood(Sky &sky,int i, int j, char mark)
{
    sky[i][j] = mark;
    now[i][j] = '1';
    pos.r0 = min(i,pos.r0);
    pos.r1 = max(i,pos.r1);
    pos.c0 = min(j,pos.c0);
    pos.c1 = max(j,pos.c1);
    int r,c;
    for (int s = 0; s < 8; ++s)
    {
        r = i + d[s][0];
        c = j + d[s][1];
        if (r >= 0 && r < H && c >= 0 && c < W)
            if (sky[r][c] == '1')
                flood(sky,r,c,mark);
    }
}
void show(Sky &s)
{
    for (int i = 0; i < H; ++i)
    {
        for (int j = 0; j < W; ++j)
            cout << s[i][j];
        cout << endl;
    }
    cout << endl;
    
}

void rotate()
{
    Sky tmp;
    memcpy(tmp, cur.sky, sizeof(tmp));
    for (int i = 0; i < cur.h; ++i)
        for (int j = 0; j < cur.w; ++j)
        {
            cur.sky[j][cur.h-1-i] = tmp[i][j];
        }
    swap(cur.h,cur.w);
}
void turn()
{
    for (int i = 0; i < cur.w/2; ++i)
        for (int j = 0; j < cur.h; ++j)
        {
            swap(cur.sky[j][i], cur.sky[j][cur.w-i-1]);
        }
}

bool check(int idx)
{
    if (pos.r1 - pos.r0 != cur.h - 1 || 
        pos.c1 - pos.c0 != cur.w - 1)
        return false;
    else
    {
        for (int i = 0; i < cur.h ; ++i)
            for (int j = 0; j < cur.w ; ++j)
                if (cur.sky[i][j] != now[i+pos.r0][j+pos.c0])
                    return false;
        return true;
    }
}
char search()
{
    for (int i = 0; i < size; ++i)
    {
        memcpy(cur.sky, cluster[i].sky, sizeof(cluster[i].sky));
        cur.h = cluster[i].h;
        cur.w = cluster[i].w;
        for (int op = 0; op < 2; ++op)
        {
            if (op == 1)
                turn();
            for (int se = 0; se < 4; ++se)
            {
                if (se > 0)
                    rotate();
                if (check(i))
                {
                    return 'a' + i;
                    break;
                }
            }
        }
    }
    return '0';
}
void insert()
{
    memset(&cluster[size].sky[0][0],'0',sizeof(cluster[size].sky));
    for (int i = pos.r0; i <= pos.r1; ++i)
        for (int j = pos.c0; j <= pos.c1; ++j)
        {
                cluster[size].sky[i-pos.r0][j-pos.c0] = 
                    now[i][j];
        }
    cluster[size].h = pos.r1 - pos.r0 + 1;
    cluster[size].w = pos.c1 - pos.c0 + 1;
    ++size;
}

int main()
{
    ifstream fin("starry.in");
    fin >> W >> H;
    for (int i = 0; i < H; ++i)
        for (int j = 0; j < W; ++j)
        {
            fin >> sky[i][j];
            ans[i][j] = sky[i][j];
        }
    fin.close();
    char m = '0';
    for (int i = 0; i < H; ++i)
        for (int j = 0; j < W; ++j)
            if (sky[i][j] == '1')
            {
                memset(now,'0',sizeof(now));
                pos.reset();
                flood(sky,i,j,'0');
                m = search();
                if (m == '0')
                {
                    m = 'a' + size;
                    insert();
                }
                flood(ans,i,j,m);

            }
    ofstream fout("starry.out");

    for (int i = 0; i < H; ++i)
    {
        for (int j = 0; j < W; ++j)
            fout << ans[i][j];
        fout << endl;
    }
    fout.close(); 
}
