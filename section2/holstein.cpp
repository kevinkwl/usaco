/*
ID: kevinli7
PROG: holstein
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;
#define V_MAX 26
#define G_MAX 16
int V;
vector<int> need(V_MAX);
int G, vi;
vector<vector<int>> feeds(G_MAX);

int min_amount;
vector<int> feed;

int check(vector<int> & all)
{
    int has = 0;
    for (int i = 1; i <= V; ++i)
    {
        has = 0;
        for (int j = 0; j < all.size(); ++j)
        {
            has += feeds[all[j]][i-1];       
        }
        if (has < need[i])
            return false;
    }
    return true;
}
void solve()
{
    queue<vector<int>> bfs;
    for (int i = 1; i <= G; ++i)
    {
        vector<int> t = {i};
        bfs.push(t);
    }
    while(!bfs.empty())
    {
        vector<int> cur = bfs.front();
        bfs.pop();
        if (check(cur))
        {
            min_amount = cur.size();
            feed = cur;
            break;
        }
        int back = cur.back();
        for (++back; back <= G; ++back)
        {
            vector<int> tobfs(cur);
            tobfs.push_back(back);
            bfs.push(tobfs);
        }

    }

}

int main()
{
    ifstream fin("holstein.in");
    fin >> V;
    for (int i = 1; i <= V; ++i)
        fin >> need[i];
    fin >> G;
    for (int i = 1; i <= G; ++i)
        for (int j = 1; j <= V; ++j)
        {   
            fin >> vi;
            feeds[i].push_back(vi);
        }
    fin.close();

    solve();

    ofstream fout("holstein.out");
    fout << min_amount;
    for (int i = 0; i < min_amount; ++i)
        fout << ' ' << feed[i];
    fout << endl;
    fout.close();


}
