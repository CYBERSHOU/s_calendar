/*
 * =====================================================================================
 *
 *       Filename:  calendar.h
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
#include <stdio.h>
#include <stdlib.h>


#define STDIN 0
#define STDOUT 1
#define STDERR 2

#define MENU_MSG "Schedule Event (s)\nCheck Calendar (c)\nShow events in an order (o)\n(q to quit)\n > "
#define INV_INPUT "Invalid input!\n"


char * event_input_summary(void);

int * event_input_date(void);

int event_input_year(void);
int event_input_month(void);
int event_input_day(int * date);
int schedule(char *);
int check_calendar(char *);
int event_order(char *, int);
int empty_stdin_buffer(void);




//eof
