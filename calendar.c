/*
 * =====================================================================================
 *
 *       Filename:  calendar.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  10/17/2019 09:22:07 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Miguel Seridónio Almeida Fernandes
 *   Organization:
 *
 * =====================================================================================
 */
#include "calendar.h"


char * event_input_summary() {
    static char summary[32];

    printf("Insert event summary(chars-32): ");

    int i;
    for(i = 0; i < 32; i++) {
        char buffer = getchar();
        if(buffer == '\n')
            break;
        summary[i] = buffer;
    }

    return summary;
}

int event_order(char * file_str, int sort_order) {

    FILE * f;
    f = fopen(file_str, "r");
    char c = ' ';
    int i = 0;
    int lines = 0;
    while(1) {
        c = getc(f);
        if(c == EOF)
            break;
        i++;
        if(c == '\n') lines += 1;
    }

    char * buffer = (char*)malloc(i * sizeof(char));
    if (buffer == NULL) {
        printf("Not allocated!\n");
        free(buffer);
        return 1;
    }
    int buffer_size = i * sizeof(char);

    //setting up buffer content and position of the start of the lines
    int l_start[lines];
    l_start[0] = 0;
    int l = 1;
    rewind(f);
    for(i = 0; i < buffer_size; i++) {
        buffer[i] = getc(f);
        if(buffer[i] == '\n' && l < lines) {
            l_start[l] = i+1;
            l += 1;
        }
    }
    fclose(f);

    char * p_b = &buffer[0];
    //setting up the order, starting by finding the first element and going down from there
    if(sort_order) {
        for(i = 0; i < lines; i++) {
            for(int j = i+1; j < lines; j++) {
                //compare char by char in ascending order by date
                for(int c = 0; c < 10; c++) {
                    //l_start[i] is the index position of the first char in one of the lines of buffer
                    if(*(p_b+l_start[i]+c) < *(p_b+l_start[j]+c)) break;
                    if(*(p_b+l_start[i]+c) > *(p_b+l_start[j]+c)) {
                        int buf = l_start[i];
                        l_start[i] = l_start[j];
                        l_start[j] = buf;
                        break;
                    }
                }
            }
        }
    } else {
        for(i = 0; i < lines; i++) {
            for(int j = i+1; j < lines; j++) {
                //compare char by char in descending order by date
                for(int c = 0; c < 10; c++) {
                    if(*(p_b+l_start[i]+c) > *(p_b+l_start[j]+c)) break;
                    if(*(p_b+l_start[i]+c) < *(p_b+l_start[j]+c)) {
                        int buf = l_start[i];
                        l_start[i] = l_start[j];
                        l_start[j] = buf;
                        break;
                    }
                }
            }
        }
    }

    printf("\n");
    for(i = 0; i < lines; i++) {
        int c = 0;
        while(*(p_b+l_start[i]+c) != '\n') {
            printf("%c", *(p_b+l_start[i]+c));
            c++;
        }
        printf("\n");
    }
    printf("\n");
    free(buffer);
    return 0;
}

int * event_input_date() {
    static int date[3];
    int buff;
    int i = -1;

    int year[4];
    /* scanf(" %d%d%d", &date[0], &date[1], &date[2]); */
    while(i == -1) {
        printf("Insert year(yyyy): ");
        for(i = 0; i < 4; i++) {
            /* printf("FOR%d", i); */
            buff = getchar();
            /* printf("getchar %d \n", buff); */
            if(buff < 48 || buff > 58 || buff == '\n'){
                printf(INV_INPUT);
                i = -1;
                break;
            }
            buff -= 48;
            /* printf("buff %d\n", buff); */
            year[i] = buff;
            /* printf("%d%d%d%d", year[0], year[1], year[2], year[3]); */
        }
        empty_stdin_buffer();
    }
    date[0] = (year[0]*(1000)) + (year[1]*(100)) + (year[2]*(10)) + year[3];
    /* printf("%d", date[0]); */

    int month[2];
    while(1) {
        printf("Insert month(mm): ");
        for(i = 0; i < 2; i++) {
            buff = getchar();
            if(buff == 10) {
                break;
            }
            if(buff < 48 || buff > 58) {
                printf(INV_INPUT);
                break;
            }
            else {
                month[i] = buff - 48;
            }
        }
        if(i == 1 && buff == 10) {
            buff = month[0];
        }
        else {
            buff = month[0]*(10) + month[1];
        }
        if(buff > 12 || buff < 1) {
            printf(INV_INPUT);
        }
        else {
            if(i == 2) empty_stdin_buffer();
            break;
        }
        empty_stdin_buffer();
    }
    date[1] = buff;

    int days[2];
    while(1) {
        printf("Insert day(dd): ");
        for(i = 0; i < 2; i++) {
            buff = getchar();
            if(buff == 10) {
                break;
            }
            if(buff < 48 || buff > 58) {
                printf(INV_INPUT);
                break;
            }
            else {
                days[i] = buff - 48;
            }
        }
        if (i == 1 && buff == 10) {
            buff = days[0];
        }
        else {
            buff = days[0]*(10) + days[1];
        }
        if (buff > 31 || buff <= 0) {
            printf("Do you live on planet earth!?\n");
            empty_stdin_buffer();
            continue;
        }
        if ( ((date[1] == 2) && (buff == 29) && (((date[0] % 4) != 0) && ((date[0] % 400) != 0))) || (buff == 30 && date[1] == 2) ) {
            printf("This isn't a leap year!\n");
            empty_stdin_buffer();
            continue;
        }
        if (buff > 30 && (( (date[1] % 2) == 0 && date[1] < 7) || ( (date[1] % 2 != 0) && date[1] > 7 ) )) {
            printf("This month only has a maximum of 30 days!\n");
            empty_stdin_buffer();
            continue;
        }
        else {
            if( i == 2) empty_stdin_buffer();
            break;
        }
    }
    date[2] = buff;

    return date;
}

int schedule(char * file_str) {
    char yn;

    do {
        printf("Do you want to schedule an event?(y/n) ");
        yn = getchar();
        empty_stdin_buffer();

        if (yn == 'n') return 1;

        printf("\n");
    } while(yn != 'y');

    char *s;
    int *p;
    p = event_input_date();
    s = event_input_summary();


    FILE *fi;
    fi = fopen(file_str, "a");

    int i;
    for(i = 0; i < 3; i++) {
        if (i == 0) {
            fprintf(fi, "%d", *(p + i));
            continue;
        }
        if(*(p + i) < 10) {
            fprintf(fi, "/0%d", *(p + i));
        }
        else {
            fprintf(fi, "/%d", *(p + i) );
        }
    }

    //':' separating date from summary
    fprintf(fi, ": ");
    fprintf(fi, "%s", s);
    fprintf(fi, "\n");
    fclose(fi);

    return 0;
}

int check_calendar(char * file_str) {
    char yn;
    do {
        printf("Do you want to check your calendar?(y/n) ");
        scanf(" %c", &yn);
        empty_stdin_buffer();
        if(yn == 'n')
            return 1;

        printf("\n");
    } while(yn != 'y');

    char date[11];
    FILE * fo;
    fo = fopen(file_str, "r");
    fgets(date, 11, fo);
    printf("%s\n", date);

    return 0;
}

void empty_stdin_buffer() {
    char c;
    while(c != '\n'){
        c = getchar();
    }

    return;
}

//eof
