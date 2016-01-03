/*
ID: kevinli7
PROG: shopping
LANG: C++11
*/
#include <iostream>
#include <fstream>
#define for(k,N,s) for(int k = s; k <= (N); ++k)
using namespace std;
const int SMAX = 100;
int F[6][6][6][6][6];
int code[1000];
int s,n,c,k,p,b;
int price[6];
int offer[SMAX][6];
int offerp[SMAX];
int basket[6];
int cnt = 1,mprice;
/*
void show()
{
    cout << "code: " << endl;
    for(i,1000,1)
        if (code[i])
            cout << i << ':' << code[i] << endl;
    cout << "<<<<<---->>>>>>" << endl << "offer :" << endl;
    for(i,s,1)
        for(k,5,1)
            cout << k << ' ' << offer[i][k] << ' ' << offerp[i] <<  endl;
}
*/
int main()
{
    ifstream fin("shopping.in");
    fin >> s;
    for(i,s,1)
    {
        fin >> n;
        for(j,n,1)
        {
            fin >> c >> k;
            if (!code[c])
                code[c] = cnt++;
            offer[i][code[c]] = k;
        }
        fin >> p;
        offerp[i] = p; 
    }
    fin >> b;
    for(i,b,1)
    {
        fin >> c >> k >> p;
        if (!code[c])
            code[c] = cnt++;
        basket[code[c]] = k;
        price[code[c]] = p;
        mprice += k*p;
    }
    fin.close();

   // show();
    int newprice;
    for(i,basket[1],0)
    for(j,basket[2],0)
    for(k,basket[3],0)
    for(l,basket[4],0)
    for(m,basket[5],0)
        F[i][j][k][l][m] = i*price[1]+j*price[2]+k*price[3]+l*price[4]+m*price[5];
    for(w,s,1)
    for(i,basket[1],0)
    for(j,basket[2],0)
    for(k,basket[3],0)
    for(l,basket[4],0)
    for(m,basket[5],0)
    {
        if (i>=offer[w][1] && j>=offer[w][2] && k>=offer[w][3] && l>=offer[w][4] && m >= offer[w][5])
        {
           newprice  = F[i-offer[w][1]][j-offer[w][2]][k-offer[w][3]][l-offer[w][4]][m-offer[w][5]];
           newprice += offerp[w];
           if (newprice < F[i][j][k][l][m])
               F[i][j][k][l][m] = newprice;
        }
       // cout << i << ' ' << j << ' ' << k << ' ' << l << ' ' << m << endl;
       // cout << offer[w][1] << offer[w][2] << offer[w][3]<<offer[w][4]<<offer[w][5]<<endl;
       // cout << F[i][j][k][l][m] << endl;
    }
    ofstream fout("shopping.out");
    fout << F[basket[1]][basket[2]][basket[3]][basket[4]][basket[5]] << endl;
    fout.close();

    
}
