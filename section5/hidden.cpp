/*
ID: kevinli7
PROG: hidden
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
using namespace std;
string str,cur;
ofstream fout("hidden.out");
int L,best;
int pos[100001];
int len,k;
int compare(const char* s, int i, int j)
{
    for (k = 0; k < L; ++k)
        if (s[i+k] > s[j+k])
            return 1;
        else if (s[i+k] < s[j+k])
            return -1;
    fout << i << endl;
    fout.close();
    exit(0);
}
int main()
{
    ifstream fin("hidden.in");
    fin >> L;
    while (fin >> cur)
        str += cur;
    fin.close();
    str = str + str;
    const char* seq = str.c_str();
    int i = 0, j = 1;
    while (j < L)
    {
        if (compare(seq, i, j) > 0)
        {
            i = j;
            ++j;
        }
        else
        {
            if (k == 0) ++j;
            else        j += k+1;
        }
    }
    fout << i << endl;
    fout.close();
}
