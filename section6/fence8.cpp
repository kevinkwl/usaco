/*
ID: kevinli7
PROG: fence8
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
const int NMAX = 55;
const int RMAX = 1040;
int board[NMAX],rail[RMAX],b[NMAX];
int railsum[RMAX], boardsum;
int N,R,l,h,m,space;
int dfsid(int curR, int maxB)
{
    if (curR <= 0) return 1;
    if (space > boardsum - railsum[m]) return 0;
    if (curR > m)   return 0;
    for (int i = maxB; i <= N; ++i)
    {
        if (b[i] >= rail[curR])
        {
            b[i] -= rail[curR];
            if (b[i] < rail[1])
                space += b[i];
            if (curR > 0 && rail[curR] == rail[curR-1])
            {
                if (dfsid(curR-1,i) == 1)
                    return 1;
            }
            else if (dfsid(curR-1,1) == 1)
                return true;
            if (b[i] < rail[1])
                space -= b[i];
            b[i] += rail[curR];
        }
    }
    return false;
}
int main()
{
    ifstream fin("fence8.in");
    fin >> N;
    for (int i = 1; i <= N; ++i)
    {
        fin >> board[i];
        boardsum += board[i];
    }
    fin >> R;
    for (int i = 1; i <= R; ++i)
        fin >> rail[i];
    fin.close();
    sort(board,board+N+1);
    sort(rail,rail+R+1);
    for (int i = 1; i <= R; ++i)
        railsum[i] = rail[i] + railsum[i-1];
    l = 0;
    h = R;
    m = (l+h)/2;
    while (l <= h)
    {
        space = 0;
        for (int i = 1; i <= N; ++i)
            b[i] = board[i];
        if (dfsid(m, 1) == 1)
            l = m+1;
        else
            h = m-1;
        m = (h+l)/2;
    }

    ofstream fout("fence8.out");
    fout << m << endl;
    fout.close();
}
