/*
ID: kevinli7
PROG: milk3
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
int A,B,C;
int a,b;
bool vis[21][21];
int ans[21];
void dfs(int i, int j)
{
    if (vis[i][j]) 
        return;
    vis[i][j] = true;
    if (i == 0)
        ans[C-j] = 1;
    if (i != 0 && j != B)  // A->B
    {
        b = min(B, j + i);
        a = i - b + j;
        dfs(a,b);
    }
    if (i != 0)  // A->C
    {
        a = 0;
        dfs(a,j);
    }
    if (j != 0 && i != A)  // B->A
    {
        a = min(A, j + i);
        b = j - a + i;
        dfs(a,b);
    }
    if (j != 0)  // B->C
    {
        dfs(i,0); 
    }
    if (C-i-j != 0 && i != A)  // C->A
    {
        a = min(A, C-j);
        dfs(a,j);
    }
    if (C-i-j != 0)  // C->B
    {
        b = min(B, C-i);
        dfs(i,b); 
    }
    return;
}
int main()
{
    ifstream fin("milk3.in");
    fin >> A >> B >> C;
    fin.close();

    ans[C] = 1;
    dfs(0,0);
    ofstream fout("milk3.out");
    for (int i = 0; i < C; ++i)
        if (ans[i] == 1)
            fout << i << ' ';
    fout << C << endl;
    fout.close();
    
}
