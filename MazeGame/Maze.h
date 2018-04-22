#pragma once
#define MAXROW 5
#define MAXCOL 5
typedef struct maze{
    int map[MAXROW][MAXCOL];
}Maze;

typedef struct positon{
    int x;
    int y;
}Postion;

void InitMaze(Maze *m, int map[MAXROW][MAXCOL]); //初始化迷宫
void PrintMaze(Maze m);  //打印迷宫
void PassMaze(Maze *m, Postion start); //标记迷宫
void GoFllowedBySign(Maze *m);//跟着标记走

