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
    int tmem,ttlb,tfault;   /* Memory Access Time, TLB Access Time, Page Fault Time */
    FILE *fp;               /* Pointer to the file */
    int address;            /* Numeric value of the logical address */
    char operation;         /* Operation to be done (W or R) */
    char caddress[LOGADD];   /* Binary representation of the logical address */

    /* Check if the number of parameters is correct */
    if(argc < NUMARAMS)
    {
        printf("Need a file with the process information\n");
        printf("Abnormal termination\n");
        return (EXIT_FAILURE);
    }
    else
    {
        /* Open the file and check that it exist */
        fp = fopen(argv[1],"r");    /* Open the file for read operation */
        if (!fp)                    /* There is an error */
        {
            printf("%s\n","ERROR 404 (FILE NOT FOUND)");
            return EXIT_FAILURE;
        }
        else
        {
            /* Read the times from the file */
            tmem = GetInt(fp);
            ttlb = GetInt(fp);
            tfault = GetInt(fp);

            if(tmem == EXIT_FAILURE || ttlb == EXIT_FAILURE || tfault == EXIT_FAILURE) /* We check to see if we read succesfully the three times */
            {
                printf("%s\n", "ERROR 404 (TIME NOT FOUND)"); /* In case of error we notify the user and terminate the program */
                return EXIT_FAILURE;
            }
            else
            {
                int pageSize,frameSize;                 /* Variables declared that will hold the page and frame size or spaces */
                pageSize = pow(2,LOGADD-OFFSET);        /* Page size is calculated */
                int pageTable[pageSize][2];             /* Array is declared with the age size and 2 int spaces, one for the frame and the second for validity */
                frameSize = pow(2,PHYADD-OFFSET);       /* Frame size is calculated */
                int frame[frameSize][3];                /* Array is declared with the frame size and 3 int spaces */
                                                        /* One is for the page entry, the second as a dirty bit, the third for the LRU time */

                #ifdef DEBUG
                /* In debug mode the number of entries is printed */                                        
                printf("%d Page Entries\n ", temp);
                printf("%d Frame Entries\n ", temp);
                printf("%d TLB Entries\n ", TLBSIZE);
                #endif

                int tlb[TLBSIZE][3];                             /* TLB is declared with three int spaces, one for page entry, second for the frame and third for the LRU time */
                int rem,n,i;                                     /* Rem is the remainder used to convert to binary, n stores numeric value of the address and i is used for 'fors' */
                int frameN,tlbn,pageEntry,smallest;              /* Frame number, TLB number, Page Entry and Smallest LRU time */
                double accessTime,sum;                           /* Access Time of the current memory request and the sum of all the access time of memories request */
                int counter = 1;                                 /* Counter serves as a time counter */
                int hits = 0;                                    /* Hits stores the number of TLB hits we have */
                int pageOut = 0, pageIn = 0;                     /* Page outs into disk and page ins from disk */
                int found;                                       /* Bool variable that is set to 1 if found */

                for(i=0;i<pageSize;i++) /* We set the page table to neutral values */
                {
                    pageTable[i][0]= 0;
                    pageTable[i][1]= 0;
                }
                
                for(i=0;i<frameSize;i++) /* We set the frame table to neutral values */
                {
                    frame[i][0]= 0;
                    frame[i][1]= 0;
                    frame[i][2]= 0;
                }

                for(i=0;i<TLBSIZE;i++) /* We set the TLB to neutral values */
                {
                    tlb[i][0]= 0;
                    tlb[i][1]= 0;
                    tlb[i][2]= 0;
                }
            }
        }
    }
}
