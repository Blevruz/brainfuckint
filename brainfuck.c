#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "brainfuck.h"

//typedef unsigned char byte;

const int bfms = 30000;                                 // How much memory we allocate.

const bool debug = 0;                                   //help me im scared

byte *
allocateBFMem()
{
    byte * BFMem = (byte*)malloc(bfms*sizeof(byte));    // Using malloc
    if (BFMem == NULL)
        abort();

    return BFMem;
}

void
memTo0(byte* BFMem)
{
    for (long int i = 0; i < bfms; i++)
    {
        BFMem[i] = 0;
        //printf("%i ",i);
    }

    //printf("\n");
    return;
}

bool
test_m(const byte* BFMem)
{
    for (long int i = 0; i < bfms; i++)
    {
        //printf("%i %i;",i,BFMem[i]);
        if (BFMem[i])
            return false;
    }

    return true;
}

char *
loadBFProg(const char * filename)
{
    FILE * input = fopen(filename, "r");
    if (!input) return NULL;
    fseek(input, 0, SEEK_END);
    unsigned int fl = (unsigned int)ftell(input);
    if (debug) printf("program size: %i\n", fl);

    fseek(input, 0, SEEK_SET);

    char * BFProg = (char*) malloc(fl*sizeof(char)+1);
    BFProg[fl] = '\0';                                  //EOS char for ease of use as a string
    for (unsigned int i = 0; i < fl; i++)
            BFProg[i] = getc(input);

    fclose(input);

    return BFProg;
}

void
cleanUpBFProg(char * BFProg)
{
    free(BFProg);
    return;
}

bool
runBF(byte * BFMem, const char * BFProg)
{
    const char * proggers = BFProg;
    byte * mPtr = BFMem;
    long unsigned int r = 0;
    while (*proggers!='\0')
    {


        if (debug) printf("Prog Adress: %i; Instruction: %c; Mem adress: %i; Mem value: %i\n", proggers-BFProg, *proggers, mPtr-BFMem, *mPtr);
        switch(*proggers)
        {
            case '>':
                mPtr++;
                break;
            case '<':
                mPtr--;
                break;
            case '+':
                ++(*mPtr);
                break;
            case '-':
                --(*mPtr);
                break;
            case '.':
                if (debug) printf("\n-------------\n%i\n-------------\n",*mPtr);
                putchar(*mPtr);
                //putchar('\n');
                break;
            case ',':
                *mPtr=(byte)getchar();
                break;
            case '[':
                if (!*mPtr) //printf("[ and 0!\n");
                {
                    int nc = 0;
                    while (!(*proggers == ']'))
                    {
                        proggers++;
                        if (*proggers == '[')
                            i_nestCrawl(BFProg,&proggers,'[',']');
                    }
                }

                //if (*mPtr) printf("[ and non0!\n");
                break;
            case ']':
                //if (!*mPtr) printf("] and 0!\n");

                if (*mPtr) //printf("] and non0!\n");
                {
                    int nc = 0;
                    while (!(*proggers == '['))
                    {
                        proggers--;
                        if (*proggers == ']')
                            i_nestCrawl(BFProg,&proggers,']','[');
                    }

                }
                break;
            default:
                break;
        }
        if (mPtr < BFMem)
        {
            mPtr+= bfms;
        }
        //printf("\n%i\n",mPtr-BFMem);
        //mPtr = (char*)((((int)mPtr-(int)BFMem)%bfms)+(int)BFMem);
        proggers++;
    }
}

static void i_nestCrawl(const char * BFProg,const char ** proggers, char start, char stop)
{
    if (debug) printf("Nesting on char %i, being %c ...\n", *proggers-BFProg, **proggers);
    while (**proggers != stop)
    {
        (*proggers)+= stop-92;
        if (debug) printf(" Prog Adress: %i; Instruction: %c\n", *proggers-BFProg, **proggers);
        if (**proggers == start)
            i_nestCrawl(BFProg, proggers, start, stop);
    }
    if (debug) printf("Nest ended on char %i, being %c !\n", *proggers-BFProg, **proggers);
    (*proggers)+=stop-92;
    return;
}
