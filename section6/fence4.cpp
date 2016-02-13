/*
ID: kevinli7
PROG: fence4
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;
const int NMAX = 201;
struct Point
{
    int x,y;
};
struct Line
{
    Point p1,p2;
    double ang;
    void cal()
    {
        ang = atan2(p2.y-p1.y,p2.x-p1.x);
    }
} line[NMAX];
Point obs;
int N;
int visible[NMAX];
int cnt;
double cross(Point p, Point u, Point v)  // pu x pv
{
    return (1.0*u.x - p.x) * (v.y - p.y) - (u.y - p.y) * (v.x - p.x);   
}
double side(Point p, Line l)
{
    return cross(p, l.p1, l.p2);
}
bool sameSide(Point P, Point Q, Line L)
{
    double s1 = side(P, L);
    double s2 = side(Q, L);
    return s1 * s2 > 0 || (s1 == 0 && s2 == 0);
}
bool intersect(Line l1, Line l2)
{
    return !sameSide(l1.p1,l1.p2,l2) && !sameSide(l2.p1,l2.p2,l1);
}
bool Valid()
{
    for (int i = 3; i <= N-1; ++i)
        for (int j = 1; j < i-1; ++j)
            if (intersect(line[i],line[j]))
            {
                return false;
            }
    for (int j = 2; j < N-1; ++j)
        if (intersect(line[N],line[j]))
            return false;
    return true;
}
void Next(int &x, int &y, Line &L)
{
    x += 2 * cos(L.ang) + 0.5;
    y += 2 * sin(L.ang) + 0.5;
}
bool check(Point &p, Point& end, int comp)
{
    switch (comp)
    {
        case 0: return p.y <= end.y;
        case 1: return p.x <= end.x;
        case 2: return p.x >= end.x;
        case 3: return p.y >= end.y;
    }
}
void see()
{
    int curLine, v=0,end;
    bool flag;
    int comp;
    Point curPoint;
    Line testLine;
    testLine.p1.x = obs.x;
    testLine.p1.y = obs.y;
    for (int i = 1; i <= N; ++i)
    {
        if (line[i].p1.y < line[i].p2.y)     // <= p2.y
            comp = 0;
        else if (line[i].p1.y == line[i].p2.y)
            if (line[i].p1.x < line[i].p2.x)  // <= p2.x
                comp = 1;
            else   // >= p2.x
                comp = 2;
        else    // >= p2.y
            comp = 3;
        curPoint.x = line[i].p1.x;
        curPoint.y = line[i].p1.y;


        while (check(curPoint, line[i].p2, comp))
        {
            if (i == 100000)
            {
                cout << curPoint.x/100 << ' ' << curPoint.y/100 << endl;
            }
            flag = false;
            testLine.p2.x = curPoint.x;
            testLine.p2.y = curPoint.y;
            for (int j = 1; j <= N; ++j)
                if (j != i && intersect(testLine,line[j]))
                {
                    flag = true;
                    break;
                }
            if (!flag)
            {
                ++v;
            }
            if (v >= 1)
            {
                visible[cnt++] = i;
                v = 0;
                break;
            }
            Next(curPoint.x,curPoint.y,line[i]);
        }

    }
}
void checkBack()
{
    int i = visible[cnt-1],j = visible[cnt-2];
    if (i == N && j == N-1)
        swap(visible[cnt-1],visible[cnt-2]);
}
int main()
{
    ifstream fin("fence4.in");
    fin >> N;
    fin >> obs.x >> obs.y;
    int x,y;
    obs.x *= 200;
    obs.y *= 200;
    for (int i = 1; i <= N; ++i)
    {
        fin >> x >> y;
        x *= 200;
        y *= 200;
        if (i == 1)
        {
            line[N].p1.x = x;
            line[N].p1.y = y;
        }
        line[i-1].p2.x = x;
        line[i-1].p2.y = y;
        line[i-1].cal();
        if (i != N)
        {
            line[i].p1.x = x;
            line[i].p1.y = y;
        }
    }
    fin.close();
    line[N].p2.x = x;
    line[N].p2.y = y;
    line[N].cal();
    ofstream fout("fence4.out");
    if (Valid())
    {
        see();
        fout << cnt << endl;
        checkBack();
        for (int i = 0; i < cnt; ++i)
            fout << line[visible[i]].p1.x/200 << ' ' << line[visible[i]].p1.y/200
                << ' ' << line[visible[i]].p2.x/200 << ' ' << line[visible[i]].p2.y/200 << endl;
    }
    else
        fout << "NOFENCE" << endl;
    fout.close();

}
