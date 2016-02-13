/*
ID: kevinli7
PROG: checker
LANG: C++11
*/
#include <iostream>
#include <fstream>
using namespace std;
ofstream fout("checker.out");
bool inv1[50],inv2[50]; // inv1 x+y   inv2 x-y+13
bool inv3[20]; // col
int place[14],N,cnt;
bool canplacequeen(int row, int col)
{
    return !inv1[row+col] && !inv2[row-col+13] && !inv3[col];
}
void mark(int row, int col)
{
    place[row] = col;
    inv1[row+col] = 1;
    inv2[row-col+13] = 1;
    inv3[col] = 1;
}
void unmark(int row, int col)
{
    inv1[row+col] = 0;
    inv2[row-col+13] = 0;
    inv3[col] = 0;
}
void placeQueen(int row)
{
    if (row > N)
    {
        ++cnt;
        if (cnt < 4)
        {
            for (int i = 1; i < N; ++i)
                fout << place[i] << ' ';
            fout << place[N] << endl;
        }
        return;
    }
    for (int col = 1; col <= N; ++col)
        if (canplacequeen(row, col))
        {
            mark(row, col);
            placeQueen(row+1);
            unmark(row, col);
        }

}
int main()
{
    ifstream fin("checker.in");
    fin >> N;
    fin.close();

    placeQueen(1);

    fout << cnt << endl;
    fout.close();
}
