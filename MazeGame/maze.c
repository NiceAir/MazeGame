#include "Maze.h"
#include <stdio.h>

void InitMaze(Maze *m, int map[MAXROW][MAXCOL]) //初始化迷宫
{
    int i = 0;
    int j = 0;
    for (i = 0; i<MAXROW; i++)
    {
        for (j = 0; j<MAXCOL; j++)
        {
            m->map[i][j] = map[i][j];
        }
    }
}


void PrintMaze(Maze m)  //打印迷宫
{
    int i = 0;
    int j = 0;
    for (i = 0; i<MAXROW; i++)
    {   
        for (j = 0; j<MAXCOL; j++)
        {
            printf("%d ", m.map[i][j]);
        }
        printf("\n");
    }
}

static int CheckUp(Maze *m, Postion now)    //检查当前位置上方是否可行
{
    if (now.x-1 >= 0 && m->map[now.x-1][now.y] == 1)
    {
        return 1;
    }
    return 0;
}
  
static int CheckDown(Maze *m, Postion now)  //检查当前位置下方是否可行
{
    if (now.x+1 <= MAXROW-1 && m->map[now.x+1][now.y] == 1)
    {
        return 1;
    }
    return 0;
}

static int CheckRight(Maze *m, Postion now) //检查当前位置右方是否可行
{
    if (now.y+1 <= MAXROW-1 && m->map[now.x][now.y+1] == 1)
    {
        return 1;
    }
    return 0;
}

static int CheckLeft(Maze *m, Postion now)  //检查当前位置左方是否可行
{
    if (now.y-1 >= 0 && m->map[now.x][now.y-1] == 1)
    {
        return 1;
    }
    return 0;
}


static Postion RollBack(Maze *m, Postion now)   //回退
{
    if (now.x == 0)            //若在出口位置，直接往来时的方向退一步
        now.x++;
    else if (now.x == MAXROW-1)
        now.x--;
    else if (now.y == 0)
        now.y++;
    else if (now.y == MAXCOL-1)
        now.y--;
    else 
    {                   //若在普通位置，则选择最优回退路线
        Postion cache;
        cache.x = now.x;
        cache.y = now.y;
        if (m->map[now.x-1][now.y] != 0 && m->map[now.x][now.y] > m->map[now.x-1][now.y])
        {
             cache.x = now.x-1;
             cache.y = now.y;
        } 
        if (m->map[now.x+1][now.y] != 0 && m->map[now.x][now.y] > m->map[now.x+1][now.y])
        {
            cache.x = now.x+1;
            cache.y = now.y;
        }
        if (m->map[now.x][now.y-1] != 0 && m->map[now.x][now.y] > m->map[now.x][now.y-1])
        {
            cache.x = now.x;
            cache.y = now.y-1;
        }
        if (m->map[now.x][now.y+1] != 0 && m->map[now.x][now.y] > m->map[now.x][now.y+1])
        {
            cache.x = now.x;
            cache.y = now.y+1;
        }
        now.x = cache.x;
        now.y = cache.y;
    }
    return now;
}

void PassMaze(Maze *m, Postion start) //走迷宫
{
    Postion now;
    now.x = start.x;
    now.y = start.y;
    m->map[start.x][start.y] = 2;
    while(1)
    {                               //前进方向为上、下、右、左，依次检查各个方向。若各个方向都不能，则回退到合适位置
        if (CheckUp(m, now))    //向上走
        {
            m->map[now.x-1][now.y] = m->map[now.x][now.y] + 1;
            now.x--;
        }
        else if (CheckDown(m, now)) //走不通则向下走
        {
            m->map[now.x+1][now.y] = m->map[now.x][now.y] + 1;
            now.x++;
        }
        else if (CheckRight(m, now))    //走不通则向右走
        {
            m->map[now.x][now.y+1] = m->map[now.x][now.y] + 1;
            now.y++;
        }
        else if (CheckLeft(m, now)) //走不通则向左走
        {
            m->map[now.x][now.y-1] = m->map[now.x][now.y] + 1;
            now.y--;
        }
        else    //若还是走不通，则回退到合适位置
        {
            now = RollBack(m, now);
            if (now.x == start.x && now.y == start.y)
            {
                break;
            }
        }
    }
}

static Postion NextBiggest(Maze *m, Postion now)    //选择周围标记数最大的位置，
{                                                   //返回之前都把所选位置的标记数置为当前位置标记数加1
    Postion cache;
    cache.x = now.x;
    cache.y = now.y;    //若在起点，选择前进一步的位置
    if (now.x == 0)  
        cache.x++;       
    else if (now.x == MAXROW-1)  
        cache.x--;
    else if (now.y == 0)    
        cache.y++;
    else if (now.y == MAXCOL-1)
        cache.y--;
    if (cache.x != now.x || cache.y != now.y)
    {
        m->map[cache.x][cache.y] = m->map[now.x][now.y] + 1;
        return cache;
    }
                            
    cache.x = now.x-1;          //若不在起点，则在上下左右四个位置中选标记数最大的
    if (m->map[cache.x][cache.y] < m->map[now.x+1][now.y])
    {
        cache.x = now.x+1;
        cache.y = now.y;
    }
    if (m->map[cache.x][cache.y] < m->map[now.x][now.y-1])
    {
        cache.x = now.x;
        cache.y = now.y-1;
    }
    if (m->map[cache.x][cache.y] < m->map[now.x][now.y+1])
    {
        cache.x = now.x;
        cache.y = now.y+1;
    }
    m->map[cache.x][cache.y] = m->map[now.x][now.y] + 1;
    return cache;
}

void GoFllowedBySign(Maze *m)   //对整个迷宫进行标记整理
{
    Postion now;
    now.x = 0;
    now.y = 1;
    m->map[now.x][now.y] = 1;
    while(1)
    {
         now = NextBiggest(m, now);
         if ( !(now.x > 0 && now.x < MAXROW-1 && now.y > 0 && now.y <MAXCOL-1) )
            break;
    }
    
}