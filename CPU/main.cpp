#ifndef DEBUG_MODE
#define DEBUG_MODE 1

#if DEBUG_MODE
#define $ if(1)
#else
#define $ ;
#endif
#endif

//-----------------------------------------

#include <iostream>
#include <conio.h>
#include <cstdio>
#include <cstring>
#include "stack.hpp"

#define COMPARE(X)  if (Stack_Pop (&program) X Stack_Pop (&program))    \
                        Stack_Push (&program, 1);                       \
                    else                                                \
                        Stack_Push (&program, 0);

#define OPERATE(X) Stack_Push (&program, Stack_Pop (&program) X Stack_Pop (&program));

//------------------------------------------

const char commands[15][11] = {"push_const","push_reg","add","sub","mul","div",
            "equal","noteq","boreq","aoreq","below","above","and","or","negate"};
int main()
{
    FILE* in = fopen ("in.txt","r");
    Stack_t program;
    Stack_Construct (&program, 10);

    int c = 0;
    char buf[11] = {};
    int i;
    for (i = 0; i < 11; i++)
        buf[i] = '\0';
    i = 0;
    bool no_cmd = 1;

    while( (c = fgetc(in)) != EOF)
    {
        if (c == ' ' || c == '\n')
        {
            buf[i] = '\0';

            for (i = 0; i < 15; i++)
            {
                if (strcmp (buf, commands[i]) == 0)
                {
                    no_cmd = 0;
                    if ((i == 0) || (i == 1))
                        break;
                    switch (i)
                    {
                        case 2:
                        {
                            OPERATE(+)
                            break;
                        }
                        case 3:
                        {
                            OPERATE(-)
                            break;
                        }
                        case 4:
                        {
                            OPERATE(*)
                            break;
                        }
                        case 5:
                        {
                            OPERATE(/)
                        }
                        case 6:
                        {
                            COMPARE(==)
                            break;
                        }
                        case 7:
                        {
                            COMPARE(!=)
                            break;
                        }
                        case 8:
                        {
                            COMPARE(<=)
                            break;
                        }
                        case 9:
                        {
                            COMPARE(>=)
                            break;
                        }
                        case 10:
                        {
                            COMPARE(<)
                            break;
                        }
                        case 11:
                        {
                            COMPARE(>)
                            break;
                        }
                        case 12:
                        {
                            COMPARE(&&)
                            break;
                        }
                        case 13:
                        {
                            COMPARE(||)
                            break;
                        }
                        case 14:
                        {
                            Stack_Push (&program, Stack_Pop (&program) ^ 1);
                        }
                    }
                    break;
                }
            }
            if (no_cmd)
            {
                Stack_Push (&program, atoi(buf));
                printf ("number %d pushed (buf = %s)\n", atoi(buf), buf);
            }

            no_cmd = 1;
            for (i = 0; i < 11; i++)
                buf[i] = '\0';
            i = 0;
        }
        else
            buf[i++] = (char)c;
    }
    Stack_Dump (&program);

    fclose(in);
    getch();
    return 0;
}