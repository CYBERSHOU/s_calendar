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
#ifndef CALENDAR_H_
#define CALENDAR_H_


#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2

#define MENU_MSG "Schedule Event (s)\nCheck Calendar(c)\nShow events in an order (o)\nWipe old/past events (w)\n(q to quit)\n > "
#define INV_INPUT "Invalid input!\n"


char * event_input_summary(void);

int * event_input_date(void);
int * read_file_chars(char *);

int event_input_year(void);
int event_input_month(void);
int event_input_day(int *);
int schedule(char *);
int check_calendar(char *);
int wipe_old_events(char *);
int event_order(char *, int);
int empty_stdin_buffer(void);



#endif /* ifndef CALENDAR_H_ */
