/*
ID: kevinli7
PROG: cowcycle
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
int f[6],r[11];
int bestf[6],bestr[11];
int F,R,F1,F2,R1,R2;
double minVar = 0x7fffffff;
void show()
{
    for (int i = 1; i <= F; ++i)
        cout << f[i] << ' ';
    cout << endl;
    for (int i = 1; i <= R; ++i)
        cout << r[i] << ' ';
    cout <<endl << "XXXXXXXXXXXXXXXXXXXX" << endl;
}
void cal()
{
    double curVar = 0;
    double diff[100] = {0.0};
    double mean = 0;
    double sum = 0, sumS = 0;
    double ratio[100] = {0};
    int num_ratio = 0;
    int l;
    double rr = 0;
    for (int i = 1; i <= F; ++i)
        for (int j = 1; j <= R; ++j)
        {
            rr = f[i]*1.0/r[j];
            l = ++num_ratio;
            while (ratio[l-1] > rr)
            {
                ratio[l] = ratio[l-1];
                --l;
            }
            ratio[l] = rr;
        }
    for (int i = 1; i < num_ratio; ++i)
    {
        diff[i] = ratio[i+1] - ratio[i];
        sum += diff[i];
        sumS += diff[i]*diff[i];
    }
    curVar = sumS - sum*sum/(num_ratio-1);
    if (curVar < minVar)
    {
        minVar = curVar;
        memcpy(bestf+1, f+1, sizeof(int)*F);
        memcpy(bestr+1, r+1, sizeof(int)*R);
    }
    
}
bool valid()
{
    return f[F]*r[R] >= 3*f[1]*r[1];
}
void dfsR(int d,int l)
{
    if (d == R)
    {
        if (valid())
            cal();
        return;
    }
    for (int i = l; i+R-d-1 <= R2; ++i)
    {
        r[d+1] = i;
        dfsR(d+1, i+1);
    }

}
void dfsF(int d,int l)
{
    if (d == F)
    {
        dfsR(0,R1);
        return;
    }
    for (int i = l; i+F-d-1 <= F2; ++i)
    {
        f[d+1] = i;
        dfsF(d+1, i+1);
    }
}
int main()
{
    ifstream fin("cowcycle.in");
    fin >> F >> R >> F1 >> F2 >> R1 >> R2;
    fin.close();
    dfsF(0,F1);
    ofstream fout("cowcycle.out");
    for (int i = 1; i <= F; ++i)
        if (i != F)
            fout << bestf[i] << ' ';
        else
            fout << bestf[i] << endl;
    for (int i = 1; i <= R; ++i)
        if (i != R)
            fout << bestr[i] << ' ';
        else
            fout << bestr[i] << endl;
    fout.close();
}
