/*
ID: kevinli7
PROG: hamming
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <bitset>
#include <vector>
using namespace std;
vector<bitset<8>> num(256);
int N,B,D;
vector<bitset<8>> ans;

void solve()
{
    bitset<8> test;
    for (int i = 0; i < B; ++i)
    {
        //cout << num[i] << endl;
        vector<bitset<8>> cur = {num[i]};
        for (int j = i+1; i < B; ++j)
        {
            //cout << num[j] << endl;
            bool flag = true;
            if (cur.size() == N)
            {
                ans = cur;
                return;
            }
            for (auto & code : cur)
            {
                test = code^num[j];
                if (test.count() < D)
                    flag = false; 
            }
            if (flag)
                cur.push_back(num[j]);
        }

        //cout << endl;
    }
}
int main()
{
    ifstream fin("hamming.in");
    fin >> N >> B >> D;
    fin.close();
    
    for (int i = 0; i < 256; ++i)
    {
        num[i] = bitset<8>(i);
    }
    
    B = 1<<B;
    solve();
    
    ofstream fout("hamming.out");
    for (int i = 0; i < ans.size(); ++i)
    {
        if (i%10 == 0 && i != 0)
            fout << endl;
        else if (i != 0)
            fout << ' ';
        fout << ans[i].to_ulong();
    }
    fout << endl;

    fout.close();

}
