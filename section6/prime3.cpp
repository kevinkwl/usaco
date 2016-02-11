/*
ID: kevinli7
PROG: prime3
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
using namespace std;
int prime[100000][7], num[6][6];
int primenum[1000],size;
int sum,start;
string ans[10000];
int m;
void show()
{
    int i,j;
    for (i = 1;i<=5;++i)
    {
        for (j=1;j<=5;++j)
            cout << num[i][j] << ' ';
        cout << endl;
    }
    cout << endl;

}
bool isprime(int n)
{
    if (prime[n][0] == -1)
        return false;
    if (prime[n][0] == 1)
        return true;
    for (int i = 2; i*i <= n; ++i)
        if (n%i == 0)
        {
            prime[n][0] = -1;
            return false;
        }
    prime[n][0] = 1;
    return true;
}
void genprime()
{
    for (int i = 10001; i <= 99999; ++i)
        if (isprime(i))
        {
            prime[i][1] = i/10000;
            prime[i][2] = (i/1000)%10;
            prime[i][3] = (i/100)%10;
            prime[i][4] = (i/10)%10;
            prime[i][5] = i%10;
            for (int j = 1; j <= 5; ++j)
                prime[i][6] += prime[i][j];
            if (prime[i][6] == sum)
                primenum[size++] = i;
        }
}
bool check(int x1,int x2,int x3,int x4,int x5)
{
    int p = x1*10000+x2*1000+x3*100+x4*10+x5;
    if (prime[p][0] == 1 && prime[p][6] == sum)
        return true;
    return false;
}
void finalCheck()
{
    ans[m] = "";
    int i,j;
    // check row 3
    if (!check(num[3][1],num[3][2],num[3][3],num[3][4],num[3][5]))
        return;
    // check col 1
    if (!check(num[1][1],num[2][1],num[3][1],num[4][1],num[5][1]))
        return;
    // col 5
    if (!check(num[1][5],num[2][5],num[3][5],num[4][5],num[5][5]))
        return;
    for (i = 1;i<=5;++i)
        for (j=1;j<=5;++j)
            ans[m] += to_string(num[i][j]);
    ++m;
}
void solveRow24()
{
    int i,j,k,l,p;
    for (i = 1;i<=9;++i) // num[2][1]
    for (j = 1;j<=9;j+=2) // num[2][5]
    {
        num[2][1] = i;
        num[2][5] = j;
        if (!check(num[2][1],num[2][2],num[2][3],num[2][4],num[2][5]))
            continue;

    for (k = 1;k<=9;++k)// num[4][1]
    for (l = 1;l<=9;l+=2)// num[4][5]
    {
        num[4][1] = k;
        num[4][5] = l;
        if (!check(num[4][1],num[4][2],num[4][3],num[4][4],num[4][5]))
            continue;
        num[3][1] = sum - num[1][1]-num[2][1]-num[4][1]-num[5][1];
        num[3][5] = sum - num[1][5]-num[2][5]-num[4][5]-num[5][5];
 
        if (num[3][1] >0 && num[3][1] <= 9 &&
            num[3][5] >0 && num[3][5] <= 9)
        {
            finalCheck();
        }
    }
    }
}
void solveRow15()
{
    int i,j,k,l,p;
    for (i = 1;i<=9;++i) // num[1][2]
    for (j = 1;j<=9;++j) // num[1][4]
    {
        num[1][2] = i;
        num[1][4] = j;
        if (!check(num[1][1],num[1][2],num[1][3],num[1][4],num[1][5]))
            continue;            // breakpoint

    for (k = 1;k<=9;k+=2)// num[5][2]
    for (l = 1;l<=9;l+=2)// num[5][4]
    {
        num[5][2] = k;
        num[5][4] = l;
        if (!(check(num[5][1],num[5][2],num[5][3],num[5][4],num[5][5])))
            continue;

        num[3][2] = sum - num[1][2]-num[2][2]-num[4][2]-num[5][2];
        num[3][4] = sum - num[1][4]-num[2][4]-num[4][4]-num[5][4];

        if (num[3][2] >=0 && num[3][2] <= 9 &&
            num[4][2] >=0 && num[4][2] <= 9)
        {            
            if (check(num[1][2],num[2][2],num[3][2],num[4][2],num[5][2])
               && check(num[1][4],num[2][4],num[3][4],num[4][4],num[5][4]))
            {

                solveRow24();
            }
        }
    }
    }
}
void solveCol3()
{
    int i,j,k,p;
    //Col 3
    for (i = 0;i<size;++i)
    {
        p = primenum[i];
        if (prime[p][3] == num[3][3] && prime[p][6] == sum)
        {
            num[1][3] = prime[p][1];
            num[2][3] = prime[p][2];
            num[4][3] = prime[p][4];
            num[5][3] = prime[p][5];


            solveRow15();
        }

    }
}


int main()
{
    ifstream fin("prime3.in");
    fin >> sum >> start;
    fin.close();
    num[1][1] = start;
    genprime();
    int i,j,k;
    int p,pre;
    for (i = 0;i< size;++i)
    {
        p = primenum[i];
        pre = p;
        if (prime[p][1] == start && prime[p][6] == sum)
        {

            for (j = 2; j <= 5; ++j)
                num[j][j] = prime[p][j];
            
            // another diagonal
            for (j = 0;j<size;++j)
            {
                p = primenum[j];
                if (prime[p][3] == num[3][3] & prime[p][6] == sum)
                {
                    for (k = 1;k<=5;++k)
                        num[k][6-k] = prime[p][6-k];
                    solveCol3();
                }
            }
        }
    }
    sort(ans,ans+m);
    ofstream fout("prime3.out");
    for (i = 0; i < m; ++i)
    {
        if (i != 0)
            fout << endl;
        for (j = 0; j < 25; ++j)
        {
            if (j != 0 && j%5 == 0)
                fout << endl;
            fout << ans[i][j];
        }
        fout << endl;
    }
    fout.close();
}
