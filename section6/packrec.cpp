/*
ID: kevinli7
PROG: packrec
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;
#define min(x,y) (((x) < (y)) ? (x):(y))
#define max(x,y) (((x) > (y)) ? (x):(y))
vector<int> s{0,1,2,3};
int l[4],w[4];
int ol[4],ow[4];
int best = 0x7fffffff;
pair<int, int> ans[2400];
bool has[300][300];
int n;
void update(int curl, int curw)
{
    int area = curl * curw;
    if (area > best)
        return;
    int bl = max(curl,curw);
    int bw = min(curl,curw);
    if (has[bl][bw])
        return;
    if (area < best)
    {
        n = 0;
        best = area;
    }
    ans[n].second = bl;
    ans[n].first = bw;
    has[bl][bw] = 1;
    ++n;
}
void cal()
{
    int curl,curw;
    int it[4],i;
    for (it[0] = 0; it[0] < 2; ++it[0])
        for (it[1] = 0; it[1] < 2; ++it[1])
            for (it[2] = 0; it[2] < 2; ++it[2])
                for (it[3] = 0; it[3] < 2; ++it[3])
                {
    for (i = 0; i < 4; ++i)
    {
        if (it[i] == 1)
        {
            l[i] = ow[i];
            w[i] = ol[i];
        }
        else
        {
            l[i] = ol[i];
            w[i] = ow[i];
        }
    }

    // case 1

    curl = max(l[s[0]],max(l[s[1]],max(l[s[2]],l[s[3]])));
    curw = w[s[0]] + w[s[1]] + w[s[2]] + w[s[3]];
    update(curl, curw);

    // case 2
    curl = w[s[0]] + max(l[s[1]], max(l[s[2]], l[s[3]]));
    curw = max(l[s[0]], w[s[1]]+w[s[2]]+w[s[3]]);
    update(curl, curw);


    // case 3
    curl = max(l[s[1]], w[s[0]]+max(l[s[2]],l[s[3]]));
    curw = w[s[1]] + max(l[s[0]], w[s[2]]+w[s[3]]);
    update(curl, curw);

    // case 4
    curl = max(l[s[0]], max(l[s[1]]+l[s[2]], l[s[3]]));
    curw = w[s[0]] + w[s[3]] + max(w[s[1]], w[s[2]]);
    update(curl, curw);

    // case 5
    curl = max(l[s[2]], max(l[s[0]]+l[s[1]], l[s[3]]));
    curw = w[s[2]] + w[s[3]] + max(w[s[0]], w[s[1]]);
    update(curl, curw);

    // case 6
    if (l[s[2]] < l[s[1]] || w[s[0]] > w[s[1]])
        continue;
    curl = max(l[s[0]]+l[s[1]], w[s[3]]+l[s[2]]);
    curw = max(w[s[0]]+l[s[3]], w[s[1]]+w[s[2]]);
    update(curl, curw);
                }
}
int main()
{
    ifstream fin("packrec.in");
    int x,y;
    for (int i = 0; i < 4; ++i)
    {
        fin >> ow[i] >> ol[i];
    }
    fin.close();
    do
    {
        cal();
    } while (next_permutation(s.begin(), s.end()));
    ofstream fout("packrec.out");
    fout << best << endl;
    sort(ans, ans + n, [](const pair<int,int>&a,const pair<int,int>&b)
            {
                return a.first < b.first;
            });
    for (int i = 0; i < n; ++i)
        fout << ans[i].first << ' ' << ans[i].second << endl;
    fout.close();
}
