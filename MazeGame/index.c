#include "Maze.h"
#include <stdio.h>

int main()
{
    Maze m;
    int map[MAXROW][MAXCOL] = { {0,1,0,0,0},
                                {0,1,1,1,1},
                                {0,1,0,1,0},
                                {0,1,1,1,0},
                                {0,0,0,0,0}, };
    Postion start;
    start.x = 0;
    start.y = 1;
    InitMaze(&m, map);  //初始化迷宫
    PrintMaze(m);
    printf("\n\n");

    PassMaze(&m, start);    //预处理
    PrintMaze(m);
    printf("\n\n"); 

    GoFllowedBySign(&m);    //按标记走
    PrintMaze(m);
    return 0;
}
