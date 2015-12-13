/*
ID: kevinli7
PROG: skidesign
LANG: C++11
 */
#include <iostream>
#include <fstream>
using namespace std;
#define N_max 1000
int N,h,best = 0x7fffffff;
int hill[N_max];
int solve()
{
    int i,j;
    for (i = 0, j = 17; j <= 100; ++i, ++j)
    {
        int cost = 0;
        for (int k = 0 ; k < N; ++k)
        {
            if (hill[k] < i)
                cost += (i-hill[k])*(i-hill[k]);
            if (hill[k] > j)
                cost += (hill[k]-j)*(hill[k]-j);
        }
        if (cost < best)
            best = cost;
    }
    return best;
}

int main()
{
    ifstream fin("skidesign.in");
    fin >> N;
    for (int i = 0 ; i < N; ++i)
        fin >> hill[i];
    fin.close();
    
    ofstream fout("skidesign.out");
    fout << solve() << endl;
    fout.close();
}
