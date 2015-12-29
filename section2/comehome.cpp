/*
ID: kevinli7
PROG: comehome
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <cctype>
#include <queue>
using namespace std;
const int INF = 0x7fffffff;
const int P_MAX = 10000;
struct pasture
{
    bool hasCow;
    bool visited;
    int dist;
    vector<pair<int, int>> path;
};
pasture field[100];
int P;

int index(char ch)
{
    return (ch == 'Z')? 0:((isupper(ch))? 
            ch - 'A' + 1: ch - 'a' + 26);
}
bool comp(const pair<int,int> &a, const pair<int,int> &b)
{
    return a.second > b.second;
}
void dijkstra()
{
    field[0].dist = 0;
    priority_queue<pair<int, int>, vector<pair<int,int>>, greater<pair<int,int>>> pqueue;
    pqueue.push(make_pair(0,0));
    for (int i = 1; i < 52; ++i)
    {
        field[i].dist = INF;
        field[i].visited = false;
    }    
    while (!pqueue.empty())
    {
        pair<int,int> cur = pqueue.top();pqueue.pop();
        int v = cur.second, d = cur.first;

        if (d <= field[v].dist)
        {
            for (auto p : field[v].path)
            {
                if (field[p.first].dist > field[v].dist + p.second)
                {
                    field[p.first].dist = field[v].dist + p.second;
                    pqueue.push(make_pair(field[p.first].dist,p.first));
                }
            }
        }

    }
}

int main()
{
    ifstream fin("comehome.in");
    fin >> P;
    char a,b;
    int d;
    for (int i = 1; i <= P; ++i)
    {
        fin >> a >> b >> d;
        int f = index(a), t = index(b);
        field[f].path.push_back(make_pair(t, d));
        field[t].path.push_back(make_pair(f, d));
        field[f].hasCow = field[t].hasCow = false;
        if (isupper(a))
            field[f].hasCow = true;
        if (isupper(b))
            field[t].hasCow = true;
    }
    fin.close();
    
    dijkstra();
    int ans = INF;
    int pas = 0;
    for (int i = 1; i < 52; ++i)
        if (field[i].hasCow && field[i].dist < ans)
        {
            ans = field[i].dist;
            pas = i;
        }

    ofstream fout("comehome.out");
    fout << char('A' + pas - 1) << ' '<< ans << endl;
}

