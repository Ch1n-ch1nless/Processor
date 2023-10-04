#ifndef CALCULATOR_H_INCLUDED
#define CALCULATOR_H_INCLUDED

#include "../../Stack/source/stack.h"
#include <stdlib.h>
#include <math.h>

enum MODE : unsigned int
{
    PUSH_MODE = 1,
    IN_MODE   = 2,
    ADD_MODE  = 3,
    SUB_MODE  = 4,
    MUL_MODE  = 5,
    DIV_MODE  = 6,
    SQRT_MODE = 7,
    SIN_MODE  = 8,
    COS_MODE  = 9,
    OUT_MODE  = 10,
    HLT_MODE  = 0
};

void ProcessorCalculate(Stack* cpu_stk);
void ProcessorPush(FILE* byte_code_ptr, Stack* cpu_stk);
void ProcessorIn(Stack* cpu_stk);
void ProcessorAdd(Stack* cpu_stk);
void ProcessorSub(Stack* cpu_stk);
void ProcessorMul(Stack* cpu_stk);
void ProcessorDiv(Stack* cpu_stk);
void ProcessorSqrt(Stack* cpu_stk);
void ProcessorSin(Stack* cpu_stk);
void ProcessorCos(Stack* cpu_stk);
void ProcessorOut(Stack* cpu_stk);

#endif // CALCULATOR_H_INCLUDED
