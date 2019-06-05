#include "flappy.h"


int main(void){
    initscr();
    cbreak();
    noecho();
    clear();
    refresh();
    curs_set(0);
    signal(SIGALRM, fly);
    set_ticker(BASETIME);
    srand(time(0));

    win0 = newwin(MAINWINDOWLINES,MAINWINDOWCOLS,2,2);
    win1 = newwin(INFORWINDOWLINES,INFORWINDOWCOLS,2,MAINWINDOWCOLS);

    init();
    initWin1();
    GAMESTAT = RUN;



    while(1){
        int input = getchar();
        switch(input){
            case 'q': goto endProgram;
            case ' ':{
                if(GAMESTAT!=PAUSE){
                    plane.v = -1;
                    vInterval = 0;
                }
                break;
            }
            case 'p':{
                if(GAMESTAT == RUN){
                    signal(SIGALRM,pauseGame);
                    GAMESTAT = PAUSE;
                }
                else if(GAMESTAT == PAUSE){
                    signal(SIGALRM,fly);
                    GAMESTAT = RUN;
                }
                break;
            }
            case 'r':{    
                init();
                initWin1();
                GAMESTAT = RUN;
                signal(SIGALRM,fly);
                break;
            }
            default: break;
        }
    }
endProgram:
    delwin(win0);
    delwin(win1);
    endwin();
    return 0;


}