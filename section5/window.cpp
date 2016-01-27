/*
ID: kevinli7
PROG: window
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>
#include <iomanip>
using namespace std;
const int WMAX = 62;
ifstream fin("window.in");
ofstream fout("window.out");
struct Rect
{
    int x1,y1,x2,y2;
    int size() const {return (x2-x1)*(y2-y1);}
    Rect():x1(0),x2(0),y1(0),y2(0){}
    Rect(int a,int b,int c,int d):x1(a),y1(b),x2(c),y2(d){}
    Rect(const Rect& r): x1(r.x1),y1(r.y1),x2(r.x2),y2(r.y2){}
    Rect(Rect&& r): x1(r.x1),y1(r.y1),x2(r.x2),y2(r.y2){}
    Rect& operator=(const Rect& r)
    {x1 = r.x1,x2 = r.x2,y1=r.y1,y2=r.y2;return *this;}
};
int top,bottom;
struct Win
{
    int lv;
    bool reg;
    Rect rect;
    double vis;
    Win(): reg(false),vis(0),rect(Rect()) {}
    void regis(int x1,int y1,int x2,int y2) 
    {
        lv = ++top;
        reg = true;
        rect = Rect(x1,y1,x2,y2);
        vis = 100;
    }
} win[62];
int id(char ch) 
{
    if (ch < 'A')       return ch-'0';
    else if (ch <'a')   return ch-'A' + 10;
    else                return ch-'a' + 36;
}
void create(char ch,int x1,int y1,int x2,int y2)
{
    if (win[id(ch)].reg)
        return;
    win[id(ch)].regis(x1,y1,x2,y2);
}
void toTop(char ch)
{
    win[id(ch)].lv = ++top;
}
void toBot(char ch)
{
    win[id(ch)].lv = --bottom;
}
void destroy(char ch)
{
    win[id(ch)].reg = false;
}
void see(char ch)
{
    queue<Rect> Q;
    queue<int> toCover;
    int lv = win[id(ch)].lv;
    queue<Rect> tmp;
    tmp.push(win[id(ch)].rect);
    for (int i = 0; i < WMAX; ++i)
        if (win[i].reg && win[i].lv > lv)
            toCover.push(i);
    while (!toCover.empty())
    {
        int cov = toCover.front();
        toCover.pop();
        swap(Q, tmp);
        while (!Q.empty())
        {
            Rect rec = Q.front();
            Rect next = rec;
            Q.pop();
            if (win[cov].rect.x1 > rec.x1)
            {
                next.x2 = min(win[cov].rect.x1, rec.x2);
                rec.x1 = next.x2;
                tmp.push(next);
            }
            if (rec.x2 > rec.x1 && win[cov].rect.x2 < rec.x2)
            {
                next.x2 = rec.x2;
                next.x1 = max(win[cov].rect.x2,rec.x1);
                rec.x2 = next.x1;
                tmp.push(next);
            }
            next = rec;
            if (rec.x2 > rec.x1 && win[cov].rect.y1 > rec.y1)
            {
                next.y2 = min(win[cov].rect.y1,rec.y2);
                rec.y1 = next.y2;
                tmp.push(next);
            }
            if (rec.x2 > rec.x1 && rec.y2 > rec.y1 &&
                    win[cov].rect.y2 < rec.y2)
            {
                next.y2 = rec.y2;
                next.y1 = max(win[cov].rect.y2, rec.y1);
                rec.y2 = next.y1;
                tmp.push(next);
            }
        }
    }
    double visible = 0;
    double total = win[id(ch)].rect.size();
    while (!tmp.empty())
    {
        Rect rec = tmp.front();
        tmp.pop();
        visible += rec.size();
    }
    fout << fixed << setprecision(3) << visible/total*100 << endl;
}
int main()
{
    char m,ch;
    int x1,y1,x2,y2;
    while (fin >> m)
    {
        switch (m)
        {
            case 'w': fin >> m >> ch >> m;
                      fin >> x1 >> m >> y1 >> m >> x2 >> m >> y2 >> m;
                      if (x1 > x2) swap(x1,x2);
                      if (y1 > y2) swap(y1,y2);
                      create(ch,x1,y1,x2,y2);
                      break;
            case 't': fin >> m >> ch >> m;
                      toTop(ch);
                      break;
            case 'b': fin >> m >> ch >> m;
                      toBot(ch);
                      break;
            case 'd': fin >> m >> ch >> m;
                      destroy(ch);
                      break;
            case 's': fin >> m >> ch >> m;
                      see(ch);
                      break;
        }
    }

    fin.close();
    fout.close(); 
}
