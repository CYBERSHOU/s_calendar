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

    char * buffer = malloc(i * sizeof(char));
    if (buffer == NULL) {
        printf("Not allocated!\n");
        free(buffer);
        return 1;
    }
    int buffer_size = i * sizeof(char);

    /* char buffer [i * sizeof(char)]; */
    /* int buffer_size = i * sizeof(char); */
    rewind(f);
    for(i = 0; i < buffer_size; i++) {
        buffer[i] = getc(f);
    }
    fclose(f);

    printf("\n%d\n", i);
    //b and b2 contain the 'dynamic' size of buf and buf2 respectively
    //b_full and b2_full indicate if bufs have reached their \n and therefore are full
    //rev_buf_order to change logic order without having to exchange buf and buf2 content
    for(int j = 0; j < lines; j++) {
        char buf [264], buf2 [264];
        int b = 0, b2 = 0;
        int b_full = 0, b2_full = 0;
        int at_line = 0;
        int rev_buf_order = 0;
        for(int i = 0; i < buffer_size; i++) {
            if(buffer[i] == '\0') break;
            if(b_full == 0) {
                buf[b] = buffer[i];
                if(buf[b] != '\n') {
                    b++;
                }
                else {
                    b_full = 1;
                    b++;
                }
            }
            else if(b2_full == 0) {
                buf2[b2] = buffer[i];
                if(buf2[b] != '\n') {
                    b2++;
                }
                else {
                    b2_full = 1;
                    b2++;
                }
            }
            /* if((b2_full == 1) && (b_full == 1)) { */
            /*     printf("%s\n%s\n", buf, buf2); */
            /*     int order = -1; */
            /*     for(int k = 0; k < 10; k++) { */
            /*         if(buf[k] > buf2[k]) { */
            /*             if(rev_buf_order) */
            /*                 order = 0; */
            /*             else */
            /*                 order = 1; */
            /*             break; */
            /*         } */
            /*         if(buf[k] < buf2[k]) { */
            /*             if(rev_buf_order) */
            /*                 order = 1; */
            /*             else */
            /*                 order = 0; */
            /*             break; */
            /*         } */
            /*     } */
            /*     if(sort_order == order) { */
            /*         for(int k = 0; k < b2; k++) { */
            /*             buffer[(i + k + 1) - (b2 + b)] = buf2[k]; */
            /*         } */
            /*         for(int k = 0; k < b; k++) { */
            /*             buffer[(i + k +1) - b] = buf[k]; */
            /*         } */
            /*         if(rev_buf_order) { */
            /*             b_full = 0; */
            /*             b = 0; */
            /*             rev_buf_order = 0; */
            /*         } */
            /*         else { */
            /*             b2_full = 0; */
            /*             b2 = 0; */
            /*             rev_buf_order = 1; */
            /*         } */
            /*     } */
            /*     else { */
            /*         if(rev_buf_order) { */
            /*             b2_full = 0; */
            /*             b2 = 0; */
            /*             rev_buf_order = 0; */
            /*         } */
            /*         else { */
            /*             b_full = 0; */
            /*             b = 0; */
            /*             rev_buf_order = 1; */
            /*         } */
            /*     } */
            /* } */
        }
    }

    printf("%s\n", buffer);
    /* f = fopen(file_str, "w"); */

    /* for(i = 0; i < buffer_size; i++) { */
    /*     fprintf(f, "%c", buffer[i]); */
    /* } */
    /* fclose(f); */
    /* printf("\nThe buffer has a sizeof : %d \n", buffer_size ); */
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
    //there is no such thing as ^ to make powers of a number
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
        if (date[1] == 2 && buff == 29 && (((date[0] % 4) != 0) && ((date[0] % 400) != 0)) || (buff == 30 && date[1] == 2) ) {
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
    printf("%s\n", &date);

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
