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
    if(argc != 2) {
        printf("Please provide a second argument with the file's name!\n");
        return 0;
    }

    FILE * f = fopen(argv[1], "r");
    if(f == NULL) {
        printf("File doesn't exist.\nCreating file...\n\n");
        f = fopen(argv[1], "w");
    }
    else fclose(f);

    char yn;
    do {
        printf(MENU_MSG);
        scanf(" %c", &yn);
        empty_stdin_buffer();
        if(yn == 'q') break;

        int x;
        switch(yn) {
            case 'c':
                //argv[1] file that keeps calendar events
                check_calendar(argv[1]);
                break;
            case 's':
                schedule(argv[1]);
                break;
            case 'o':
                printf("Ascending(1) or Descending(0) order? ");
                scanf(" %d", &x);
                if(x == 1 || x == 0) {
                    if(event_order(argv[1], x)) printf("File is empty...\n");
                }
                else
                    printf("\nInsert 1 or 0!\n\n");
                break;
            case 'w':
                printf("Wiping old events...\n");
                if(wipe_old_events(argv[1])) {
                    printf("No old events found.\n");
                    break;
                }
                printf("Old events wiped.\n");
                break;
            default:
                printf("\n# Please insert a valid option #\n\n");
                break;
        }
    }while (yn != 'q');

    return 0;
}



//eof
