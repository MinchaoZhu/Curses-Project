#ifndef FLAPPY
#define FLAPPY
#include <curses.h>
#include <sys/time.h>
#include <time.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>



#define WLINES _maxy+1
#define WCOLS _maxx+1
#define MAINWINDOWLINES 40
#define MAINWINDOWCOLS 100
#define INFORWINDOWLINES MAINWINDOWLINES
#define INFORWINDOWCOLS 22
#define PLANELINES 5
#define PLANECOLS 7
#define WALLWIDTH 10
#define FREEWIDTH 30
#define WALLCELLCOLS (WALLWIDTH+FREEWIDTH)
#define WALLNUM (MAINWINDOWCOLS/WALLCELLCOLS)
#define BASETIME 50
#define vFull 3
#define RUN 0
#define PAUSE 1

typedef struct point{
    int x;
    int y;
}point, *ppoint;

typedef struct planedef{
    int posLine;
    int posCol;
    int lines;
    int cols;
    point body[12];
    int stat;
    int v;
}planedef,pplanedef;

typedef struct walldef{
    int end1;
    int end2;
    int freeHigh;
    int pos;
}walldef,*pwalldef;

walldef wall[WALLNUM+1];
planedef plane;
int vInterval;
int GAMESTAT;
int SCORE;

void init();
void initWin1();
void paintPlane();
void paintWall();
void paintEdge();
void fly();
int set_ticker(int msec);
void updateWin0();
int collision();
void pauseGame();

WINDOW *win0,*win1;

#endif