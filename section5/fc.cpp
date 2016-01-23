/*
ID: kevinli7
PROG: fc
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <algorithm>
using namespace std;
const int NMAX = 10000;
struct Point
{
    double x,y;
    double ang;
} pnt[NMAX];
int N;
int hull[NMAX], hullpos;
double ans = 0,x = 0,y = 0;
double dist(int i, int j)
{
    return sqrt((pnt[i].x-pnt[j].x)*(pnt[i].x-pnt[j].x) + 
                (pnt[i].y-pnt[j].y)*(pnt[i].y-pnt[j].y));
}
double cross(int i, int j, int k)
{
    double x1,y1,x2,y2;
    x1 = pnt[i].x - pnt[j].x;
    y1 = pnt[i].y - pnt[j].y;
    x2 = pnt[k].x - pnt[j].x;
    y2 = pnt[k].y - pnt[j].y;
    return x1*y2-x2*y1;
}
void print(int i)
{
    cout << pnt[i].x << ' ' << pnt[i].y << endl;
}
int main()
{
    ifstream fin("fc.in");
    fin >> N;
    for (int i = 0; i < N; ++i)
    {
        fin >> pnt[i].x >> pnt[i].y;
        x += pnt[i].x/N;
        y += pnt[i].y/N;
    }
    //cout << x << ' ' << y << endl;
    for (int i = 0; i < N; ++i)
    {
        pnt[i].ang = atan2(pnt[i].y-y,pnt[i].x-x);
    }

    fin.close();
    sort(pnt, &pnt[N],[](const Point& a, const Point& b)
            {
                return a.ang < b.ang;
            });

    hull[0] = 0;
    hull[1] = 1;
    hullpos = 2;
    int p;
    for (p = 2; p < N - 1; ++p)
    {
        while (hullpos > 1 && cross(hull[hullpos-2],hull[hullpos-1],
                                    p) >= 0)
            --hullpos;
        hull[hullpos] = p;
        ++hullpos;
    }
    p = N - 1;
    while (hullpos > 1 && cross(hull[hullpos-2],hull[hullpos-1],
                                p) >= 0)
        --hullpos;
    int hullstart = 0;
    bool flag;
    do
    {

        flag = false;
        if (hullpos - hullstart >= 2 && 
            cross(hull[hullpos-1], p, hull[hullstart]) >= 0)
        {
            p = hull[--hullpos];
            flag = true;
        }
        if (hullpos - hullstart >= 2 &&
            cross(p,hull[hullstart],hull[hullstart+1]) >= 0)
        {
            ++hullstart;
            flag = true;
        } 
    } while (flag);
    hull[hullpos] = p;
    ans += dist(hull[hullstart], hull[hullpos]);
    while (hullstart < hullpos)
    {
        ans += dist(hull[hullstart],hull[hullstart+1]);
        ++hullstart;
    }
    ofstream fout("fc.out");
    fout << fixed << setprecision(2) << ans << endl;
    fout.close();
}
