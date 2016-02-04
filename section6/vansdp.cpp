/*
ID: kevinli7
PROG: vans
LANG: C++11
*/
#include <iostream>
#include <fstream>
using namespace std;
const int MOD = 100000000;
const int SIZE = 100;
bool trans[8][8] = {
    {0,0,1,0,0,0,0,1},
    {0,0,0,0,1,0,0,0},
    {1,0,0,1,0,1,1,0},
    {0,0,1,0,0,0,0,0},
    {0,1,0,0,0,0,0,0},
    {0,0,1,0,0,0,0,1},
    {1,0,0,0,0,1,1,0},
    {0,0,1,0,0,0,0,1}
};
struct BigInt
{
    int  size;
    long num[SIZE]; // number start from index 1.
    BigInt(int x = 0)
    {
        num[++size] = x;
    }
    void reset()
    {
        size = 0;
    }
    void print(ostream &os)
    {
        long raw = 0;
        int k = 0;
        for (int i = size; i > 0; --i)
        {
            if (i < size)
            {
                raw = num[i];
                k = 0;
                while (raw > 0)
                    raw/=10,++k;
                for (int i = 0; i < k; ++i)
                    os << '0';
            }
            os << num[i];
        }
        os << endl;

    }
    BigInt& operator=(BigInt &rhs)
    {
        for (int i = 1; i <= rhs.size; ++i)
            num[i] = rhs.num[i];
        size = rhs.size;
        return *this;
    }
    BigInt& operator+(BigInt &rhs)
    {
        int i, p = max(size, rhs.size);
        long carry = 0;
        for (i = 1; i <= p; ++i)
        {
            if (i > size) num[i] = 0;
            if (i > rhs.size) rhs.num[i] = 0;
            carry += num[i] + rhs.num[i];
            num[i] = carry%MOD;
            carry /= MOD;
        }
        if (carry > 0)
            num[++p] = carry;
        size = p;
        return *this;
    }
};
BigInt pre[8], cur[8];
int N;

int main()
{
    ifstream fin("vans.in");
    ofstream fout("vans.out");
    fin >> N;
    fin.close();
    BigInt init(1);
    pre[2] = pre[7] = init;
    for (int i = 0; i < N-2; ++i)
    {
        for (int k = 0; k < 8; ++k)
            cur[k].reset();
        for (int f = 0; f < 8; ++f)
            for (int t = 0; t < 8; ++t)
                if (trans[f][t])
                    cur[t] = cur[t] + pre[f];
        for (int k = 0; k < 8; ++k)
            pre[k] = cur[k];
    }
    BigInt ans = pre[2] + pre[2] + pre[6] + pre[6];
    ans.print(fout);
    fout.close();

}
