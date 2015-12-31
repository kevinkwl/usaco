/*
ID: kevinli7
PROG: agrinet
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <utility>
#include <vector>
#include <algorithm>
using namespace std;
using ii = pair<int,int>;
using iii = pair<int, ii>;
using viii = vector<iii>;
const int N_MAX = 100;
const int pmax = N_MAX*N_MAX + 100;
int N;
bool intree[N_MAX+1];
int adj[N_MAX+1][N_MAX+1];
viii edge;
int ans;
int cnt;
int p[N_MAX+1], r[N_MAX+1];
void make_set(int n)
{
    p[n] = n;
    r[n] = 0;
}
int find_set(int n)
{
    if (n != p[n])
        p[n] = find_set(p[n]);
    return p[n];
}
void union_set(int i, int j)
{
    int lhs = find_set(i),rhs = find_set(j);
    if (lhs == rhs)
        return;
    if (r[lhs] < r[rhs])
        p[lhs] = rhs;
    else
        p[rhs] = lhs;
    if (r[lhs] == r[rhs])
        ++r[lhs];
}

void kruskal()
{
    sort(edge.begin(), edge.end(), [](const iii &lhs,
                const iii &rhs)
            {
                return lhs.first < rhs.first;
            });
    for (int i = 0; i < edge.size() && cnt < N - 1; ++i)
    {
        int cost = edge[i].first;
        ii farms = edge[i].second;
        int a = farms.first, b = farms.second;
        if (!intree[a] && !intree[b])
        {
            intree[a] = intree[b] = true;
            make_set(a),make_set(b);
            union_set(a,b);
            ans += cost;
            ++cnt;
        }
        else if (intree[a] && intree[b])
        {
            if (find_set(a) == find_set(b))
                continue;
            else
            {
                union_set(a,b);
                ans += cost;
                ++cnt;
                
            }
        }
        else
        {
            int m = (intree[a])? b : a;
            int n = (intree[a])? a : b;
            intree[m] = true;
            make_set(m);
            union_set(m, n);
            ans += cost;
            ++cnt;

        }
    }
}


int main()
{
    ifstream fin("agrinet.in");
    fin >> N;

    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= N; ++j)
        { 
            fin >> adj[i][j];
            if (i > j)
            {
                edge.push_back(make_pair(adj[i][j],make_pair(i,j)));
            }
        }
    fin.close();

    kruskal();

    ofstream fout("agrinet.out");
    fout << ans << endl;
    fout.close();
}
