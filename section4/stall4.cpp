/*
ID: kevinli7
PROG: stall4
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
const int NMAX = 200;
const int INF = 0x7fffffff;
int match[2*NMAX+2][2*NMAX+2];
int q[NMAX*2+2];
int pre[NMAX*2+2];
int T,f,p1,N,M,S,st;

int augment(void)
{
    int mloc = 0,maxf = INF;
    fill_n(q,NMAX*2+2,0);
    fill_n(pre,NMAX*2+2,-1);
    int front = 0, tail = 0,u,v;
    for (q[front] = 0; front <= tail; ++front)
    {
        u = q[front];
        for (v = 0; v <= T && pre[T] < 0; v++)
        {
            if (match[u][v] > 0 && pre[v] < 0)
            {
                pre[v] = u;
                q[++tail] = v;
            }
        }
    }
    if (pre[T] < 0)
        return 0;
    for (u = pre[v = T]; v != 0; v = u, u = pre[u])
    {
        if (match[u][v] < maxf)
            maxf = match[u][v];
    }
    for (u = pre[v = T]; v != 0; v = u, u = pre[u])
    {
        match[u][v]--;
        match[v][u]++;
    }
    return maxf;
}

int main()
{
    ifstream fin("stall4.in");
    fin >> N >> M;
    T = N + M + 1;
    for (int i = 1; i <= N; ++i)
    {
        match[0][i] = 1;
        fin >> S;
        for (int j = 1; j <= S; ++j)
        {
            fin >> st;
            ++match[i][st+N];
            match[st+N][T] = 1;
        }
    }
    fin.close();
    while((p1 = augment()))
        f += p1;
    ofstream fout("stall4.out");
    fout << f << endl;
    fout.close();
}
