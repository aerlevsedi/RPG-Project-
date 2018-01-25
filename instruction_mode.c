#include <ncurses.h>
#include "menu_mode.h"
#include "instruction_mode.h"

void write_instruction()
{
    clear();
    printw("HERE WILL INSTRUCTION APPEAR\n");
    printw("Press Escape to leave.");
    char znak;
    do znak=getch();
    while(znak!=27);
}
