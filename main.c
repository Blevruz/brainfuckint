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


int main(int argc, char* argv[])
{
    //printf("Allocating space...\n");
    byte* BFMem = allocateBFMem();

    //printf("Space allocated.\n");

    //printf("Setting all data in allocated space to 0...\n");

    memTo0(BFMem);

    //if (test_m(BFMem))
        //printf("Allocation succesful.\n");
    //else
        //printf("Allocation unsuccesful.\n");

    char filename[100];

    char* BFProg = NULL;

    if (argc > 1) {
	    BFProg = loadBFProg(argv[1]);
    }
    while (BFProg == NULL)
    {
        printf("Please enter file name\n>");
        scanf("%s",filename);

        BFProg = loadBFProg(filename);
    }

    //printf("Running program:\n");
    runBF(BFMem,BFProg);

    //printf("Cleaning up...\n");
    cleanUpBFProg(BFProg);
    cleanUpBFMem(BFMem);
    //printf("Done!\n");
    return 0;
}

