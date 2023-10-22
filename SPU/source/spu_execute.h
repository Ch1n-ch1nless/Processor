#ifndef CALCULATOR_H_INCLUDED
#define CALCULATOR_H_INCLUDED

#include "spu_input.h"
#include <stdlib.h>
#include <math.h>

static int BIT_MASK_OF_COMMAND   = 31;
static int BIT_MASK_OF_ARGS_TYPE = 96;

enum CMD : int
{
    CMD_HLT  = -1,
    CMD_PUSH =  1,
    CMD_IN   =  2,
    CMD_ADD  =  3,
    CMD_SUB  =  4,
    CMD_MUL  =  5,
    CMD_DIV  =  6,
    CMD_SQRT =  7,
    CMD_SIN  =  8,
    CMD_COS  =  9,
    CMD_OUT  = 10
};

error_t ExecuteCommands(Processor* clm);

#endif // CALCULATOR_H_INCLUDED
