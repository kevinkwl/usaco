/*
ID: kevinli7
PROG: msquare
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <queue>
#include <utility>
#include <set>
#include <algorithm>
#include <string>
using namespace std;
using ii = pair<string, string>;
set<string> visited;
string trans_A(string & origin)
{
    string s = origin;
    swap(s[0],s[4]);
    swap(s[1],s[5]);
    swap(s[2],s[6]);
    swap(s[3],s[7]);
    return s;
}
string trans_B(string & origin)
{   
    string s = origin.substr(0,3);
    s = origin[3] + s + origin[7];
    s += origin.substr(4,3);
    return s;
}
string trans_C(string & origin)
{
    string s = origin;
    swap(s[1],s[2]);
    swap(s[1],s[6]);
    swap(s[1],s[5]);
    return s;
}

int main()
{
    ifstream fin("msquare.in");
    string str;
    string str_;
    string ch;
    for (int i = 0; i < 4; ++i)
    {
        fin >> ch;
        str += ch;
    }
    for (int i = 0; i < 4; ++i)
    {
        fin >> ch;
        str_ = ch + str_;
    }
    str += str_;
    fin.close();
    ofstream fout("msquare.out");
    string origin = "12348765";
    string ans;
    queue<ii> transform;
    transform.push(ii(origin, ""));
    visited.insert(origin);
    while (!transform.empty())
    {
        ii state = transform.front();transform.pop();
        string cur = state.first;
        string trans = state.second;
        if (cur == str)
        {
            ans = trans;
            break;
        }
        string A = trans_A(cur);
        if (!visited.count(A))
        {
            visited.insert(A);
            transform.push(ii(A, trans + "A"));
        }
        string B = trans_B(cur);
        if (!visited.count(B))
        {
            visited.insert(B);
            transform.push(ii(B, trans+ "B"));
        }
        string C = trans_C(cur);
        if (!visited.count(C))
        {
            visited.insert(B);
            transform.push(ii(C, trans + "C"));
        }
    }
    fout << ans.size() << endl;
    int cnt;
    for (char & ch : ans)
    {
        if (cnt == 60)
        {
            fout << endl;
            cnt = 0;
        }
        fout << ch;
        ++cnt;
    }
    fout << endl;
    fout.close();
}

