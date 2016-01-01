/*
ID: kevinli7
PROG: ratios
LANG: C++11
*/
#include <iostream>
#include <fstream>
using namespace std;
int ga,gb,gc;
int a1,b1,c1;
int a2,b2,c2;
int a3,b3,c3;
int x1,x2,x3;
int g;
int get(int a1,int b1,int c1,int a2,int b2, int c2,int a3,int b3,int c3)
{
    return a1*b2*c3+a2*b3*c1+b1*c2*a3-a3*b2*c1-a2*b1*c3-b3*c2*a1;
}

int main()
{
    ifstream fin("ratios.in");
    fin >> ga >> gb >> gc;
    fin >> a1 >> b1 >> c1 >> a2 >> b2 >> c2 >> a3 >> b3 >> c3;
    fin.close();
    
    ofstream fout("ratios.out");
    g = get(a1,b1,c1,a2,b2,c2,a3,b3,c3);
    if (g == 0)
    {
        fout << "NONE" << endl;
        return 0;
    }
    int i;
    for (i = 1; i <= 100; ++i)
    {
        x1 = get(i*ga,i*gb,i*gc,a2,b2,c2,a3,b3,c3);
        if (x1/g < 0 || x1%g != 0)
            continue;
        x2 = get(a1,b1,c1,i*ga,i*gb,i*gc,a3,b3,c3);
        if (x2/g < 0 || x2%g != 0)
            continue;
        x3 = get(a1,b1,c1,a2,b2,c2,i*ga,i*gb,i*gc);
        if (x3/g < 0 || x3%g != 0)
            continue;
        x1 /= g;
        x2 /= g;
        x3 /= g;
        fout << x1 << ' ' << x2 << ' ' << x3 << ' ' << i << endl;
        return 0;
    }
    if (i > 100)
        fout << "NONE" << endl;
    fout.close();
}
