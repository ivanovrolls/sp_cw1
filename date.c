#ifndef _DATE_H_INCLUDED_
#define _DATE_H_INCLUDED_
#include "stdlib.h"
#include <stdio.h>
/*process the arguments                                   just copied this for reference
create a TLD list
if no file args are provided
 process stdin
else for each file in the argument list
 open the file
 process the file
 close the file
create an iterator
while there is another entry in the iterator
 print out the percentage associated with that TLD
destroy the iterator
destroy the Date structures
destroy the TLDList */

//Structure definition for Date in date.h
typedef struct date {
    int day;
    int month;
    int year;
} Date;

// date_create creates Date structure from `datestr` with 'datestr' at tend of form
// will return pointer to Date structure if successful, or NULL */
Date *date_create(char *datestr) {
    Date *date_new = malloc(sizeof(Date));
    if (date_new == NULL) { //check memory has been allocated correctly
        return NULL; //fail
    }
    if (sscanf(datestr, "%d/%d/%d", &(date_new->day), &(date_new->month), &(date_new->year)) != 3) {
        free(date_new);
        return NULL; //error in datestr
    }
    return date_new;
}

Date *date_duplicate(Date *d) { //date_duplicate generates a duplicate and returns pointer on success
    Date *date_new = malloc(sizeof(Date));
    if (date_new == NULL) { //ensure memory was allocated properly
        return NULL; //fail
    }
    
    //assign day/month/year member data of d to day/month/year member of date_new
    date_new->day = d->day;
    date_new->month = d->month;
    date_new->year = d->year;
    
    return date_new;
}

/*
* date_compare compares two dates, returning <0, 0, >0 if
* date1<date2, date1==date2, date1>date2, respectively
*/
int date_compare(Date *date1, Date *date2) {
    if (date1->year != date2->year) {
        return date1->year - date2->year;
    }
    if (date1->month != date2->month) {
        return date1->month - date2->month;
    }
    return date1->day - date2->day;
}



void date_destroy(Date *d) { //date_destroy frees storage 
    free(d);
}

#endif /* _DATE_H_INCLUDED_ */
