/*
ID: kevinli7
PROG: spin
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
const int WMAX = 6;
struct Wheel
{
    int speed;
    int numofWg;
    int wg_begin[WMAX];
    int wg_len[WMAX];
    bool wg[360];
    void update_wg()
    {
        fill_n(wg, 360, false);     
        for (int i = 1; i <= numofWg; ++i)
        {
            for (int j = wg_begin[i]; j <= wg_begin[i]+wg_len[i]; ++j)
            {
                wg[j%360] = true;
            }
        }
    }
    void update()
    {
        for (int i = 1; i <= numofWg; ++i)
        {
            wg_begin[i] = (wg_begin[i] + speed)%360;
        }
        update_wg();
    }
};
struct Sys
{
    Wheel wheel[5];
    int   bound;
    void init(ifstream & fin)
    {
        for (int i = 0; i < 5; ++i)
        {
            fin >> wheel[i].speed >> wheel[i].numofWg;
            for (int j = 1; j <= wheel[i].numofWg; ++j)
                fin >> wheel[i].wg_begin[j] >> wheel[i].wg_len[j];
            wheel[i].update_wg();
        }
    }
    bool check()
    {
        for (int i = 0; i < 360; ++i)
            if (wheel[1].wg[i] && wheel[2].wg[i] && wheel[3].wg[i]
                    && wheel[4].wg[i] && wheel[0].wg[i])
                return true;
        return false;
    }
    void update_all()
    {
        for (int i = 0; i < 5; ++i)
            wheel[i].update();
    }
    int run()
    {
        for (int i = 0; i < 360; ++i)
        {
            if (check())
                return i;
            update_all();
        }
        return -1;
    }
};


int main()
{
    ifstream fin("spin.in");
    Sys sol;
    sol.init(fin);
    int res = sol.run();
    ofstream fout("spin.out");
    if (res == -1)
        fout << "none" << endl;
    else
        fout << res << endl;
    fout.close();
    
}
