#ifndef CALCULATOR_H_INCLUDED
#define CALCULATOR_H_INCLUDED

#include "spu_input.h"
#include <stdlib.h>
#include <math.h>

#include "../../Common_files/global_cmd_consts_and_structs.h"

error_t ExecuteCommands(Processor* clm, Stack* call_stk);

#endif // CALCULATOR_H_INCLUDED
