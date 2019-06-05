#ifndef SNAKE_H
#define SNAKE_H
#include <signal.h>
#include <curses.h>
#include <unistd.h>
#include <sys/time.h>
#include <stdlib.h>

#define direct int
#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3
#define SCORE (snake0.length)
#define BASETIME 100


#define RUN 0
#define PAUSE 1
#define OVER 2

#define INTMAX 2147483647


typedef struct point{
    int x;
    int y;
}point,*ppoint;

typedef struct snake{
    direct direction;
    point body[5000];
    int length;
}snake,*psnake;

typedef point Food;
snake snake0;
Food food;

int gameStat;
int gameSpeed;

void snakeMove(int signum);  
void snakeMoveSubFunc();
int set_ticker(int msec);
void init();
bool collision();
void genFood();
void fresh();
int myRand();

void blankFun();

#endif