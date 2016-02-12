/*
ID: kevinli7
PROG: vans
LANG: C++11
*/
#include <iostream>
#include <fstream>
using namespace std;
const int NMAX = 1000;
const int MOD = 1000000000;
const int MAXS = 100;
bool vis[4][NMAX];
int N;
struct Bignum
{
    long num[MAXS];
    int size;
    Bignum()
    {
        num[size=1] = 0;
    }
    Bignum & operator=(Bignum &rhs)
    {
        for (int i = 1; i <= rhs.size; ++i)
        {
            this->num[i] = rhs.num[i];
        }
        this->size = rhs.size;
        return *this;
    }
    Bignum & plus(Bignum &rhs)
    {
        long carry = 0;
        long cur = 0;
        for (int i = 1; i <= max(rhs.size, this->size);++i)
        {
            if (i > this->size) this->num[i] = 0;
            if (i > rhs.size) rhs.num[i] = 0;
            cur = this->num[i] + rhs.num[i] + carry;
            carry = cur/MOD;
            this->num[i] = cur%MOD;
        }
        this->size = max(rhs.size, this->size);
        if (carry != 0)
        {
            this->size += 1;
            this->num[size] = carry;
        }
        return *this;
    }
    Bignum & minus(Bignum &rhs) // bad minus just for this case
    {
        long borrow = 0;
        long cur = 0;
        for (int i = 1; i <= this->size;++i)
        {
            if (i > this->size) this->num[i] = 0;
            if (i > rhs.size) rhs.num[i] = 0;
            num[i] -= (rhs.num[i]+borrow);
            if (num[i] < 0)
            {
                num[i] += MOD;
                borrow = 1;
            }
            else
                borrow = 0;
        }
        return *this;
    }
};
ostream& operator<<(ostream & os,const Bignum& n)
{
    int k;
    long raw;
    for (int i = n.size; i > 0; --i)
    {
        if (i < n.size)
        {
            k = 0;
            raw = n.num[i];
            while (raw > 0)
                raw/=10,++k;
            for (int i = 1; i <= 9-k; ++i)
                os << '0';
        }
        os << n.num[i];
    }
    return os;
}

Bignum f[1001];
/*
void dfs(int r, int c, int sofar)
{
    if (vis[r][c] && r == 0 && c == 0 && sofar == 4*N)
    {
        ++ans;
        return;
    }
    else if (vis[r][c])
        return;
    vis[r][c] = 1;
    if (r-1 >= 0)
        dfs(r-1,c,sofar+1);
    if (r+1 < 4)
        dfs(r+1,c,sofar+1);
    if (c-1 >= 0)
        dfs(r,c-1,sofar+1);
    if (c+1 < N)
        dfs(r,c+1,sofar+1);
    vis[r][c] = 0;
}
*/
int main()
{
    ifstream fin("vans.in");
    fin >> N;
    fin.close();
    f[2].num[1] = 2;
    f[3].num[1] = 4;
    f[4].num[1] = 12; 
    for (int i = 5; i <= N; ++i)
    {
        for (int j = 0; j < 2; ++j)
        {
            f[i].plus(f[i-1]);
            f[i].plus(f[i-2]);
        }
        f[i].plus(f[i-4]);
        f[i].minus(f[i-3]);
        f[i].minus(f[i-3]);
    }
    ofstream fout("vans.out");
    fout << f[N] << endl;
    fout.close();
    
}
