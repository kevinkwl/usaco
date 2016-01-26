/*
ID: kevinli7
PROG: milk4
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
using namespace std;
const int PMAX = 101;
int pv[PMAX];
int Q,P,depth;
bool dp[20001];
int pail[PMAX];

bool check()
{
    memset(dp, false, sizeof(dp));
    dp[0] = 1;
    for (int i = 1; i <= depth; ++i)
    {
        for (int j = pail[i]; j <= Q; ++j)
            dp[j] |= dp[j-pail[i]];
    }
   
    return dp[Q];

}
bool dfs(int p, int d)
{
    if (p > P)
    {
        if (d != depth)
            return false;
        if (check())
            return true;
        return false;
    }
    pail[d] = pv[p];
    if (d == depth && check())
        return true;
    if (d < depth && dfs(p+1,d+1))
        return true;
    if (d + P - p > depth && dfs(p+1,d))
        return true;

    return false;
}

int main()
{
    ifstream fin("milk4.in");
    fin >> Q >> P;
    for (int i = 1; i <= P; ++i)
        fin >> pv[i];
    sort(&pv[1], &pv[P+1]);
    fin.close();
    ofstream fout("milk4.out");
    for (int i = 1; i <= P; ++i)
    {
        depth = i;
        if (dfs(1,1))
        {
            fout << i;
            for (int j = 1; j <= i; ++j)
                fout << ' ' << pail[j];
            fout << endl;
            break;
        }
    }
    fout.close();
}
