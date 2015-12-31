/*
ID: kevinli7
PROG: cowtour
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
using namespace std;
const int N_MAX = 151;
const double INF = 1000000;
int X[N_MAX], Y[N_MAX];
int N;
int adj[N_MAX][N_MAX];
int p[N_MAX], rk[N_MAX];
double ans = INF;
double newDiam = INF;
double connect = INF;
double dis[N_MAX][N_MAX];
double diam[N_MAX];
double farthest[N_MAX];

double get_distance(int i, int j)
{
    return  sqrt((X[i]-X[j])*(X[i]-X[j]) + 
                 (Y[i]- Y[j])*(Y[i]-Y[j]));
}
void make_set(int n)
{
    p[n] = n;
    rk[n] = 0;
}

int find_set(int n)
{
    if (n != p[n])
        p[n] = find_set(p[n]);
    return p[n];
}
void union_set(int i, int j)
{
    int lhs = find_set(i);
    int rhs = find_set(j);
    if (lhs == rhs)
        return;
    if (rk[lhs] < rk[rhs])
        p[lhs] = rhs;
    else
        p[rhs] = lhs;
    if (rk[lhs] == rk[rhs])
        ++rk[lhs];
}
void floyd()
{
    for (int i = 1; i <= N; ++i)        
        for (int j = 1; j <= N; ++j)
        {
            if (adj[i][j] == 1)
            {
                dis[i][j] = sqrt((X[i]-X[j])*(X[i]-X[j]) + 
                                (Y[i]- Y[j])*(Y[i]-Y[j]));
            }
            else if (i != j)
                dis[i][j] = INF ;
            else
                dis[i][j] = 0;
        }
    for (int k = 1; k <= N; ++k)
        for (int i = 1; i <= N; ++i)
            for (int j = 1; j <= N; ++j)
                if (dis[i][k] + dis[k][j] < dis[i][j])
                    dis[i][j] = dis[i][k] + dis[k][j];
    for (int i = 1; i <= N; ++i)
    {
        int rep = find_set(i);
        for (int j = 1; j <= N; ++j)
        {
            if (find_set(i) == find_set(j) && dis[i][j] > farthest[i])
            {
                farthest[i] = dis[i][j];
                if (farthest[i] > diam[rep])
                    diam[rep] = farthest[i];
            }
        }
    }
}


int main()
{
    ifstream fin("cowtour.in");
    fin >> N;
    for (int i = 1; i <= N; ++i)
    {
        fin >> X[i] >> Y[i];
        make_set(i);
    }
    char ch;
    for (int i = 1; i <= N; ++i)
    {
        for (int j = 1; j <= N; ++j)
        {
            fin >> ch;
            if (ch == '1')
            {
                adj[i][j] = 1;
                union_set(i,j);
            }
        }
    }
    fin.close();
    floyd();
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= N; ++j)
        {
            if (find_set(i) != find_set(j))
            {
                connect = farthest[i] + get_distance(i,j) + farthest[j];
                newDiam = max(max(connect,diam[find_set(j)]), diam[find_set(i)]);
                if (newDiam < ans)
                    ans = newDiam;
            }
        }

    ofstream fout("cowtour.out");
    fout << fixed << setprecision(6) << ans << endl;
    fout.close();
}
