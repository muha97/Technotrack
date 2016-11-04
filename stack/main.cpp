#include <iostream>
#include <conio.h>
#include "stack.hpp"

int main() {
    Stack_t stk;
    Stack_Construct(&stk, 5);
    Stack_Dump(&stk);

    Stack_Push(&stk, (double)1.0);
    Stack_Push(&stk, 3.0);
    Stack_Push(&stk, 10.0);
    Stack_Push(&stk, 5.0);
    Stack_Push(&stk, 13.0);
    Stack_Dump(&stk);

    Stack_Push(&stk, 6.0);
    Stack_Dump(&stk);

    Stack_Pop(&stk); Stack_Pop(&stk); Stack_Pop(&stk); Stack_Pop(&stk); Stack_Pop(&stk); Stack_Pop(&stk);
    Stack_Dump(&stk);

    Stack_Grow(&stk);
    Stack_Dump(&stk);

    getch();
    return 0;
}