#include <ctype.h>      /* Used for the isdigit() function */
#include <stdlib.h>     /* Used for malloc definition */
#include <stdio.h>      /* Used for fprintf */
#include <math.h>

/********************************************************
 *              Global Constant Values                  *
 ********************************************************/
#define LOGADD 16       /* Constant used to define the logial address space */
#define PHYADD 13       /* Constant used to define the physical address space */
#define OFFSET 9        /* Constant used to define the offset used */
#define TLBSIZE 8       /* Constant for the TLB size */
#define NUMARAMS 2      /* Constant used to define the number of parameters we must receive */

/* Used to get a number from a file passed as a parameter */
int GetInt(FILE *fp)
{
    int c,i; /* Character read and integer representation of it */
    int sign = 1;
    do
    {
        c = getc(fp); /* Get next character */
        if(c == '#') /* Help to skip the comment's */
        {
           do
           {
               c = getc(fp);
           } while(c != '\n');
           if(c == '-')
           {
               sign = -1;
           }
        }
    }while (!isdigit(c) && !feof(fp));

    if(feof(fp))
    {
        return (EXIT_FAILURE);
    }
    else
    {
        /* Found 1st digit, begin coversion until a non-digit is found */
        i = 0;
        while(isdigit(c) && !feof(fp))
        {
            i = (i*10) + (c - '0');
            c = getc(fp);
        }
        return (i*sign);
    }
}

