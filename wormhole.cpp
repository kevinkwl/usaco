/*
ID: kevinli7
PROG: wormhole
LANG: C++11
*/

#include <iostream>
#include <fstream>
using namespace std;
#define N_Max 12
int X[N_Max+1], Y[N_Max+1];
int to[N_Max+1];
int next_right[N_Max+1];
int N;
bool cycle_exists()
{
    for (int i = 1; i <= N; ++i)
    {
        int pos = i;
        for (int cnt = 0; cnt < N; ++cnt)
            pos = next_right[to[pos]];
        if (pos != 0)
            return true;
    }
    return false;
}
int solve()
{
    int total = 0; 
    int i;
    for (i = 1; i <= N; ++i)
    {
        if (to[i] == 0)
           break;
    }
    
    if (i > N)
    {
        if (cycle_exists())
            return 1;
        else
            return 0;
    }
    for (int j = i+1; j <= N; ++j)
    {
        if (to[j] == 0)
        {
            to[i] =j;
            to[j] =i;
            total += solve();
            to[i] = to[j] = 0;
        }
    }
   
    return total;
}
int main()
{
	ifstream fin("wormhole.in");
	ofstream fout("wormhole.out");
	fin >> N;
	for (int i = 1; i <= N; ++i)
	{
		fin >> X[i] >> Y[i];
	}
    fin.close();
    for (int i = 1; i <= N; ++i)
    {
        for (int j = 1; j <= N; ++j)
        {
            if (Y[j] == Y[i] && X[j] > X[i])
                if (next_right[i] == 0 || 
                        X[next_right[i]]-X[i] > X[j] - X[i])
                {
                    next_right[i] = j;
                }
         }   
    }
    fout << solve() << endl;
}
