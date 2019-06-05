#include "snake.h"

int main(void){
    initscr();
    cbreak();
    noecho();
    clear();
    init();
    curs_set(0);
    signal(SIGALRM, snakeMove);
    set_ticker(BASETIME);
    int i = 0;
    while(1){
        ++i;
        int ch = getch();
        switch(ch){
            case 'q':
                endwin();
                return 0;
                break;
            case 'w':
                if(snake0.direction!=DOWN&&gameStat==RUN)
                    snake0.direction = UP;
                break;
            case 'd':
                if(snake0.direction!=LEFT&&gameStat==RUN)
                    snake0.direction = RIGHT;
                break;
            case 's':
                if(snake0.direction!=UP&&gameStat==RUN)
                    snake0.direction = DOWN;
                break;
            case 'a':
                if(snake0.direction!=RIGHT&&gameStat==RUN)
                    snake0.direction = LEFT;
                break;
            case 'p':
                if(gameStat==RUN){
                    signal(SIGALRM, blankFun);
                    gameStat=PAUSE;
                }
                else if(gameStat==PAUSE){
                    signal(SIGALRM, snakeMove);
                    gameStat = RUN;
                }
                break;
            case 'r':
                clear();
                init();
                break;
        }
    }
    endwin();
    return 0;
}