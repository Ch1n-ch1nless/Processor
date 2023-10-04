#include "cpu.h"

void ProcessorCalculate(Stack* cpu_stk)
{
    FILE* byte_code_ptr = fopen("Txt/commands_in_byte_code.txt", "r");
    if (byte_code_ptr == nullptr)
    {
        printf("In Preprocessor/Stack/source/calculate.cpp \n"
               "Program can NOT open the file byte_code.txt\n");
        return;
    }

    while(true)
    {
        unsigned int mode = 0;
        fscanf(byte_code_ptr, "%u", &mode);
        switch(mode)
        {
            case(PUSH_MODE):
                ProcessorPush(byte_code_ptr, cpu_stk);
                break;

            case(IN_MODE):
                ProcessorIn(cpu_stk);
                break;

            case(ADD_MODE):
                ProcessorAdd(cpu_stk);
                break;

            case(SUB_MODE):
                ProcessorSub(cpu_stk);
                break;

            case(MUL_MODE):
                ProcessorMul(cpu_stk);
                break;

            case(DIV_MODE):
                ProcessorDiv(cpu_stk);
                break;

            case(SQRT_MODE):
                ProcessorSqrt(cpu_stk);
                break;

            case(SIN_MODE):
                ProcessorSin(cpu_stk);
                break;

            case(COS_MODE):
                ProcessorCos(cpu_stk);
                break;

            case(OUT_MODE):
                ProcessorOut(cpu_stk);
                break;

            case(HLT_MODE):
                return;

            default:
                printf("Error in Preprocessor/Stack/cpu.cpp(%d)\n", __LINE__);
                break;
        }
    }
    return;
}

void ProcessorPush(FILE* byte_code_ptr, Stack* cpu_stk)
{
    elem_t new_elem = POISON_VALUE;
    fscanf(byte_code_ptr, elem_format, &new_elem);

    StackPush(cpu_stk, new_elem);

    return;
}

void ProcessorIn(Stack* cpu_stk)
{
    elem_t new_elem = POISON_VALUE;
    scanf(elem_format, &new_elem);

    StackPush(cpu_stk, new_elem);

    return;
}

void ProcessorAdd(Stack* cpu_stk)
{
    elem_t elem_x = POISON_VALUE;
    elem_t elem_y = POISON_VALUE;

    StackPop(cpu_stk, &elem_x);
    StackPop(cpu_stk, &elem_y);

    StackPush(cpu_stk, elem_x + elem_y);

    return;
}

void ProcessorSub(Stack* cpu_stk)
{
    elem_t elem_x = POISON_VALUE;
    elem_t elem_y = POISON_VALUE;

    StackPop(cpu_stk, &elem_y);
    StackPop(cpu_stk, &elem_x);

    StackPush(cpu_stk, elem_x - elem_y);

    return;
}

void ProcessorMul(Stack* cpu_stk)
{
    elem_t elem_x = POISON_VALUE;
    elem_t elem_y = POISON_VALUE;

    StackPop(cpu_stk, &elem_y);
    StackPop(cpu_stk, &elem_x);

    StackPush(cpu_stk, elem_x * elem_y);

    return;
}

void ProcessorDiv(Stack* cpu_stk)
{
    elem_t elem_x = POISON_VALUE;
    elem_t elem_y = POISON_VALUE;

    StackPop(cpu_stk, &elem_y);
    StackPop(cpu_stk, &elem_x);

    StackPush(cpu_stk, elem_x / elem_y);

    return;
}

void ProcessorSqrt(Stack* cpu_stk)
{
    elem_t stk_elem = POISON_VALUE;

    StackPop(cpu_stk, &stk_elem);

    double sqrt_elem = sqrt((double) stk_elem);

    stk_elem = (elem_t) sqrt_elem;

    StackPush(cpu_stk, stk_elem);

    return;
}

void ProcessorSin(Stack* cpu_stk)
{
    elem_t stk_elem = POISON_VALUE;

    StackPop(cpu_stk, &stk_elem);

    double sin_elem = sin((double) stk_elem);

    stk_elem = (elem_t) sin_elem;

    StackPush(cpu_stk, stk_elem);

    return;
}

void ProcessorCos(Stack* cpu_stk)
{
    elem_t stk_elem = POISON_VALUE;

    StackPop(cpu_stk, &stk_elem);

    double cos_elem = cos((double) stk_elem);

    stk_elem = (elem_t) cos_elem;

    StackPush(cpu_stk, stk_elem);

    return;
}

void ProcessorOut(Stack* cpu_stk)
{
    elem_t stk_elem = POISON_VALUE;

    StackPop(cpu_stk, &stk_elem);

    fprintf(stdout, elem_format "\n", stk_elem);
}
