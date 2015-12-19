/*
ID: kevinli7
PROG: lamps
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;
int N, C;
vector<int> on;
vector<int> off;
vector<bitset<101>> ans;

vector<vector<bitset<101>>> odd(5);
vector<bitset<101>> button(4);
unordered_map<bitset<101>, bool> visited;       

bitset<101> start;
void init()
{
    button[0].set();

    // set buttons
    for (int i = 1; i < 100; i += 2)
    {
        button[1].set(i);
        button[2].set(i+1);
    }
    for (int i = 1; i <= 100; i += 3)
        button[3].set(i);
    // set odd : multiple buttons
    odd[0].push_back(start);
    for (int i = 0; i < 4; ++i)
        odd[1].push_back(button[i]);
    for (int i = 0; i < 3; ++i)
        for (int j= i; j < 4; ++j)
        {
            bitset<101> comb = button[i] ^ button[j];
            odd[2].push_back(comb);
        }
    for (int i = 0; i < 2; ++i)
        for (int j = i; j < 3; ++j)
            for (int k = j; k < 4; ++k)
            {
                bitset<101> comb = button[i]^button[j]^button[k];
                odd[3].push_back(comb);
            }
    bitset<101> comb = button[0]^button[1]^button[2]^button[3];
    odd[4].push_back(comb);
}

bool check(bitset<101> & res)
{
    for (auto & no : on)    
        if (!res[no])
            return false;
    for (auto & no: off)
        if (res[no])
            return false;

    return true;
}

void print(bitset<101> & bits)
{
    for (int i = 1; i <= N; ++i)
        cout << bits[i];
    cout <<endl;
}
void trybuttons(vector<bitset<101>> & buttons)
{
    for (auto & bits : buttons)
    {
        start.set();
        start ^= bits;
        //print(start);
        if (check(start))
            ans.push_back(start);
    }

}

bool sortBit(const bitset<101> & lhs, const bitset<101> & rhs)
{
    string ls = lhs.to_string();
    string rs = rhs.to_string();
    reverse(ls.begin(), ls.end());
    reverse(rs.begin(), rs.end());
    return ls < rs;
}

int main()
{
    ifstream fin("lamps.in");
    fin >> N >> C;
    int no;
    for (fin >> no; no != -1; on.push_back(no), fin >> no);
    for (fin >> no; no != -1; off.push_back(no), fin >> no);
    fin.close();
    init();
    start.set();


    if (C&1)
    {
        trybuttons(odd[1]);
        if (C >= 3)
            trybuttons(odd[3]);
    }
    else
    {
        for (int i = 0; i < 5 && C >= i; i += 2)
            trybuttons(odd[i]);
    }
    ofstream fout("lamps.out");

    bitset<101> mask;
    mask.reset();
    for (int i = 1; i <= N; ++i)
        mask.set(i);
    for (auto & bits : ans)
        bits &= mask;

    if (!ans.empty())
    {
        sort(ans.begin(), ans.end(), sortBit);
        auto last = unique(ans.begin(), ans.end());
        ans.erase(last, ans.end());
    }
    for (auto & bits : ans)
    {
        //if (visited[bits])
          //  continue;
        //visited[bits] = true;
        for (int i = 1; i <= N; ++i)
        {
            fout << bits[i];
        }
        //cout << bits << endl;
        fout << endl;
    }
    if (ans.empty())
        fout << "IMPOSSIBLE" << endl;
    fout.close();
}
