/*
ID: kevinli7
PROG: frac1
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;
int N;
struct frac
{
    int num;
    int deno;

    frac(int a, int b):num(a), deno(b){}
};
vector<frac> ans;

int gcd(int a, int b)
{
    return (b==0? a: gcd(b,a%b));
}


int main()
{
    ifstream fin("frac1.in");
    fin >> N;
    fin.close();

    ans.push_back(frac(0,1));
    ans.push_back(frac(1,1));
    for (int i = 2; i <= N; ++i)
        for (int j = 1; j < i; ++j)
        {
            if (gcd(j,i) != 1)
                continue;
            else
            {
                ans.push_back(frac(j,i));
            }
        }
    sort(ans.begin(), ans.end(), [](frac & a, frac & b){
            return a.num * b.deno < a.deno * b.num;
            });

    ofstream fout("frac1.out");
    for (auto & f : ans)
        fout << f.num << '/' << f.deno<< endl;
    fout.close();
    
    
}
