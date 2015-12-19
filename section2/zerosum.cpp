/*
ID: kevinli7
PROG: zerosum
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
const int N_MAX = 9;
int digit[N_MAX+1];
vector<char> op(N_MAX+1);
vector<vector<char>> valid;
int cur;
int N;

void dfs(int step, int res,int preres, int pre, char preop)
{
    if (step > N + 1)
        return;
    if (step == N + 1 && res == 0)
    {
        valid.push_back(op);
        return;
    }
    else if (step < N + 1)
    {
        cur = pre*10 + step;
        switch(preop)
        {
            case '+' :op[step] = ' ';dfs(step + 1, preres + cur, preres, cur, '+');break;
            case '-' :op[step] = ' ';dfs(step + 1, preres - cur, preres, cur, '-');break;
        }
        op[step] = '+';
        dfs(step + 1, res + step, res, step, '+');
        op[step] = '-';
        dfs(step + 1, res - step, res, step, '-');
    }

}

int main()
{
    ifstream fin("zerosum.in");
    fin >> N;
    fin.close();

    dfs(2, 1, 0, 1, '+');
    ofstream fout("zerosum.out");
    if (valid.size())
        for (auto & ops : valid)
        {
            fout << 1;
            for (int i = 2; i <= N; ++i)
                fout << ops[i] << i;
            fout << endl;
        }
    fout.close();
}
