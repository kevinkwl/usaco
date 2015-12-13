/*
ID: kevinli7
PROG: ariprog
LANG: C++11
 */

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#define N_max 25
#define M_max 251
using namespace std;
using PA = pair<int, int>;
int N, M;
bool bs[M_max*M_max*2];
int maxdiff;
int maxstart;
int maxnum;
vector<PA> ans;

void init()
{
    bs[0] = true;
    for (int i = 1; i <= M; ++i)
        for (int j = 1; j <= M; ++j)
        {
            bs[i*i] = true;
            bs[i*i+j*j] = true;
        }
}
bool dfs(int number, int diff)
{
    for (int i = 0; i < N; ++i)
    {
        if (number > maxnum || !bs[number])
        {   
            return false;
        }
        number += diff;
    }
    return true;
}

void solve()
{
   for (int start = 0; start <= maxstart; ++start)
   {
       if (!bs[start])
           continue;
       for (int i = 1; i <= maxdiff; ++i) 
       {
            if ((start + (N-1)*i <= maxnum)  && dfs(start, i))
                ans.push_back(make_pair(i, start));
       }
   }
}


int main()
{
    ifstream fin("ariprog.in");
    fin >> N >> M;
    fin.close();
    maxnum = M*M + M*M;
    maxdiff = maxnum / (N-1);
    maxstart = maxnum - N + 1;
    init();
    solve();
    ofstream fout("ariprog.out");
    stable_sort(ans.begin(), ans.end(), [](PA a, PA b){return a.first < b.first;});
    for (auto & c : ans)
        fout << c.second << ' ' << c.first << endl;
    if (ans.empty())
        fout << "NONE" << endl;
    fout.close();
}
