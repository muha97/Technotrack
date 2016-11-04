#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctime>

#ifndef DEBUG_MODE
#define DEBUG_MODE
#endif //! Эта команда должна стоять здесь

#if DEBUG_MODE
    #define $ if(1)
#else
    #define $ ;
#endif
//! А не здесь.

bool dump_created = 0;

#define T
struct Stack_t
{
    double* data;
    int count;
    int max_size;
};

/*
    * Разбей файл на .h и .cpp. В заголовочном должны быть все прототипы и структура.
    * А в .cpp все реализации.
*/

/*
    * Я чуть-чуть подправил формаьирование. Посмотри по diff, где именно.
    * И определись наконец, ставишь ты пробелы между названием функции и
    * скобками, или нет.
*/

void Stack_Construct (Stack_t* stack, const int len)
{
    assert (stack);

    $   printf ("Allocating stack->data ...\n");
    stack->data = (double*) calloc(len, sizeof(double));
    $   printf ("Stack data allocated.\n");

    stack->count    =   0;
    stack->max_size = len;
}

void Stack_Destruct (Stack_t* stack)
{
    free (stack->data);

    stack->data     = NULL;
    stack->count    =   -1;
    stack->max_size = -666;
}

bool Stack_OK (const Stack_t* stack) //Stack is OK? 1 - YES, 0 -NO
{
    return ( stack                            &&
             stack->data                      &&
             stack->count >= 0                &&
             stack->count <= stack->max_size;
}

bool Stack_Empty (const Stack_t* stack) //Stack is empty? 1 -YES, 0 -NO
{
    return stack->count == 0;
}

bool Stack_Grow (Stack_t* stack)
{
    assert (Stack_OK(stack));

    stack->max_size *= 2;

    $   printf ("in Stack_Grow: increasing stack size twice ...\n");
    stack->data = (double*) realloc(stack->data, stack->max_size * sizeof(double));
    $   printf ("Stack_Grow done succesfully.\n");
}

void Stack_Push (Stack_t* stack, const double val)
{
    assert (Stack_OK(stack));

    /*
        * Здесь надо бы изменить подход. Минус твоего в том, что стек может
        * разшириться без надобности. Просто от того, что он заполнен.

        * Стек должен расширяться, когда он уже заполнен и ты туда ещё что-то
        * пихаешь. Так что логику нужно изменить так, чтобы сначала шла проверка
        * на заполненность, а потом уже пушилось значение.
    */

    stack->data[stack->count++] = val;

    $   printf ("Push %6.3lf\n", val);

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
        $   printf ("Pop %6.3lf\n", stack->data[stack->count-1]);
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
        /*
            * Используй errno
            * Да и на самом деле, нужно не только причину ошибки выводить, но и
            * содержимое струкутруры. Так что статус (OK/NOTOK) я бы вынес
            * в отдельный if.
        */
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
            fprintf(dump, "%d: %6.3lf\n", i, stack->data[i]);
        }
    }

    fclose(dump);
}
