/*
ID: kevinli7
PROG: stamps
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <map>
using namespace std;
const int KMAX = 201;
const int NMAX = 51;
bool stamp[10001];
int use[KMAX*10000];
int st[NMAX];
int K,N;


int main()
{
    ifstream fin("stamps.in");
    fin >> K >> N;
    int k,min = 0x7fffffff, max = 0;
    for (int i = 1; i <= N; ++i)
    {
        fin >> k;
        stamp[k] = true;
        st[i] = k;
        if (k < min)
            min = k;
        if (k > max)
            max = k;
    }
    fin.close();

    for (int i = 1; i <= N; ++i)
        use[st[i]] = 1;
    int i;
    for (i = 1; use[i] && use[i] <= K; ++i)
    {
        //cout << i << ' ' << use[i] << endl;
        for (int j = 1; j <= N; ++j)
        {
            if (use[i+st[j]] == 0)
                use[i+st[j]] = use[i] + 1;
            else if (use[i+st[j]] > use[i] + 1)
                use[i+st[j]] = use[i] + 1;
        }
    }
    ofstream fout("stamps.out");
    fout << i-1 << endl;
    fout.close();
    
    
}

