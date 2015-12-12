/*
ID: kevinli7
PROG: castle
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
#define W_MAX 51
#define w 1
#define n 2
#define e 4
#define s 8
int castle[W_MAX][W_MAX];
int visited[W_MAX][W_MAX];
int M, N;
int wall;
int best = 0, the_size = 0;
int pos_x, pos_y;
string dir;
void visit(int i, int j)
{
    ++the_size;
    visited[i][j] = 1;
    if (!(castle[i][j] & w) && !visited[i][j-1])
        visit(i,j-1);
    if (!(castle[i][j] & n) && !visited[i-1][j])
        visit(i-1,j);
    if (!(castle[i][j] & e) && !visited[i][j+1])
        visit(i,j+1);
    if (!(castle[i][j] & s) && !visited[i+1][j])
        visit(i+1,j);
}
void printCastle()
{
    for (int i = 0; i < M*4+1; ++i)   
        cout << '#';
    cout << endl;
    for (int i = 1; i <= N; ++i)
    {
        cout << '#';
        for (int j = 1; j <= M; ++j)
        {
            cout << "   ";
            if (castle[i][j]&e)
                cout << '#';
            else
                cout << '|';
        }
        cout << endl;
        cout << '#';
        for (int j = 1; j <= M; ++j)
        {
            if (castle[i][j] &s)
                cout << "###";
            else
                cout <<"---";
            cout << '#';
        }
        cout <<endl;
    }

}


int cal_room(int & largest)
{
    memset(visited, 0, sizeof(visited));
    int cnt = 0;
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= M; ++j)
            if (!visited[i][j])
            {
                ++cnt;
                visit(i,j);
                if (the_size > largest)
                    largest = the_size;
                the_size = 0;
            }
    return cnt;
}
void brkwall()
{
    int new_largest;
    for (int i = 1 ; i <= N; ++i)
        for (int j = 1; j <= M; ++j)
        {
            new_largest = 0;
            if (j != M)
            {
                if (castle[i][j]& e)
                {
                    castle[i][j] ^=e;
                    castle[i][j+1] ^=w;
                    cal_room(new_largest);
                    if (new_largest > best)
                    {
                        best = new_largest;
                        pos_x = i, pos_y = j;
                        dir = "E";
                    }
                    if (new_largest == best && j <= pos_y && i >= pos_y)
                    {
                        pos_x = i, pos_y = j;
                        dir = "E";
                    }
                    castle[i][j] ^=e;
                    castle[i][j+1] ^= w;
                }
            new_largest = 0;
            }
            if (i != 1)
            {
                if (castle[i][j]& n)
                {
                    castle[i][j] ^=n;
                    castle[i-1][j] ^=s;
                    cal_room(new_largest);
                    if (new_largest > best)
                    {
                        best = new_largest;
                        pos_x = i, pos_y = j;
                        dir = "N";
                    }
                    if (new_largest == best && i >= pos_x && j <= pos_y)
                    {
                        pos_x = i, pos_y = j;
                        dir = "N";
                    }
                    castle[i][j] ^=n;
                    castle[i-1][j] ^=s;
                }
            }
                    
        }
}



int main()
{
    ifstream fin("castle.in");
    fin >> M >> N;
    for (int i = 1; i <= N; ++i)
        for (int j = 1; j <= M; ++j)
        {
            fin >> castle[i][j];
        }    
    fin.close();
    //printCastle();

    ofstream fout("castle.out");
    fout << cal_room(best) << endl;
    fout << best << endl;

    brkwall();
    fout << best << endl;
    fout << pos_x << ' ' << pos_y << ' ' << dir << endl;
    fout.close();
}
