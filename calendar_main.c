/*
 * =====================================================================================
 *
 *       Filename:  main.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  10/17/2019 09:25:24 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miguel Seridónio Almeida Fernandes
 *   Organization:
 *
 * =====================================================================================
 */
#include <stdlib.h>

#include "calendar.h"

int main(int argc, char *argv[]) {
    char yn;
    do {
        printf(MENU_MSG);
        scanf(" %c", &yn);
        empty_stdin_buffer();
        if(yn == 'n') return 0;


        int x;
        switch(yn) {
            case 'c':
                check_calendar("calendar_events.txt");
                break;
            case 's':
                schedule("calendar_events.txt");
                break;
            case 'o':
                printf("Ascending(1) or Descending(0) order? ");
                scanf(" %d", &x);
                if(x == 1 || x == 0)
                    event_order("calendar_events.txt", x);
                else
                    printf("\nInsert 1 or 0!\n\n");
                break;
        }
    }while (yn != 'n');

    /* event_order("calendar_events.txt", 0); */

    return 0;
}



//eof
