/*
ID: kevinli7
PROG: picture
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
const int NMAX = 5001;
struct Line
{
    int s,t,pos;
    bool start;
    Line(int ss=0,int tt=0,int pp=0,bool st=0):s(ss),t(tt),pos(pp),start(st){}
    Line& operator=(const Line& l)
    {
        s = l.s;t=l.t;pos=l.pos;start=l.start;
        return *this;
    }
};
int N;
Line Lx[2*NMAX+100],Ly[2*NMAX+100];
int level[20005],bmin=-10000,bmax=10000;
long long ans;
void scan(Line * line)
{
    for (int i = 0; i <= 2*bmax; ++i)
        level[i] = 0;
    for (int i = 0; i < 2*N; ++i)
    {
        for (int s = line[i].s; s < line[i].t; ++s)       
        {
            if (line[i].start)
            {
                ++level[s+bmax];
                if (level[s+bmax] == 1)
                    ++ans;
            }
            else
            {
                --level[s+bmax];
                if (level[s+bmax] == 0)
                    ++ans;
            }
        }
    }
}
auto ff = [](const Line& l,const Line& r)
            {
                if (l.pos != r.pos)
                    return l.pos < r.pos;
                else if (l.start && !r.start)
                    return true;
                else
                    return false;
            };
int main()
{
    ifstream fin("picture.in");
    fin >> N;
    int x1,x2,y1,y2,p1,p2;
    for (int i = 0; i < N; ++i)
    {
        fin >> x1 >> y1 >> x2 >> y2;
        
        Lx[2*i] = Line(x1,x2,y1,true);
        Lx[2*i+1] = Line(x1,x2,y2,false);
        Ly[2*i] = Line(y1,y2,x1,true);
        Ly[2*i+1] = Line(y1,y2,x2,false); 
    }
    fin.close();

    sort(Lx,&Lx[2*N],ff);
    sort(Ly,&Ly[2*N],ff);
    scan(Lx);
    scan(Ly);
    ofstream fout("picture.out");
    fout << ans << endl;
    fout.close();

}
