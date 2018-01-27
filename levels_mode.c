#include <ncurses.h>
#include "levels_mode.h"


void write_levels(int line)
{
    clear();
    start_color();
    init_pair( 7, COLOR_RED, COLOR_BLACK );

    if(line==-1 || line==0){
        printw("Choose difficulty level:\n");
        attron( A_UNDERLINE | A_BOLD | COLOR_PAIR(7));
        printw("EASY\n");
        attroff( A_UNDERLINE | A_BOLD | COLOR_PAIR(7));
        printw("MEDIUM\n");
        printw("HARD\n");
    }else if(line==1){
        printw("Choose difficulty level:\n");
        printw("EASY\n");
        attron( A_UNDERLINE | A_BOLD | COLOR_PAIR(7));
        printw("MEDIUM\n");
        attroff( A_UNDERLINE | A_BOLD | COLOR_PAIR(7));
        printw("HARD\n");
    }else{
        printw("Choose difficulty level:\n");
        printw("EASY\n");
        printw("MEDIUM\n");
        attron( A_UNDERLINE | A_BOLD | COLOR_PAIR(7));
        printw("HARD\n");
        attroff( A_UNDERLINE | A_BOLD | COLOR_PAIR(7));
    }
}

int level()
{
    //initscr();  /*start*/
    //keypad(stdscr, TRUE);
    //noecho();
    clear();
    write_levels(-1);

    char znak;
    int line_number=0, lvl=1;

    znak=getch();

    while(znak!=10){
        if(znak==2){
            line_number++;
            if(line_number>=3) line_number=0;
        }else if(znak==3){
            line_number--;
            if(line_number<=-1) line_number=2;
        }
        write_levels(line_number);
        znak=getch();
    }

    if(line_number==0)      lvl=1;
    else if(line_number==1) lvl=2;
    else if(line_number==2) lvl=3;

    printf("\nLVL=%d\n", lvl);
    return lvl;
    //endwin();   /*end*/
}
