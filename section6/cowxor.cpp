/*
ID: kevinli7
PROG: cowxor
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <map>
using namespace std;
const int NMAX = 100001;
const int MAX = 4194306;
const int M = 2097153;
map<int,int> idx;
// I don't know why usaco was so stricted on memory...
//int num[M];
bool reg[MAX];
int d[NMAX];
int ans,start=1,en=1,bias;
int N,high;
inline int l(int i) {return 2*i+1;}
inline int r(int i) {return 2*i+2;}
int main()
{
    ifstream fin("cowxor.in");
    fin >> N;
    int n;
    int M;
    for (int i = 1; i <= N; ++i)
    {
        fin >> n;
        d[i] = d[i-1]^n;
        if (n > M)
            M = n;
    }
    fin.close();
    for (int i = 20; i >= 0; --i)
    {
        if (M & (1<<i))
        {
            high = i;
            break;
        }
    }
    reg[0] = 1;
    int cur = 0;    
    bias = (1<<(high+1))-1;
    // go l is zero, one otherwise.
    for (int i = 0; i <= high; ++i)
    {
        cur = l(cur);
        reg[cur] = true;
    }
    //num[cur] = 0;
    idx[cur] = 0;
    int mask = 0, res = 0;
    for (int e = 1; e <= N; ++e)
    {
        res = 0;
        cur = 0;
        for (int s = high; s >= 0; --s)
        {
            mask = 1<<s;
            if (d[e] & mask)
                if (reg[l(cur)])
                    cur = l(cur);
                else
                    cur = r(cur);
            else 
                if (reg[r(cur)])
                    cur = r(cur);
                else
                    cur = l(cur);
        }
       // res = d[e]^d[num[cur-bias]];
        res = d[e]^d[idx[cur]];
        if (res > ans)
        {
            ans = res;
            //start = num[cur-bias] + 1;
            start = idx[cur] + 1;
            en = e;
        }
        cur = 0;
        for (int s = high; s >= 0; --s)
        {
            mask = 1<<s;
            cur = (d[e]&mask)?r(cur):l(cur);
            reg[cur] = 1;
        }
        //num[cur-bias] = e;
        idx[cur] = e;
    }
    ofstream fout("cowxor.out");
    fout << ans << ' ' << start << ' ' << en << endl;
    fout.close();

}
