/*
ID: kevinli7
PROG: sprime
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
int N;
vector<vector<int>> super(9);

bool isPrime(int d)
{
    if (d == 1)
        return false;
    if (d == 2)
        return true;
    if (d%2 == 0)
        return false;
    for (int i = 3; i*i <= d; i+=2)
        if (d%i == 0)
            return false;
    return true;
}
void gen(int d)
{
    int number;
    for (int j = 0; j < super[d-1].size(); ++j)
        for (int i = 1; i <= 9; i+=2)
        {
            number = super[d-1][j]*10 + i;
            if (isPrime(number))
                super[d].push_back(number);
        }
}
int main()
{
    ifstream fin("sprime.in");
    fin >> N;
    fin.close();
    ofstream fout("sprime.out");
    super[1].push_back(2);
    super[1].push_back(3);
    super[1].push_back(5);
    super[1].push_back(7);
    for (int i = 2; i <= N; ++i)
        gen(i);

    for (int i = 0; i < super[N].size(); ++i)
        fout << super[N][i] << endl;
    fout.close();

}
