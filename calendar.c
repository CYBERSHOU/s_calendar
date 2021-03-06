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
    static char summary[33];
    char y_n;
    char buffer;
    do{
        printf("Insert event summary(chars-32): ");
        summary[0] = '\0';
        int i = 0;
        for(i = 0; i < 32; i++) {
            buffer = getchar();
            if(buffer == '\n')
                break;
            summary[i] = buffer;
        }
        summary[32] = '\0';
        printf("SUMMARY: %s\nContinue? (Y/n) ", summary);
        if (buffer != '\n') empty_stdin_buffer();
        y_n = getchar();
        if (y_n != '\n') empty_stdin_buffer();
    }while(y_n != 'y' && y_n != '\n');
    return summary;
}


int event_order(char * file_str, int sort_order) {
    //read_file_chars - reading number of chars(i) and lines.
    int * arr = read_file_chars(file_str);
    int i = arr[0];
    int lines = arr[1];
    if (i == 0) return 1;

    char * buffer = (char*)malloc(i * sizeof(char));
    if (buffer == NULL) {
        perror("Unable to allocate space!");
        free(buffer);
        return 1;
    }
    int buffer_size = i * sizeof(char);

    //setting up buffer content and position of the start of the lines
    int l_start[lines];
    l_start[0] = 0;
    int l = 1;
    FILE * f = fopen(file_str, "r");
    for(i = 0; i < buffer_size; i++) {
        buffer[i] = getc(f);
        if(buffer[i] == '\n' && l < lines) {
            l_start[l] = i+1;
            l += 1;
        }
    }
    fclose(f);

    char * p_b = &buffer[0];
    //setting up the order, starting by finding the first element and
    //going down from there
    if(sort_order) {
        for(i = 0; i < lines; i++) {
            for(int j = i+1; j < lines; j++) {
                //compare char by char in ascending order by date
                for(int c = 0; c < 10; c++) {
                    //l_start[i] is the index position of the first char
                    //in one of the lines of buffer
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

    date[0] = event_input_year();

    date[1] = event_input_month();

    date[2] = event_input_day(date);

    return date;
}


int event_input_year() {
    int year[4];
    int i = -1;
    int buff;
    while(i == -1) {
        printf("Insert year(yyyy): ");
        for(i = 0; i < 4; i++) {
            buff = getchar();
            if(buff < 48 || buff > 58 || buff == '\n'){
                printf(INV_INPUT);
                i = -1;
                break;
            }
            buff -= 48;
            year[i] = buff;
        }
        if(empty_stdin_buffer()) {
             i = -1;
             printf("Please make sure to insert only 4 digits!\n");
        }
    }
    return (year[0]*(1000)) + (year[1]*(100)) + (year[2]*(10)) + year[3];
}


int event_input_month() {
    int month[2];
    int i = -1;
    int buff;
    while(i == -1) {
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
        if(empty_stdin_buffer()) {
            i = -1;
            printf("Please make sure to insert only 2 digits!\n");
            continue;
        }
        if(buff > 12 || buff < 1) {
            i = -1;
            printf(INV_INPUT);
            continue;
        }
    }
    return buff;
}


int event_input_day(int * date) {
    int days[2];
    int i = -1;
    int buff;
    while(1) {
        printf("Insert day(dd): ");
        for(i = 0; i < 2; i++) {
            buff = getchar();
            //dec ascii
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
        if (empty_stdin_buffer()) {
            printf("Please insert only 2 digits!\n");
            continue;
        }
        if (buff > 31 || buff <= 0) {
            printf("Do you live on planet earth!?\n");
            continue;
        }
        if ( ((date[1] == 2) && (buff == 29) && (((date[0] % 4) != 0) && ((date[0] % 400) != 0))) || (buff == 30 && date[1] == 2) ) {
            printf("This isn't a leap year!\n");
            continue;
        }
        if (buff > 30 && (( (date[1] % 2) == 0 && date[1] < 7) || ( (date[1] % 2 != 0) && date[1] > 7 ) )) {
            printf("This month only has a maximum of 30 days!\n");
            continue;
        }
        break;
    }
    return buff;
}


int * read_file_chars(char * file_str) {

    FILE * f;
    f = fopen(file_str, "r");
    char c = ' ';
    int i = 0;
    int lines = 0;
    while(1) {
        c = getc(f);
        if(c == EOF) {
            int arr [2] = {i, lines};
            int * p = arr;
            return p;
        }
        i++;
        if(c == '\n') lines += 1;
    }
}


int schedule(char * file_str) {
    char yn;

    do {
        printf("Do you want to schedule an event?(Y/n) ");
        yn = getchar();
        if(yn != '\n') empty_stdin_buffer();

        if (yn != 'y' || yn != '\n') return 1;

        printf("\n");
    } while(yn != 'y');

    char *s;
    int *p;
    p = event_input_date();
    s = event_input_summary();
    printf("\n");

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

    FILE * fo;
    fo = fopen(file_str, "r");
    char c;
    while(c != EOF) {
        c = getc(fo);
        if( c != EOF)
            printf("%c", c);
    }
    fclose(fo);
    printf("\n");
    return 0;
}


int wipe_old_events(char * file_str) {
    FILE * f = fopen(file_str, "wr");
    //delete old events that have ocurred relative to current date
    fclose(f);
    return 0;
}


int empty_stdin_buffer() {
    char c = getchar();
    if( c == '\n') return 0;
    while(c != '\n'){
        c = getchar();
    }

    return 1;
}



//eof
