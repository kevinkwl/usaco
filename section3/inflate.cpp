/*
ID: kevinli7
PROG: inflate
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;
const int M_MAX = 10001;
const int N_MAX = 10001;
int M,N;
int score[M_MAX];
int c[N_MAX],w[N_MAX];

int main()
{
    ifstream fin("inflate.in");
    fin >> M >> N;
    for (int i = 1; i <= N; ++i)
    {
        fin >> w[i] >> c[i];
    }
    fin.close();

    for (int i = 1; i <= N; ++i)
    {
        for (int j = c[i]; j <= M; ++j)
        {
            if (score[j-c[i]] + w[i] > score[j])
                score[j] = score[j-c[i]] + w[i];
        }
    }

    ofstream fout("inflate.out");
    fout << score[M] << endl;
    fout.close();
    return 0;
}
