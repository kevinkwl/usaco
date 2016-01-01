/*
ID: kevinli7
PROG: humble
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <set>
using namespace std;
const int KMAX = 101;
const int NMAX = 100001;
int K,N;
set<long long> hum;
long long prime[KMAX];
long long p;
long long m;
void solve()
{
    hum.insert(1);
    p = 1;
    for (int i = 1; i <= N; ++i)
    {
        for (int j = 1; j <= K; ++j)
        {
            m = *(--hum.end());   
            if (hum.size() > N + 1 && p*prime[j] > m)
                break;
            hum.insert(p*prime[j]);
        }
        while (hum.size() > N + 1)
            hum.erase(--hum.end());
        p = *(hum.upper_bound(p));
        //cout << hums[i] << endl;
    }
}

int main()
{
    ifstream fin("humble.in");
    fin >> K >> N;
    for (int i = 1; i <= K; ++i)
    {
        fin >> prime[i];
    }
    fin.close();

    solve();
    ofstream fout("humble.out");
    fout << p << endl;
    fout.close();
}
