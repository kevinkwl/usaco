/*
ID: kevinli7
PROG: buylow
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
using namespace std;
const int NMAX = 5000;
const int MAXS = 8;
const int MOD = 1000000000;
long p[NMAX+1],dp[NMAX+1];
int ago[NMAX];
int N,len;
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

Bignum cnt[NMAX+1];
int main()
{
    ifstream fin("buylow.in");
    fin >> N;
    for (int i = 0; i < N; ++i)
        fin >> p[i];
    fin.close();
    for (int i = 0; i <= N; ++i)
        for (int j = i+1; j <= N; ++j)
            if (p[i] == p[j])
            {
                ago[i] = j;
                break;
            }
    p[N] = 0,dp[0] = 1, cnt[0].num[1] = 1;
    for (int i = 1; i <= N; ++i)
    {
        dp[i] = 1;
        cnt[i].num[1] = 1;
        for (int j = 0; j < i; ++j)    
        {
            if (ago[j] && ago[j] < i)
                continue;
            if (p[j] > p[i])
            {
                if (dp[j] + 1 > dp[i])
                {
                    dp[i] = dp[j] + 1;
                    cnt[i] = cnt[j];
                }
                else if (dp[j] + 1 == dp[i])
                    cnt[i].plus(cnt[j]);
            }
        }
    }

    ofstream fout("buylow.out");
    fout << dp[N] - 1 << ' ' << cnt[N] << endl;
    fout.close();
}
