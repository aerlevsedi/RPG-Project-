#include <ncurses.h>
#include "menu_mode.h"
#include "game_mode.h"
#include "instruction_mode.h"
#define NL printw("\n")

void write_menu(int line)
{
    clear();
    start_color();
    init_pair( 7, COLOR_RED, COLOR_BLACK );

    if(line==-1 || line==0){
        attron( A_UNDERLINE | A_BOLD | COLOR_PAIR(7));
        printw("Start game\n");
        attroff( A_UNDERLINE | A_BOLD | COLOR_PAIR(7));
        printw("Instruction\n");
        printw("Difficulty level\n");
    }else if(line==1){
        printw("Start game\n");
        attron( A_UNDERLINE | A_BOLD | COLOR_PAIR(7));
        printw("Instruction\n");
        attroff( A_UNDERLINE | A_BOLD | COLOR_PAIR(7));
        printw("Difficulty level\n");
    }else{
        printw("Start game\n");
        printw("Instruction\n");
        attron( A_UNDERLINE | A_BOLD | COLOR_PAIR(7));
        printw("Difficulty level\n");
        attroff( A_UNDERLINE | A_BOLD | COLOR_PAIR(7));
    }
}

void open_menu()
{
    initscr();  /*start*/
    keypad(stdscr, TRUE);
    noecho();
    clear();
    write_menu(-1);

    char znak;
    int line_number=0;

    znak=getch();
    while(znak!=27){
        while(znak!=10){
            if(znak==2){
                line_number++;
                if(line_number>=3) line_number=0;
            }
            else if(znak==3){
                line_number--;
                if(line_number<=-1) line_number=2;
            }
            printw("line: %d\n", line_number);
            write_menu(line_number);
            znak=getch();
        }

        if(line_number==0){
            start_game(); /*tryb gry*/
            write_menu(-1);
            line_number=0;
        }
        else if(line_number==1){
            write_instruction();    /*instrukcja*/
            write_menu(-1);
            line_number=0;
        }
        /*else if(line_number==2)*/ /*poziom trudnosci*/

        znak=getch();
    }
    endwin();   /*end*/
}
