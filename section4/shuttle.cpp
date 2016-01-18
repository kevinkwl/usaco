/*
ID: kevinli7
PROG: shuttle
LANG: C++11
*/
#include <iostream>
#include <fstream>
using namespace std;
int seq[2][1000];
int len,N,total;
void print(ostream & os)
{
    int i;
    for (i = 1; i <= total; ++i)
    {
        os << seq[0][i];
        if (i%20 == 0 || i == total) 
            os << endl;
        else   
            os << ' '; 
    }
}
int main()
{
    ifstream fin("shuttle.in");
    fin >> N;
    seq[0][1] = 1;
    seq[0][2] = 3;
    seq[0][3] = 2;
    len = 2;
    total = 3;
    int k,newlen;
    // use the previous movement sequences to generate new one
    // the first part is change WWW_BBB to BWBWBW_
    // or WW_BB to _BWBW (odd or even)
    // then make several movements such that the head and tail are done
    // e.g. BBW_W
    // then use the previous part to complete the middle part (plus 1)
    for (int i = 2; i <= N; ++i)
    {
        for (int j = 1; j <= len; ++j)
            seq[1][j] = seq[0][j] + 1;
        k = len;
        if (i&1)
        {
            for (int n = 0; n <= i; ++n)
                seq[1][++k] = 2*n+1;
            newlen = k;
            for (int n = i; n > 0; --n)
                seq[1][++k] = 2*n;
        }
        else
        {
            for (int n = i; n >= 0; --n)
                seq[1][++k] = 2*n+1;
            newlen = k;
            for (int n = 1; n <= i; ++n)
                seq[1][++k] = 2*n;
        }
        for (int j = len+1; j <= total; ++j)
            seq[1][++k] = seq[0][j] + 1;
        len = newlen;
        total = k;
        for (int m = 1; m <= total; ++m)
            seq[0][m] = seq[1][m];
    }
    ofstream fout("shuttle.out");
    print(fout);
    fout.close();
}
