/*
ID: kevinli7
PROG: fence9
LANG: C++11
*/
#include <iostream>
#include <fstream>
using namespace std;
int n,m,p;
int ans;
double l,r;
int li,ri;
struct Func
{
    double k;
    double b;
    Func(int x0,int y0, int x1, int y1)
    {
        k = (x0*1.0-x1)/(y0*1.0-y1);
        b = x0*1.0 - k*y0;
    }
    double operator()(int y)
    {
        return k*y + b;
    }
};
int main()
{
    ifstream fin("fence9.in");
    fin >> n >> m >> p;
    fin.close();
    Func lhs(0,0,n,m);
    Func rhs(n,m,p,0);
    for (int i = 1; i <= m-1; ++i)
    {
        l = lhs(i);
        r = rhs(i);
        li = l + 1;
        ri = r;
        ri = (r > ri)? ri: ri - 1;
        ans += ri - li + 1;
    }
    ofstream fout("fence9.out");
    fout << ans << endl;
    fout.close();
}
