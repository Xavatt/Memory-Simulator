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

/* Get the smallest LRU time from an array passed as parameter and the size of said parameter */
int getTLB(int tlb[][3], int size)
{
    int i,tlbn;
    int smallest=tlb[0][2]; /* Get the first LRU from the first entry in the TLB */
    for(i=0;i<size;i++)     /* The array is searched for lower LRU or LRU of zero */
    {
        if(tlb[i][2]==0)
        {
            tlbn = i;
            break;
        }
        if(tlb[i][2]<smallest)
        {
            smallest = tlb[i][2];
            tlbn = i;
        }
    }
    return tlbn; /* Return the index of the lowest LRU in the TLB */
}

/********************************************************
 *                  Main Entry Point                    *
 ********************************************************/

int main(int argc, char const *argv[])
{
    int tmen,ttlb,tfault;   /* Memory Access Time, TLB Access Time, Page Fault Time */
    FILE *fp;               /* Pointer to the file */
    int address;            /* Numeric value of the logical address */
    char operation;         /* Operation to be done (W or R) */
    char caddress[LOGADD]   /* Binary representation of the logical address */
    
}
