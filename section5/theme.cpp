/*
ID: kevinli7
PROG: theme
LANG: C++11
*/
#include <iostream>
#include <fstream>
using namespace std;
const int NMAX = 5001;
int N;
int music[NMAX];
int step[NMAX];
int ans;

int main()
{
    ifstream fin("theme.in");
    fin >> N;
    for (int i = 1; i <= N; ++i)
    {
        fin >> music[i];
        step[i-1] = music[i] - music[i-1];
    }
    fin.close();
    int cur = 0,start = 0, pos = 0;
    for (int i = 1; i <= N-ans; ++i)
        for (int j = 1; j < i; ++j)
        {
            start = i;
            cur = 1;
            pos = j;
            while (pos < i-1 && step[pos] == step[start])
            {
                ++start;
                ++cur;
                ++pos;
            }
            ans = max(ans, cur);
            if (pos == i-1)
                break;
        }
    ofstream fout("theme.out");
    fout << (ans > 4 ? ans : 0) << endl;
    fout.close();
}
