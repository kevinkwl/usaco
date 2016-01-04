/*
ID: kevinli7
PROG: camelot
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <utility>
using namespace std;
#define ii pair<int,int>
#define iii pair<ii,int>
const int INF = 0x7fffffff/1000;
struct Knight
{
    int x,y;
};
Knight knt[31*27];
int kx,ky;
int dist[27][31][27][31], dc[8] = {1,2,2,1,-1,-2,-2,-1};
int dr[8] = {-2,-1,1,2,2,1,-1,-2};
int K;
bool visit[27][31];
int C,R,x,y,d,newx,newy;
char ch;
int ans,cur,wk,wkb,tkk,tkx,tky;
int ksc,kec,ksr,ker;
void init()
{
    for (int ic = 1; ic <= C; ++ic)
        for (int ir = 1; ir <= R ; ++ir)
            for (int jc = 1; jc <= C; ++jc)
                for (int jr = 1; jr <= R; ++jr)
                    dist[ic][ir][jc][jr] = INF;
}
void reset()
{
    cur = wk = wkb = tkk = tkx = tky = 0;
}
void bfs(int c, int r)
{
    fill_n(*visit,sizeof(visit),0);
    queue<iii> Q;
    Q.push(iii(ii(c,r),0));
    while (!Q.empty())
    {
        iii st = Q.front(); Q.pop();
        x = st.first.first, y = st.first.second;
        if (visit[x][y])
            continue;
        visit[x][y] = true;
        d = st.second;
        dist[c][r][x][y] = d;
        for (int i = 0; i < 8; ++i)
        {
            newx = x + dc[i];
            newy = y + dr[i];
            if (newx > 0 && newx <= C && newy > 0 && newy <= R)
                Q.push(iii(ii(newx,newy),d+1));
        }
    }
}


int main()
{
    ifstream fin("camelot.in");
    fin >> R >> C;
    fin >> ch >> ky;
    kx = ch - 'A' + 1;
    while (fin >> ch >> y)
    {
        ++K;
        knt[K].x = ch - 'A' + 1;
        knt[K].y = y;
    }
    fin.close();
    init();
    for (int c = 1; c <= C; ++c)
        for (int r = 1; r <= R; ++r)
            bfs(c,r);
    ksc = max(1, kx - 2);
    kec = min(C, kx + 2);
    ksr = max(1, ky - 2);
    ker = min(R, ky + 2);

    /*for (int i = 1; i <= C; ++i)
        for (int j = 1; j <= R; ++j)
        {
            cout << i << ' ' << j << "<<<__>>>>>>>" << endl;
            for (int ni = 1; ni <= C; ++ni)
            {
                for (int nj = 1; nj <= R; ++nj)
                    cout << dist[i][j][ni][nj] << ' ';
                cout << endl;
            }
        }*/

    for (int c = 1; c <= C; ++c)
        for (int r = 1; r <= R; ++r)
        {
            reset();
            for (int k = 1; k <= K; ++k)
            {
                cur += dist[knt[k].x][knt[k].y][c][r];
            }
            for (int kc = ksc; kc <= kec; ++kc)
                for (int kr = ksr; kr <= ker; ++kr)
                    for (int kk = 1; kk <= K; ++kk)
                    {
                        wk = dist[knt[kk].x][knt[kk].y][kc][kr] + dist[kc][kr][c][r]; 
                        wk += max(abs(kx-kc),abs(ky-kr));
                        wk = wk + cur - dist[knt[kk].x][knt[kk].y][c][r];
                        if (ans == 0 || ans > wk)
                            ans = wk;
                    }
        }
    ofstream fout("camelot.out");
    fout << ans << endl;
    fout.close();
}
