/*
ID: kevinli7
PROG: runround
LANG: C++11
*/
#include <iostream>
#include <fstream>
using namespace std;
unsigned long M;
unsigned long nextrun;
string num;

bool isrunround(unsigned long n)
{
    bool visited[10] = {0};
    bool appeared[10] = {0};
    num = to_string(n);
    if (!(num.find('0') == string::npos))
        return false;
    int test;
    int len = num.size();
    for (int i = 0; i < len; ++i)
    {
        if (appeared[num[i] - '0'])
            return false;
        appeared[num[i] - '0'] = true;
    }

    int index = 0;
    int start = 0;
    int visit = 0;
    while (!visited[index])    
    {
        ++visit;
        visited[index] = true;
        index = (index + num[index] - '0')%len;
    }
    if (visit == len && index == start)
        return true;
    return false;
}
void find_next()
{
    for (unsigned long i = M + 1; i > 0; ++i)
    {
        if (isrunround(i))
        {
            nextrun = i;
            break;
        }
    }
}
int main()
{
    ifstream fin("runround.in");
    fin >> M;
    fin.close();

    find_next();
    ofstream fout("runround.out");

    fout << nextrun << endl;
    

}
