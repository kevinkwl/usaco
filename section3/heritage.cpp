/*
ID: kevinli7
PROG: heritage
LANG: C++11
*/
#include <iostream>
#include <fstream>
using namespace std;
string in,pre;

string post(const string ino, const string pre)
{
    if (ino.size() == 0 || pre.size() == 0)
        return "";
    char end = pre[0];
    int idx = ino.find(end);
    string lhs = post(ino.substr(0,idx),pre.substr(1,idx));
    string rhs = post(ino.substr(idx+1,ino.size()-1-idx)
                        , pre.substr(idx+1,pre.size()-1-idx));
    return lhs + rhs + end;
}

int main()
{
    ifstream fin("heritage.in");
    fin >> in >> pre;
    fin.close();
    
    ofstream fout("heritage.out");
    fout << post(in, pre) << endl;
    fout.close();
}
