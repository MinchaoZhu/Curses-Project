#include "snake.h"
#include <stdlib.h>
#include <math.h>
#include <time.h>

int myRand(int seed){
    return (seed * 16807L) % 2147483647;
}
int set_ticker(int n_msecs) 
{
    struct itimerval new_timeset;
    long n_sec,n_usecs;

    n_sec = n_msecs/1000;
    n_usecs=(n_msecs%1000)*1000L;

    new_timeset.it_interval.tv_sec=n_sec;
    new_timeset.it_interval.tv_usec=n_usecs;

    new_timeset.it_value.tv_sec = n_sec;
    new_timeset.it_value.tv_usec= n_usecs;

    return setitimer(ITIMER_REAL,&new_timeset,NULL);
}



void init(){
    gameSpeed = BASETIME;
    gameStat = RUN;
    // initialize the wall
    for(int i=0;i<COLS;++i){
        mvaddch(0,i,'#');
        mvaddch(LINES-2,i,'#');
    }
    for(int i=0;i<LINES;++i){
        mvaddch(i,0,'#');
        mvaddch(i,COLS-1,'#');
    }

    //initialize snake0
    snake0.direction = RIGHT;
    snake0.length = 1;
    snake0.body[0].x = LINES/2;
    snake0.body[0].y = COLS/2;
    mvaddch(snake0.body[0].x,snake0.body[0].y,'>');
    //initialize food
    genFood(0);
    mvprintw(LINES-1,0,"Score: %d, press 'p' to pause, 'q' to quit, 'r' to reload game, 'wasd' to change direction\n", SCORE);
}

void genFood(int flag){
    bool valid=0;
        if(flag==0){
            srand(time(0));
        }
        do{ 
            food.x = 1 + rand()%(LINES-3);
            food.y = 1 + rand()%(COLS-2);
            for(int i=0;i<snake0.length;++i){
                if(snake0.body[i].x==food.x&&snake0.body[i].y==food.y){
                    valid=0;
                    break;
                }
                valid = 1;
            }
        }while(!valid);
    
    mvaddch(food.x,food.y,'$');
}

bool collision(){
    if(snake0.body[0].x==0||snake0.body[0].x==LINES-2||snake0.body[0].y==0||snake0.body[0].y==COLS-1)
        return 1;
    for(int i = 1;i<snake0.length;++i){
        if(snake0.body[0].x==snake0.body[i].x&&snake0.body[0].y==snake0.body[i].y)
            return 1;
    }
    return 0;
}

void snakeMove(int signum){
    int tailx = snake0.body[snake0.length-1].x;
    int taily = snake0.body[snake0.length-1].y;
    int headx = snake0.body[0].x;
    int heady = snake0.body[0].y;
    snakeMoveSubFunc();
    switch(snake0.direction){
        case DOWN:
            snake0.body[0].x = headx+1;
            snake0.body[0].y = heady;
            mvaddch(snake0.body[0].x,snake0.body[0].y,'v');
            break;
        case RIGHT:
            snake0.body[0].x = headx;
            snake0.body[0].y = heady+1;
            mvaddch(snake0.body[0].x,snake0.body[0].y,'>');
            break;
        case UP:
            snake0.body[0].x = headx-1;
            snake0.body[0].y = heady;
            mvaddch(snake0.body[0].x,snake0.body[0].y,'^');
            break;
        case LEFT:
            snake0.body[0].x = headx;
            snake0.body[0].y = heady-1;
            mvaddch(snake0.body[0].x,snake0.body[0].y,'<');
            break;
        default:
            break;
    }
    if(food.x==snake0.body[0].x&&food.y==snake0.body[0].y){
        snake0.length += 1;
        mvaddch(tailx,taily,'O');
        genFood(1);
        mvprintw(LINES-1,0,"Score: %d, press 'p' to pause, 'q' to quit, 'r' to reload game, 'wasd' to change direction\n", SCORE);
    }
    else mvaddstr(tailx,taily," ");
    refresh();
    if(collision()){
        clear();
        mvaddstr(LINES/2,COLS/2-23,"Game Over! Press 'q' to quit, 'r' to restart game.\n");
        refresh();
    }
    gameSpeed = BASETIME/(1+5*(1-pow(2.73,-(1.0*SCORE)/15.0)));
    set_ticker(gameSpeed);
}

void snakeMoveSubFunc(){
    int temp1X = snake0.body[0].x,temp1Y = snake0.body[0].y;
    int temp2X,temp2Y;
    for(int i=1;i<snake0.length+1;++i){
        temp2X = snake0.body[i].x;
        temp2Y = snake0.body[i].y;
        snake0.body[i].x = temp1X;
        snake0.body[i].y = temp1Y;
        temp1X = temp2X;
        temp1Y = temp2Y;
    }
}


void blankFun(){

}




