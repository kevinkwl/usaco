/*
ID: kevinli7
PROG: sort3
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <algorithm>
using namespace std;
#define N_MAX 1000
int N;
int num[N_MAX], sorted[N_MAX];

int compare_int(const void* a, const void* b)
{
    int a1 = *(int*)a;
    int b1 = *(int*)b;
    return a1 - b1;
}
void print(int * arr)
{
    for (int i = 0; i < N; ++i)
        cout << arr[i] << ' ';
    cout << endl;
}
int main()
{
    ifstream fin("sort3.in");
    fin >> N;
    for (int i = 0; i < N; ++i)
    {
        fin >> num[i];
        sorted[i] = num[i];
    }
    fin.close();

    qsort(sorted, N, sizeof(int), compare_int);
    int cnt = 0;
    for (int i = 0; i < N-1; ++i)
    {
        if (num[i] == sorted[i])
            continue;
        else
        {
            int j = i + 1;
            int k;
            while(j < N && (num[j] != sorted[i] || num[j] == sorted[j])) 
                ++j;
            for (k = j; k < N; ++k)
            {
                if (num[k] == sorted[i] && num[i] == sorted[k])
                    break;
            }
            if (k < N)
                swap(num[i], num[k]);
            else
                swap(num[i], num[j]);
            ++cnt;
        }
    }
    
    ofstream fout("sort3.out");
    fout << cnt << endl;
    fout.close();


}
