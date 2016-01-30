/*
ID: kevinli7
PROG: charrec
LANG: C++11
*/
#include <iostream>
#include <fstream>
using namespace std;
string letter[27][21], file[1211];
int dist[27][21][1211],x[1211];
int pred[1211],car[1211];
int nletter,nline;
ofstream fout("charrec.out");
void init()
{
    for (int i = 0; i < nletter; ++i)
        for (int j = 0; j < 20; ++j)
            for (int k = 0; k < nline; ++k)
                dist[i][j][k] = -1;
    for (int i = 0; i <= nline; ++i)
        x[i] = pred[i] = car[i] = -1;
    x[0] = 0;
}
long diff(const string &a, const string &b)
{
    long i,ndif = 0;
    for (i = 0; i < 20; ++i)
        ndif += a[i]^b[i];
    return ndif;
}
void cal()
{
    long i,j,k,t,dif;
    for (i = 0; i < nline; ++i)
        if (x[i] != -1)
        {
            for (j = 0; j < nletter; ++j)
            {
                //missing one line
                if (i + 19 <= nline)
                {
                    dif = 0;
                    //default missing the  0th line
                    for (t = 0; t < 19; ++t)
                    {
                        if (dist[j][t+1][i+t] == -1)
                            dist[j][t+1][i+t] = diff(letter[j][t+1],
                                    file[i+t]);
                        dif += dist[j][t+1][i+t];
                    }
                    if ((x[i+19] == -1 || dif + x[i] < x[i+19])
                            && dif <= 114)
                    {
                        x[i+19] = x[i] + dif;
                        pred[i+19] = i;
                        car[i+19] = j;
                    }
                    for  (k = 1; k < 20; ++k)
                    {
                        if (dist[j][k-1][i+k-1] == -1)
                            dist[j][k-1][i+k-1] = diff(letter[j][k-1],
                                    file[i+k-1]);
                        if (dist[j][k][i+k-1] == -1)
                            dist[j][k][i+k-1] = diff(letter[j][k],
                                    file[i+k-1]);
                        dif += dist[j][k-1][i+k-1]-dist[j][k][i+k-1];
                        if ((x[i+19] == -1 || dif + x[i] < x[i+19])
                                && dif <= 114)
                        {
                            x[i+19] = x[i] + dif;
                            pred[i+19] = i;
                            car[i+19] = j;
                        }
                    }
                }
                //no missing
                if (i + 20 <= nline)
                {
                    dif = 0;
                    for (t = 0; t < 20; ++t)
                    {
                        if (dist[j][t][i+t] == -1)
                            dist[j][t][i+t] = diff(letter[j][t],
                                    file[i+t]);
                        dif += dist[j][t][i+t];
                    }
                    if ((x[i+20] == -1 || dif + x[i] < x[i+20])
                            && dif <= 120)
                    {
                        x[i+20] = x[i] + dif;
                        pred[i+20] = i;
                        car[i+20] = j;
                    }
                }
                //duplicate a line
                if (i + 21 <= nline)
                {
                    dif = 0;
                    for (t = 0; t < 20; ++t)
                    {
                        if (dist[j][t][i+t+1] == -1)
                            dist[j][t][i+t+1] = diff(letter[j][t],
                                    file[i+t+1]);
                        dif += dist[j][t][i+t+1];
                    }
                    if ((x[i+21] == -1 || dif + x[i] < x[i+21])
                            && dif <= 120)
                    {
                        x[i+21] = x[i] + dif;
                        pred[i+21] = i;
                        car[i+21] = j;
                    }
                    for (k = 1; k < 21; ++k)
                    {
                        if (dist[j][k-1][i+k-1] == -1)
                            dist[j][k-1][i+k-1] = diff(letter[j][k-1],
                                    file[i+k-1]);
                        if (dist[j][k-1][i+k] == -1)
                            dist[j][k-1][i+k] = diff(letter[j][k-1],
                                    file[i+k]);
                        dif += dist[j][k-1][i+k-1]-dist[j][k-1][i+k];
                        if ((x[i+21] == -1 || dif + x[i] < x[i+21])
                                && dif <= 120)
                        {
                            x[i+21] = x[i] + dif;
                            pred[i+21] = i;
                            car[i+21] = j;
                        }
                    }
                }
            }
        }
}
void recon(long k)
{
    long t;   
    if (pred[k] != -1)
    {
        recon(pred[k]);
        t = car[k];
        if (t == 0)
            fout << ' ';
        else
            fout << char(t+96);
    }
}
int main()
{
    ifstream fin("charrec.in");
    ifstream font("font.in");
    font >> nletter;
    nletter /= 20;
    for (int i = 0; i < nletter; ++i)
        for (int j = 0; j < 20; ++j)
            font >> letter[i][j];
    font.close();
    fin >> nline;
    for (int i = 0; i < nline; ++i)
        fin >> file[i];
    fin.close();
    init();
    cal();
    recon(nline);
    fout << endl;
    fout.close();
}
