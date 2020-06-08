#include <stdio.h>
#include <stdlib.h>
#include "brainfuck.h"

    //TODO:
    // Allocate 30 000 bytes
    //      malloc                      DONE
    //      ensure all bytes are clean  DONE
    // Load brainfuck program
    //      load file                   DONE
    //      store file in string        DONE
    // Execute program                  DONE
    // Clean up
    //      allocated bfspace           DONE

    //Current bugs: stability starts fucking up after some time
    //Possibilities:
    //      instructions deteriorate during runtime
    //          no: no sign of change over time
    //      parasites in memory
    //          no: these would show up from the start
    //      unintended behaviour from the base functions
    //          +: no evident flaw from testing
    //          -:
    //          >:
    //          <:
    //          [: nesting issues: fixed via kludge power!
    //          ]: idem
    //      stack over/underflow:
    //          Similar: test on the fibonacci system shows that pointer can go in the negatives.
    //          Implementing looping as workaround


    //just some utility stuff
/*
typedef struct
{
    size_t dSize;
    unsigned int lLength;
    void* data;
} blist;

void blInit(blist* nbl, size_t dSize, unsigned int lLength)
{
    free(nbl->data);
    void* data = malloc(dSize*lLength);
    if (!data)
        abort();
    nbl->dSize = dSize;
    nbl->lLength = lLength;
    nbl->data = data;
}

void lTbl(const void*l, blist* cbl)
{
    for (int i = 0; i < cbl->dSize*cbl->lLength; i++)
        *((char*)cbl->data+i) = *((char*)l+i);
    return;
}

void blTbl(const blist* o, blist* d)
{
    if (o->dSize*o->lLength != d->dSize*d->lLength)
    {
        d->dSize = o->dSize;
        d->lLength = o->lLength;
        realloc(d->data, o->dSize*o->lLength);
    }
    for (int i = 0; i < o->dSize*o->lLength; i++)
        *((char*)d->data+i) = *((char*)o->data+i);
    return;
}

void blCleanup(blist * cbl)
{
    free(cbl->data);
    return;
}

bool blTest()
{
    blist a = {0,0,NULL};
    blInit(&a,sizeof(char),20);
    char r[20] = "abcdefghijlmnop\0";
    lTbl(r,&a);

    for (int i = 0; i < 10; i++)
        if (r[i]!=((char*)a.data)[i]) printf("loose\n");
    printf("length: %i\n", (int)a.lLength);
    printf("str: %s\n", (char*)a.data);

    blCleanup(&a);
}*/


/*void defExit(blist* exit)
{
    blInit(exit,4,4);
    exit->data[0] = "exit";
    exit->data[1] = "Exit";
    exit->data[2] = "quit";
    exit->data[3] = "Quit";
    return;
}*/


int main()
{
    //blist exit = {0,0,NULL};
    //defExit(&exit);

    printf("Allocating space...\n");
    byte* BFMem = allocateBFMem();

    printf("Space allocated.\n");

    printf("Setting all data in allocated space to 0...\n");

    memTo0(BFMem);

    if (test_m(BFMem))
        printf("Allocation succesful.\n");
    else
        printf("Allocation unsuccesful.\n");

    char* filename[100];

    char* BFProg = NULL;

    while (BFProg == NULL)
    {
        printf("Please enter file name\n>");
        scanf("%s",filename);

        /*if (belongsIn(filename, exit)))
        {
            printf("\n\nCleaning up...\n\n");
            cleanUpBFProg(BFProg);
            cleanUpBFMem(BFMem);
            return 0;
        }*/

        BFProg = loadBFProg(filename);
    }
    //printf("%s\n", BFProg);

    printf("Running program:\n\n");
    runBF(BFMem,BFProg);

    printf("\n\nCleaning up...\n\n");
    cleanUpBFProg(BFProg);
    cleanUpBFMem(BFMem);
    printf("Done!\n");
    getch();
    return;
}

/*bool belongsIn(const char* input, const *blist compList)
{
    int t = 0;
    for (int i = 0; i < compList->lLength; i++)
    {
        for (char* j = (char*)((char**)(compList->data)[i]); *j = '\0'; j++)
        {
            if (*j != *(input+(j-((char**)(compList->data)[i]))))
            {
                t++;
                break;
            }

        }
    }
}*/
