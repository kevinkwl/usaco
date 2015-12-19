/*
ID: kevinli7
PROG: prefix
LANG: C++11
*/
#include <iostream>
#include <map>
#include <fstream>
#include <algorithm>

using namespace std;
map<string,bool> prim;
string  sequence;
int longest[200001];


int main()
{
    ifstream fin("prefix.in");
    string s;
    for (fin >> s; s != "."; fin >> s)
    {
        prim[s] = true;
    }
    for (;fin >> s;)
        sequence += s;
    fin.close();

    int len = sequence.size();
    for (int i = len - 1; i >= 0; --i)
        for (int j = i; j <= len && j - i <= 10; ++j)
        {
            if (longest[i] == len - i)
                break;
            string s = sequence.substr(i, j-i);
            if (prim.count(s) > 0)
            {
                longest[i] = max(longest[i], longest[j] + j - i);
            }
        }
    ofstream fout("prefix.out");
    fout << longest[0] << endl;
    fout.close();

}
