/*
ID: kevinli7
PROG: maze1
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>
using namespace std;
#define north 1
#define east 2
#define south 4
#define west 8
#define W_MAX 39
#define H_MAX 101

struct vertex
{
    int dis;
    int wall;
};
vertex maze[H_MAX][W_MAX];
char maze_map[2*H_MAX+1][2*W_MAX+1];
int W,H;
// exits
int row[2];
int col[2];
int longest;
int cnt;
char ch;
int n,e,s,w;

bool visited[H_MAX][W_MAX];
void init()
{
    for (int i = 1; i <= H; ++i)
        for (int j = 1; j <= W; ++j)
        {
            if (maze_map[2*i-1][2*j] == '-')
                maze[i][j].wall |= north;
            if (maze_map[2*i][2*j+1] == '|')
                maze[i][j].wall |= east;
            if (maze_map[2*i+1][2*j] == '-')
                maze[i][j].wall |= south;
            if (maze_map[2*i][2*j-1] == '|')
                maze[i][j].wall |= west;
        }
}

void bfs()
{
    fill_n(*visited, sizeof(visited),0);
    queue<pair<pair<int,int>,int>> bq;
    bq.push(make_pair(make_pair(row[0], col[0]), 1));
    bq.push(make_pair(make_pair(row[1], col[1]), 1));
    while (!bq.empty())
    {
        auto pa = bq.front();bq.pop();
        auto p = pa.first;
        if (visited[p.first][p.second])
            continue;
        visited[p.first][p.second] = true;
        int dis = pa.second;
        
        //cout << p.first << ' ' << p.second << ' '<< dis <<endl;
        maze[p.first][p.second].dis = dis;
        int wall = maze[p.first][p.second].wall;
        if (!(wall & north) && p.first > 1)
            bq.push(make_pair(make_pair(p.first-1,p.second), dis+1));

        if (!(wall & east) && p.second < W)
            bq.push(make_pair(make_pair(p.first,p.second+1), dis+1));

        if (!(wall & south) && p.first < H)
            bq.push(make_pair(make_pair(p.first+1,p.second), dis+1));
        
        if (!(wall & west) && p.second > 1)
            bq.push(make_pair(make_pair(p.first,p.second-1), dis+1));
    }
}

int findMax()
{
    int d = 0;
    for (int i = 1; i <= H; ++i)
    {
        for (int j = 1; j <= W; ++j)
        {
            //cout << maze[i][j].dis << ' ';
            if (maze[i][j].dis > d)
                d = maze[i][j].dis;
        }
        //cout << endl;
    }
    return d;
}

int main()
{
    ifstream fin("maze1.in");
    fin >> W >> H;
    fin.get();
    for (int i = 1; i <= 2*H + 1; ++i, fin.get())
    {
        for (int j = 1; j <= 2*W + 1; ++j)
        {
            fin.get(ch);
            maze_map[i][j] = ch;
            if (ch == ' ' && cnt < 2)            
            {
                if (i == 1 || i == 2*H+1)
                {
                    row[cnt] = (i == 1)? 1: H;
                    col[cnt] = j/2;
                    ++cnt;
                }
                if (j == 1 || j == 2*W+1)
                {
                    col[cnt] = (j == 1)? 1: W;
                    row[cnt] = i/2;
                    ++cnt;
                }
            }
        }
    }
    fin.close();

    init();
 

    bfs();
    longest = findMax();
    ofstream fout("maze1.out");
    fout << longest << endl;
    

    
}
