#include <iostream>
#include <conio.h>
#include "stack.hpp"

int main() {
    Stack_t stk;
    Stack_Construct(&stk, 5);
    Stack_Dump(&stk);

    Stack_Push(&stk, 1);
    Stack_Push(&stk, 3);
    Stack_Push(&stk, 10);
    Stack_Push(&stk, 5);
    Stack_Push(&stk, 13);
    Stack_Dump(&stk);

    Stack_Push(&stk, 6);
    Stack_Dump(&stk);

    Stack_Pop(&stk); Stack_Pop(&stk); Stack_Pop(&stk); Stack_Pop(&stk); Stack_Pop(&stk); Stack_Pop(&stk);
    Stack_Dump(&stk);

    Stack_Grow(&stk);
    Stack_Dump(&stk);

    getch();
    return 0;
}