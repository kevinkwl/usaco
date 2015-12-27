/*
ID: kevinli7
PROG: ttwo
LANG: C++11
*/
#include <iostream>
#include <fstream>
#include <map>
using namespace std;
enum Dir{North, East, South, West};
char grid[10][10];
bool record[10][10][4][10][10][4];
struct Object
{
    int r;
    int c;
    Dir dir; 
};
Object farmer;
Object cow;
int steps;

bool visited(Object &f, Object &c)
{
    return record[f.r][f.c][f.dir][c.r][c.c][c.dir];

}
void visit(Object &f, Object &c)
{
    record[f.r][f.c][f.dir][c.r][c.c][c.dir] = true;
}

void update(Object & obj)
{
    // update ;
    switch(obj.dir)
    {
        case North: 
            if (obj.r > 0 && grid[obj.r-1][obj.c] != '*')
                --obj.r;
            else
                obj.dir = East;
            break;
        case East:
            if (obj.c < 9 && grid[obj.r][obj.c+1] != '*')
                ++obj.c;
            else
                obj.dir = South;
            break;
        case South:
            if (obj.r < 9 && grid[obj.r+1][obj.c] != '*')
                ++obj.r;
            else
                obj.dir = West;
            break;
        case West:
            if (obj.c > 0 && grid[obj.r][obj.c-1] != '*')
                --obj.c;
            else
                obj.dir = North;
            break;
    }

}

bool meet()
{
    return farmer.r == cow.r && farmer.c == cow.c;
}

int main()
{
    ifstream fin("ttwo.in");
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 10; ++j)
        {
            fin >> grid[i][j];
            if (grid[i][j] == 'F')
            {   
                farmer.r = i;
                farmer.c = j;
                farmer.dir = North;
            }
            if (grid[i][j] == 'C')
            {
                cow.r = i;
                cow.c = j;
                cow.dir = North;
            }
        }
    fin.close();
    
    for (int i = 0;; ++i)
    {
        if (visited(farmer, cow))
            break;
        visit(farmer, cow);
        if (meet())
        {
            steps = i;
            break;
        }
        update(farmer);
        update(cow);
    }

    ofstream fout("ttwo.out");
    fout << steps << endl;



}
