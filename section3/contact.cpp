/*
ID: kevinli7
PROG: contact
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <utility>
using namespace std;
using is = pair<int, string>;
const int MAX = (1<<13)-1;
int A,B,N;
string record;
string pattern;
int freq[MAX+1];
vector<is> ans;
int cnt1, cnt2, cur;

int shash(const string & s)
{
    int index = 1;
    for (auto & c : s)
        index = (index<<1) + (c - '0');
    return index;
}

string str(int n)
{
    string res = "";
    while (n >= 2)
    {
        res = to_string(n&1) + res;
        n >>= 1;
    }
    return res;
}

int main()
{
    ifstream fin("contact.in");
    fin >> A >> B >> N;
    string s;
    for (; fin >> s;)
        record += s;
    fin.close();

    for (int i = 0; i < record.size(); ++i)
        for (int j = A; j <= B && i + j <= record.size(); ++j)
        {
            pattern = record.substr(i,j);
            ++freq[shash(pattern)];
        }
    for (int i = 0; i <= MAX; ++i)
        if (freq[i] != 0)
            ans.push_back(is(freq[i], str(i)));
    sort(ans.begin(), ans.end(),[](const is &a, const is &b)
            {
                if (a.first != b.first)
                    return a.first > b.first;
                else if (a.second.size() != b.second.size())
                    return a.second.size() < b.second.size();
                else
                    return a.second < b.second;
            });

    ofstream fout("contact.out");
    for (int i = 0; i < ans.size() && cnt1 < N;)
    {
        cnt2 = 0;
        cur = ans[i].first;
        fout << cur << endl << ans[i].second;
        ++cnt2;
        while (ans[++i].first == cur)
        {
            if (cnt2 == 6)
            {
                fout << endl << ans[i].second;
                cnt2 = 1;
                continue;
            }
            else
                fout << ' ' << ans[i].second; 
            ++cnt2;
        }
        fout << endl;
        ++cnt1;
    }
    fout.close();
}

