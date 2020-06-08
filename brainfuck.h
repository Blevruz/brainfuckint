#ifndef BRAINFUCK
#define BRAINFUCK

#include <stdbool.h>

typedef unsigned char byte;



// Allocating Memory

byte * allocateBFMem();

inline void
cleanUpBFMem(byte* BFMem)
{
    free(BFMem);
    return;
};

// Ensuring all memory is set to 0

void memTo0(byte* BFMem);

bool test_m(const byte* BFMem);

// Loading the program

char * loadBFProg(const char * filename);

void cleanUpBFProg(char * BFProg);

// Running the program

bool runBF(byte * BFMem, const char * BFProg);

static void i_nestCrawl(char * BFProg, char ** proggers, char start, char stop); //because recursivity is objectively the best thing to ever happen

#endif // BRAINFUCK
