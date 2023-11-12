#ifndef SPU_EXECUTE_H_INCLUDED
#define SPU_EXECUTE_H_INCLUDED

#include "spu_input.h"
#include <stdlib.h>
#include <math.h>

#include "../../Common_files/commands.h"

error_t ExecuteCommands(Processor* proc);

error_t GetArgument(Processor* proc, size_t index, int     signature,
                                                   elem_t* argument, elem_t** arg_pointer);

#endif // SPU_EXECUTE_H_INCLUDED
