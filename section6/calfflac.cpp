/*
ID: kevinli7
PROG: calfflac
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <cctype>
using namespace std;
char raw[20010], letter[20010];
int idx[20010];
int size;
int total;
int L[50000];
int main()
{
    ifstream fin("calfflac.in");
    char ch;
    while (fin.get(ch))
        raw[total++] = ch;
    for (int i = 0; i < total; ++i)
        if (isalpha(raw[i]))
        {
            letter[size] = tolower(raw[i]);
            idx[size] = i;
            ++size;
        }
    fin.close();
    int N = size;
    N = 2*N + 1;
    L[0] = 0; // '#'
    L[1] = 1; // '#a#'
    int C = 1, R = 2, i = 0;
    int iMirror,expand=-1,diff=-1;
    int maxLPSLength = 0, maxCPos = 0;
    int start = -1;
    int end = -1;

    for (i = 2; i < N; ++i)
    {
        iMirror = 2*C - i;
        expand = 0;
        diff = R - i;
        if (diff > 0)
        {
            if (L[iMirror] < diff)
                L[i] = L[iMirror];
            else if (L[iMirror] == diff && R == N-1)
                L[i] = L[iMirror];
            else if (L[iMirror] == diff && R < N-1)
            {
                L[i] = L[iMirror];
                expand = 1;
            }
            else if (L[iMirror] > diff)
            {
                L[i] = diff;
                expand = 1;
            }
        }
        else
        {
            L[i] = 0;
            expand = 1;
        }

        if (expand == 1)
        {
            while ((i + L[i] < N-1 && i - L[i] > 0) &&
                    ((i+L[i]+1)%2 == 0 || 
                     letter[(i+L[i])/2] == letter[(i-L[i]-2)/2]))   
                ++L[i];
        }
        if (L[i] > maxLPSLength)
        {
            maxLPSLength = L[i];
            maxCPos = i;
        }
        if (i + L[i] > R)
        {
            C = i;
            R = i + L[i];
        }
    }
    start = (maxCPos - maxLPSLength)/2;
    end = start + maxLPSLength - 1;
    start = idx[start];
    end = idx[end];
    ofstream fout("calfflac.out");
    fout << maxLPSLength << endl;
    for (int i = start; i <= end; ++i)
        fout << raw[i];
    fout << endl;
    fout.close();
}
