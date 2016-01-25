/*
ID: kevinli7
PROG: snail
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
const int NMAX = 120;
int N,B;
char maze[NMAX][NMAX];
bool vis[NMAX][NMAX];
int ds[4][2] = {{-1,0},{0,1},{1,0},{0,-1}}; // up right down left
int longest,cur;

void show()
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
            cout << maze[i][j] << ' ';
        cout << endl;
    }
    cout << endl;
}
void walk(int r, int c, int dir)
{
    int nr = r + ds[dir][0], nc = c + ds[dir][1];
    if (nr >= 0 && nr < N && nc >= 0 && nc < N &&
            maze[nr][nc] != '#' && !vis[nr][nc])
    {
                vis[nr][nc] = 1;
                ++cur;
                walk(nr,nc,dir);
                --cur;
                vis[nr][nc] = 0;
    }
    else if (nr < 0 || nr >= N)
    {
        if (c < N-1)
            walk(r,c,1);
        if (c > 0)
            walk(r,c,3);
    }
    else if (nc < 0 || nc >= N)
    {
        if (r > 0)
            walk(r,c,0);
        if (r < N-1)
            walk(r,c,2);
    }
    else if (maze[nr][nc] == '#')
    {
        switch (dir)
        {
            case 0: case 2:
                if (c < N-1 && maze[r][c+1] != '#')
                    walk(r,c,1);
                if (c > 0 && maze[r][c-1] != '#')
                    walk(r,c,3);
                break;
            case 1: case 3:
                if (r > 0 && maze[r-1][c] != '#')
                    walk(r,c,0);
                if (r < N-1 && maze[r+1][c] != '#')
                    walk(r,c,2);
                break;
        }
    }
    if (cur > longest)
        longest = cur;
    return;
}


int main()
{
    ifstream fin("snail.in");
    fin >> N >> B;
    char c;
    int r;
    memset(maze, '.', sizeof(maze));
    for (int i = 0; i < B; ++i)
    {
        fin >> c >> r;
        maze[r-1][c-'A'] = '#'; 
    }

    longest = cur = 1;
    for (int i = 0; i < 4; ++i)
    {
        vis[0][0] = true;
        walk(0,0,i);
    }
    
    ofstream fout("snail.out");
    fout << longest << endl;
    fout.close();
}
