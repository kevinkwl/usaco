/*
ID: kevinli7
PROG: preface
LANG: C++11
*/

#include <iostream>
#include <fstream>
#include <unordered_map>
using namespace std;
#define N_MAX 3501
#define units 7

int N;
string su = "IVXLCDM";
int nu[] = {1,5,10,50,100,500,1000};
unordered_map<char, int> freq;
string rome[N_MAX];
void init()
{
    rome[0] = "";
    rome[1] = "I";
    rome[2] = "II";
    rome[3] = "III";
    rome[4] = "IV";
}
void gen(int num)
{
    int i;
    for (i = units - 1; i >= 1; --i)
        if (num >= nu[i])
            break;
    if (i == units - 1)
        rome[num] = su[i] + rome[num - nu[i]];
    else if (i&1 && num >= nu[i+1] - nu[i-1])
        rome[num] = string(1,su[i-1]) + string(1, su[i+1])
            + rome[num - nu[i+1] + nu[i-1]];
    else if (i%2 == 0 && num >= nu[i+1] - nu[i])
        rome[num] = string(1,su[i]) + string(1,su[i+1])
            + rome[num - nu[i+1] + nu[i]];
    else
        rome[num] = string(1,su[i]) + rome[num - nu[i]];
}
int main()
{
    ifstream fin("preface.in");
    fin >> N;
    fin.close();

    init();
    string total = "";
    for (int i = 1; i <= N; ++i)
    {
        if (i >= 5)
            gen(i);
        total += rome[i];
        //cout << rome[i] << endl;
    }

    for (auto & c : total)
    {
        if (freq.count(c) == 0)
            freq[c] = 1;
        else
            ++freq[c];
    }

    ofstream fout("preface.out");

    for (auto & c : su)
    {
        if (freq[c] != 0)
            fout << c << ' ' << freq[c] << endl;
    }
    fout.close();
}
