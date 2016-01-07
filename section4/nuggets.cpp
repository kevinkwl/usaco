/*
ID: kevinli7
PROG: nuggets
LANG: C++11
*/
#include <iostream>
#include <fstream>
using namespace std;
const int MAX = 257;
const int NMAX = 11;
const long long TMAX = 65536;
int opt[NMAX];
int N,seq;
long long ans;
bool valid[MAX];
int main()
{
    ifstream fin("nuggets.in");
    fin >> N;
    for (int i = 1; i <= N; ++i)
    {
        fin >> opt[i];
    }
    fin.close();
    valid[0] = true;
    for (long long i = 1; i <= TMAX*10 ;++i)
    {
        valid[i%257] = false;
        for (int j = 1; j <= N; ++j)
        {
            if (i >= opt[j])
                if (valid[(i-opt[j])%257])
                {
                    valid[i%257] = true;
                    ++seq;
                    break;
                }
        }
        if (!valid[i%257])
        {
            ans = i;
            seq = 0;
        }
        if (seq >= 256)
            break;
    }
    ofstream fout("nuggets.out");
    fout << ((ans > TMAX ) ? 0: ans) << endl;
    fout.close();
}

