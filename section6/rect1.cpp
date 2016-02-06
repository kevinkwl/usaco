/*
ID: kevinli7
PROG: rect1
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <queue>
using namespace std;
int A,B,N;
int color[2501];
struct Rect
{
    int llx,lly,urx,ury;
    int color;
    Rect(int lx=0,int ly=0,int ux=0,int uy=0,int c=1)
    :llx(lx),lly(ly),urx(ux),ury(uy),color(c)
    {}
    int size() const
    {
        if (ury <= lly || urx <= llx)
            return -1;
        return (ury-lly)*(urx-llx);
    }
    void print()
    {
        cout << llx << ' ' << lly << ' ' << urx << ' ' << ury << ' ' << color << endl;
    }
};
int main()
{
    ifstream fin("rect1.in");
    int lx,ly,ux,uy,c;
    fin >> A >> B >> N;
    queue<Rect> Q;
    queue<Rect> Next;
    for (int i = 0; i < N; ++i)
    {
        fin >> lx >> ly >> ux >> uy >> c;

        while (!Q.empty())
        {
            Rect cur = Q.front();
            Q.pop();
            if (!(cur.ury <= ly || uy <= cur.lly ||
                  cur.urx <= lx || ux <= cur.llx))
            {
                Rect a(cur.llx, cur.lly, lx, cur.ury, cur.color);
                Rect b(ux, cur.lly, cur.urx, cur.ury, cur.color);
                Rect c(max(cur.llx,lx), cur.lly, min(cur.urx,ux), ly,cur.color);
                Rect d(max(cur.llx,lx), uy, min(cur.urx,ux), cur.ury,cur.color);
                if (a.size() > 0) Next.push(a);
                if (b.size() > 0) Next.push(b);
                if (c.size() > 0) Next.push(c);
                if (d.size() > 0) Next.push(d);
            }
            else
            {
                Next.push(cur);
            }

        }
        if (c != 1)
            Next.push(Rect(lx,ly,ux,uy,c));
        Q = Next;

        while (!Next.empty())
        {
            Rect cur = Next.front();
            Next.pop(); 

        }
    }
    int total = 0;

    while (!Q.empty())
    {
        Rect r = Q.front();
        Q.pop();
        color[r.color] += r.size();
        total += r.size();
    }
    
    color[1] += A*B - total;
    ofstream fout("rect1.out");


    for (int i = 1; i <= 2500; ++i)
        if (color[i] != 0)
            fout << i << ' ' << color[i] << endl;
    fin.close();
    fout.close();
    
}
