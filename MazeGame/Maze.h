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

void InitMaze(Maze *m, int map[MAXROW][MAXCOL]); //��ʼ���Թ�
void PrintMaze(Maze m);  //��ӡ�Թ�
void PassMaze(Maze *m, Postion start); //����Թ�
void GoFllowedBySign(Maze *m);//���ű����

