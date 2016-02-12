/*
ID: kevinli7
PROG: fence3
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
const int FMAX = 150;
const int STEP = 100;
int Lx0[FMAX],Ly0[FMAX],Lx1[FMAX],Ly1[FMAX];
int F;
int bx,by;
double best = 0x7fffffff;
int fbx,fby;

double dist(int x, int y, int k)
{
    if (Lx0[k] == Lx1[k])   // vertical line
    {
        if (y > Ly1[k])
            return sqrt((y-Ly1[k])*(y-Ly1[k])+(x-Lx1[k])*(x-Lx1[k]));
        else if (y < Ly0[k])
            return sqrt((y-Ly0[k])*(y-Ly0[k])+(x-Lx0[k])*(x-Lx0[k]));
        else
            return abs(x - Lx0[k]);
    }
    else if (Ly0[k] == Ly1[k])   // horizontal line
    {
        if (x > Lx1[k])
            return sqrt((y-Ly1[k])*(y-Ly1[k])+(x-Lx1[k])*(x-Lx1[k]));
        else if (x < Lx0[k])
            return sqrt((y-Ly0[k])*(y-Ly0[k])+(x-Lx0[k])*(x-Lx0[k]));
        else
            return abs(y - Ly0[k]);
    }
}

int main()
{
    ifstream fin("fence3.in");
    fin >> F;
    int x0,y0,x1,y1;
    for (int i = 0; i < F; ++i)
    {
        fin >> x0 >> y0 >> x1 >> y1;
        if (x1 <= x0 && y1 <= y0)
        {
            swap(x1,x0);
            swap(y1,y0);
        }
        Lx0[i] = x0*10;
        Ly0[i] = y0*10;
        Lx1[i] = x1*10;
        Ly1[i] = y1*10;
    }
    fin.close();
    int x,y,k;
    double d;
    for (x = 0; x <= 1000; x += STEP)
        for (y = 0; y <= 1000; y += STEP)
        {
            d = 0;
            for (k = 0; k < F; ++k)
                d += dist(x,y,k);
            if (d < best)
            {
                bx = x;
                by = y;
                best = d;
            }
        }
    for (x = max(0, bx-STEP); x <= bx+STEP; ++x)
        for (y = max(0, by-STEP); y <= by+STEP; ++y)
        {
            d = 0;
            for (k = 0; k < F; ++k)
                d += dist(x,y,k);
            if (d < best)
            {
                fbx = x;
                fby = y;
                best = d;
            }
        }

    ofstream fout("fence3.out");
    int be = best+0.5;
    fout << fbx/10 << '.' << fbx%10 << ' ' << fby/10 << '.' << fby%10 << ' ' << be/10 << '.' << be%10 << endl;
    fout.close();
}
