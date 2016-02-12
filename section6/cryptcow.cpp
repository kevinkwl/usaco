/*
ID: kevinli7
PROG: cryptcow
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
using namespace std;
string ori = "Begin the Escape execution at the Break of Dawn";
string crypted;
int can,times;
bool used[99992];
int elfhash(string & s)
{
    unsigned long h = 0,x=0;
    for (auto c : s)
    {
        h = (h<<4)+(c++);
        if ((x=h & 0xf0000000L) != 0)
        {
            h ^= (x>>24);
            h &=~x;
        }
    }
    return h%99991;
}


bool decrypt(string cur, int step, int depth)
{
    if (step == depth)
    {
        if (cur == ori)
            return true;
        else
            return false;
    }
    if (cur.size() <= ori.size())
        return false;

    int pc[80],po[80],pw[80];
    int nc=0,no=0,nw=0;
    for (int i = 0; i < cur.size(); ++i)
        switch (cur[i])
        {
            case 'C': pc[nc++] = i;break;
            case 'O': po[no++] = i;break;
            case 'W': pw[nw++] = i;break;
        }
    if (nc == 0 || no == 0 || nw == 0)
        return false;
    if (cur.substr(0, pc[0]) != ori.substr(0,pc[0]))
        return false;
    int n = cur.size()-pw[nw-1]-1;
    if (cur.substr(pw[nw-1]+1,n)
            != ori.substr(ori.size()-n,n))
            return false;
    if (nc > 1)
    {
        int cnt = 0;
        int pre = pc[0];
        for (int i = pc[0]+1; i < cur.size(); ++i)
        {
            if (cur[i] == 'C' || cur[i] == 'O' || cur[i] == 'W')
                ++cnt;
            if (cnt == 1)
            {
                string test = cur.substr(pre+1,i-pre-1);
                if (test.size() > 0)
                    if (ori.find(test) == string::npos)
                        return false;
                cnt = 0;
                pre = i;
            }
        }
    }
    if (used[elfhash(cur)])
        return false;
    used[elfhash(cur)] = 1;
    string next;
    for (int c = 0; c < nc; ++c)
        for (int o = 0; o < no; ++o)
        {
            if (pc[c] >= po[o])
                continue;
            for (int w = 0; w < nw; ++w)
            {
                if (po[o] >= pw[w])
                    continue;
                next = cur.substr(0, pc[c]);
                next += cur.substr(po[o]+1, pw[w]-po[o]-1);
                next += cur.substr(pc[c]+1, po[o]-pc[c]-1);
                next += cur.substr(pw[w]+1, cur.size()-pw[w]-1);
                if (decrypt(next, step+1, depth))
                    return true;
            }
        }
    return false;
}

int main()
{
    ifstream fin("cryptcow.in");
    getline(fin, crypted);
    fin.close();
    int diff = crypted.size() - ori.size();
    int d = 0;
    if (diff%3 == 0)
    {
        d = diff/3;
        if (decrypt(crypted, 0, d))
        {
            can = 1;
            times = d;
        }
    }

    ofstream fout("cryptcow.out");
    fout << can << ' ' << times << endl;
    fout.close();
}
