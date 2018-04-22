#include "Maze.h"
#include <stdio.h>

void InitMaze(Maze *m, int map[MAXROW][MAXCOL]) //≥ı ºªØ√‘π¨
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


void PrintMaze(Maze m)  //¥Ú”°√‘π¨
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

static int CheckUp(Maze *m, Postion now)
{
    if (now.x-1 >= 0 && m->map[now.x-1][now.y] == 1)
    {
        return 1;
    }
    return 0;
}
  
static int CheckDown(Maze *m, Postion now)
{
    if (now.x+1 <= MAXROW-1 && m->map[now.x+1][now.y] == 1)
    {
        return 1;
    }
    return 0;
}

static int CheckRight(Maze *m, Postion now)
{
    if (now.y+1 <= MAXROW-1 && m->map[now.x][now.y+1] == 1)
    {
        return 1;
    }
    return 0;
}

static int CheckLeft(Maze *m, Postion now)
{
    if (now.y-1 >= 0 && m->map[now.x][now.y-1] == 1)
    {
        return 1;
    }
    return 0;
}


static Postion RollBack(Maze *m, Postion now)
{
    if (now.x == 0)
        now.x++;
    else if (now.x == MAXROW-1)
        now.x--;
    else if (now.y == 0)
        now.y++;
    else if (now.y == MAXCOL-1)
        now.y--;
    else 
    {
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

void PassMaze(Maze *m, Postion start) //◊ﬂ√‘π¨
{
    Postion now;
    now.x = start.x;
    now.y = start.y;
    m->map[start.x][start.y] = 2;
    while(1)
    {
        if (CheckUp(m, now))
        {
            m->map[now.x-1][now.y] = m->map[now.x][now.y] + 1;
            now.x--;
        }
        else if (CheckDown(m, now))
        {
            m->map[now.x+1][now.y] = m->map[now.x][now.y] + 1;
            now.x++;
        }
        else if (CheckRight(m, now))
        {
            m->map[now.x][now.y+1] = m->map[now.x][now.y] + 1;
            now.y++;
        }
        else if (CheckLeft(m, now))
        {
            m->map[now.x][now.y-1] = m->map[now.x][now.y] + 1;
            now.y--;
        }
        else
        {
            now = RollBack(m, now);
            if (now.x == start.x && now.y == start.y)
            {
                break;
            }
        }
    }
}

static Postion NextBiggest(Maze *m, Postion now)
{
    Postion cache;
    cache.x = now.x;
    cache.y = now.y;
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

    cache.x = now.x-1;
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

void GoFllowedBySign(Maze *m)
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