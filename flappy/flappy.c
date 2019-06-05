#include "flappy.h"




void init(){
    /*initialize plane*/
    vInterval = 0;
    SCORE = 0;
    plane.lines = PLANELINES;
    plane.cols = PLANECOLS;
    plane.posLine = MAINWINDOWLINES/2-plane.lines/2;
    plane.posCol = MAINWINDOWCOLS/5-plane.cols;
    plane.v = 1;
    for(int i = 0;i<6;++i){
        plane.body[i].x = plane.posLine+2;
        plane.body[i].y = plane.posCol+6-i;
    }
    plane.body[6].x = plane.posLine+1; plane.body[6].y = plane.posCol;
    plane.body[7].x = plane.posLine+3; plane.body[7].y = plane.posCol;
    plane.body[8].x = plane.posLine+1; plane.body[8].y = plane.posCol+4;
    plane.body[9].x = plane.posLine+3; plane.body[9].y = plane.posCol+4;
    plane.body[10].x = plane.posLine; plane.body[10].y = plane.posCol+3;
    plane.body[11].x = plane.posLine+4; plane.body[11].y = plane.posCol+3;
    paintPlane(win0);

    /*initialize wall*/
    for(int i = 0;i<WALLNUM+1;++i){
        wall[i].pos = i*WALLCELLCOLS+MAINWINDOWCOLS;
        wall[i].freeHigh = 11+rand()%8;
        int end1Ratio = 1+rand()%7;
        int end2Ratio = 10-end1Ratio;
        wall[i].end1 = (1.0*end1Ratio)/10.0*(MAINWINDOWLINES-wall[i].freeHigh);
        wall[i].end2 = wall[i].freeHigh+wall[i].end1;
    }
    paintWall(win0);
}

void initWin1(){
    wclear(win1);
    for(int i = 0;i<INFORWINDOWCOLS;++i){
        mvwaddch(win1,0,i,'#');
        mvwaddch(win1,INFORWINDOWLINES-1,i,'#');
    }
    for(int i = 0;i<INFORWINDOWLINES;++i){
        mvwaddch(win1,i,0,'#');
        mvwaddch(win1,i,INFORWINDOWCOLS-1,'#');
    }
    mvwaddstr(win1,3,2,"   FLAPPY PLANE");
    mvwaddstr(win1,5,3,"Instruction:");
    mvwaddstr(win1,6,3,"Key press");
    mvwaddstr(win1,7,4,"'q': quit");
    mvwaddstr(win1,8,4,"'p': pause/resume");
    mvwaddstr(win1,9,4,"'r': restart");
    mvwaddstr(win1,10,4,"'q': quit");
    mvwaddstr(win1,11,4,"space: move up");
    mvwprintw(win1,13,4,"Score: %d",SCORE);
    mvwaddstr(win1,INFORWINDOWLINES-4,2,"    version 1.0");
    mvwaddstr(win1,INFORWINDOWLINES-3,2,"      Product by ");
    mvwaddstr(win1,INFORWINDOWLINES-2,2,"        Minchao Zhu");

    wrefresh(win1);
}

void paintPlane(){
    for(int i = 0;i<12;++i){
        mvwaddch(win0,plane.body[i].x,plane.body[i].y,'*');
    }
    wrefresh(win0);
}

void paintWall(){
    for(int i = 0;i<WALLNUM+1;++i){
        for(int j = 0;j<WALLWIDTH;++j){
            if(wall[i].pos+j<MAINWINDOWCOLS){
                for(int k=0;k<MAINWINDOWLINES;++k){
                    if(k<=wall[i].end1||k>=wall[i].end2)
                        mvwaddch(win0,k,wall[i].pos+j,'*');
                }
            }
        }
    }
    wrefresh(win0);
}

void paintEdge(){
    for(int i = 0;i<MAINWINDOWCOLS;++i){
        mvwaddch(win0,0,i,'#');
        mvwaddch(win0,MAINWINDOWLINES-1,i,'#');
    }
    for(int i = 0;i<MAINWINDOWLINES;++i){
        mvwaddch(win0,i,0,'#');
        mvwaddch(win0,i,MAINWINDOWCOLS-1,'#');
    }
    wrefresh(win0);
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

void fly(){
    for(int i = 0;i<12;++i){
        plane.body[i].x += plane.v;
    }
    plane.posLine += plane.v;
    if(++vInterval>=vFull){
        vInterval = 0;
        plane.v+=1;
    }
    if(wall[0].pos>(-WALLWIDTH)){
        for(int i = 0;i<WALLNUM+1;++i){   
                --wall[i].pos;
        }
    }
    else{
        for(int i = 0;i<WALLNUM;++i){
            wall[i].pos = wall[i+1].pos-1;
            wall[i].freeHigh = wall[i+1].freeHigh;
            wall[i].end1 = wall[i+1].end1;
            wall[i].end2 = wall[i+1].end2;
        }
        wall[WALLNUM].pos = wall[WALLNUM-1].pos+WALLCELLCOLS-1;
        wall[WALLNUM].freeHigh = 11+rand()%8;
        int end1Ratio = 1+rand()%7;
        int end2Ratio = 10-end1Ratio;
        wall[WALLNUM].end1 = (1.0*end1Ratio)/10.0*(MAINWINDOWLINES-wall[WALLNUM].freeHigh);
        wall[WALLNUM].end2 = 1+wall[WALLNUM].freeHigh+wall[WALLNUM].end1;
    }
    updateWin0();
    if(collision()){
        signal(SIGALRM,pauseGame);
        wclear(win0);
        mvwprintw(win1,16,3,"    GAME OVER!");
        wrefresh(win1);
        //wrefresh(win0);
    }

}


void updateWin0(){
    wclear(win0);
    paintPlane();
    paintWall();
    paintEdge();
}

int collision(){
    int i;
    if(plane.posLine<=0||(plane.posLine+PLANELINES-1)>=(MAINWINDOWLINES-1)) return 1;
    for(i=0;i<WALLNUM+1;++i){
        if(wall[i].pos+WALLWIDTH==plane.posCol){
            SCORE+=1;
            mvwprintw(win1,13,4,"Score: %d",SCORE);
            wrefresh(win1);
        }
        if((wall[i].pos>=plane.posCol-(WALLWIDTH-1))&&(wall[i].pos<=plane.posCol+PLANECOLS-1)){
            break;
        }
    }
    if(i==WALLNUM+1)return 0;
    else{
        if(wall[i].end1>=plane.posLine||wall[i].end2<=plane.posLine+PLANELINES-1){  
            //mvwprintw(win0,MAINWINDOWLINES-1,0,"i = %d",i);
            wrefresh(win0);
            return 1;
        }
        else return 0;
    }
}

void pauseGame(){}