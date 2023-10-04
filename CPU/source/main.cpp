#include "cpu.h"

int main()
{
    error_t error = NO_ERR;

    Stack cpu_stk = {};

    error = STACK_CTOR(&cpu_stk);
    if (error != NO_ERR)
    {
        PRINT_ERROR(&cpu_stk, error);
    }

    ProcessorCalculate(&cpu_stk);

    StackDtor(&cpu_stk);
}
