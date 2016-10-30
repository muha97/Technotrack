#define DEBUG_MODE 1

#if DEBUG_MODE
    #define $ if(1)
#endif

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctime>

bool dump_created = 0;

struct Stack_t
{
    int* data;
    int count;
    int max_size;
};

void Stack_Construct (Stack_t* stack, const int len)
{
    assert (stack);

$   printf ("Allocating stack->data ...\n");
    stack->data = (int*) calloc(len, sizeof(int));
$   printf ("Stack data allocated.\n");

    stack->count = 0;
    stack->max_size = len;
}

void Stack_Destruct (Stack_t* stack)
{
    free (stack->data);
    stack->data = NULL;
    stack->count = -1;
    stack->max_size = -666;
}

bool Stack_OK (const Stack_t* stack) //Stack is OK? 1 - YES, 0 -NO
{
    return ( stack && stack->data && (stack->count >= 0) && (stack->count <= stack->max_size) ) ? 1 : 0;
}

bool Stack_Empty (const Stack_t* stack) //Stack is empty? 1 -YES, 0 -NO
{
    return (stack->count == 0) ? 1 : 0;
}

bool Stack_Grow (Stack_t* stack)
{
    assert (Stack_OK(stack));

$   printf ("in Stack_Grow: increasing stack size twice ...\n");
    stack->data = (int*) realloc(stack->data, 2 * stack->max_size * sizeof(int));
$   printf ("Stack_Grow done succesfully.\n");

    stack->max_size *= 2;
}

void Stack_Push (Stack_t* stack, int val)
{
    assert (Stack_OK(stack));

    stack->data[stack->count++] = val;

$   printf ("Push %d\n", val);

    if (stack->count == stack->max_size)
    {
    $   printf ("Stack is trying to be allocated!\n");
        Stack_Grow (stack);
    $   printf ("Stack is allocated!\n");
    }
}

int Stack_Pop (Stack_t* stack)
{
    assert (Stack_OK(stack));

    if (Stack_Empty(stack))
        printf ("Trying to pop underflow stack!!!\n");
    else
    {
    $   printf ("Pop %d\n", stack->data[stack->count-1]);
        return stack->data[--stack->count];
    }
}

void Stack_Dump (Stack_t* stack)
{
    FILE* dump = fopen ("stack_dump.txt", "a");

    if (!dump_created)
    {
        fprintf(dump, "\n==============================================\n");
        time_t rawtime;
        struct tm *timeinfo;
        time(&rawtime);
        timeinfo = localtime(&rawtime);
        fprintf(dump, "%s", asctime(timeinfo));

        dump_created = 1;
    }

    if (!Stack_OK(stack))
    {
        fprintf(dump, "\nSTACK IS NOT OK!!!\n");
        if (!stack)
            fprintf(dump, "Stack points to NULL. ");
        if (!stack->data)
            fprintf(dump, "Stack has no data. ");
        if (stack->count < 0)
            fprintf(dump, "Stack's counter is negative.\n");
        if (stack->count >= stack->max_size)
            fprintf(dump, "Stack is overflow.\n");
    }
    else
    {
        fprintf(dump, "\nStack's max size is %d.\n", stack->max_size);
        fprintf(dump, "Stack has %d elements:\n", stack->count);

        int i = 0;
        for (; i < stack->count; ++i)
        {
            fprintf(dump, "%d: %d\n", i, stack->data[i]);
        }
    }

    fclose(dump);
}