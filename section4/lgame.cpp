/*
ID: kevinli7
PROG: lgame
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <map>
using namespace std;
map<string, int> dict;
int v[26] = {2,5,4,4,1,6,5,5,1,7,6,3,5,2,3,5,7,2,1,2,4,6,6,7,5,7};
int letters[26];
string input;
int MAX;
bool check(const string &word)
{
    fill_n(letters,26,0);
    for (auto &c : input)
        ++letters[c-'a'];
    for (auto &c : word)
        --letters[c-'a'];
    for (int i = 0; i < 26; ++i)
        if (letters[i] < 0)
            return false;
    return true;
}
int cal(const string &s)
{
    int res = 0;
    for (auto &c : s)
        res += v[c-'a'];
    return res;
}

int main()
{
    ifstream fin("lgame.in");
    fin >> input;
    fin.close();
    fin.open("lgame.dict");
    string buf;
    int score = 0;
    while (fin >> buf)
    {
        if (buf == ".")
            break;
        else
        {
            if (check(buf))
            {
                score = cal(buf);
                MAX = max(score, MAX);
                dict[buf] = score;
            }
        }
    }
    fin.close();
    for (auto i = dict.begin(); i != dict.end(); ++i)
    {
        for (auto j = i; j != dict.end(); ++j)   
        {
            buf = i->first + j->first;
            if (check(buf))
            {
                score = i->second + j->second;
                if (score >= MAX)
                {
                    buf = (i->first < j->first) ? i->first + ' ' + j->first : j->first + ' ' + i->first;
                    MAX = score;
                    dict[buf] = score;
                }
            }
        }
    }
    auto i = dict.begin();
    while (i != dict.end())
    {
        if (i->second != MAX)
            i = dict.erase(i);
        else
            ++i;
    }

    ofstream fout("lgame.out");
    fout << MAX << endl;
    for (auto &p : dict)
        fout << p.first << endl;
    
}
