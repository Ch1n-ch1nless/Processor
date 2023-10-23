#include "spu_execute.h"

error_t ExecuteCommands(Processor* clm, Stack* call_stk)
{
    error_t error = NO_ERR;
    PRINT_PROC_ERR(error, clm)

    for (size_t i = 0; i < clm->buf_size; i++)
    {
        int command = clm->cmd_array[i] & BIT_MASK_OF_CMD;

        if (clm->cmd_array[i] == CMD_HLT)
        {
            return error;
        }

#define DEF_CMD(name, num, arg_type, num_of_args, action) \
    case(CMD_##name):                                     \
    action                                                \
    break;

        switch(command)
        {
#include "../../DSL/commands.dsl"

            default:
                printf("ERROR!!! Undefined Command in [%d]\n", i);
                break;
        }

#undef DEF_CMD

        PRINT_PROC_ERR(error, clm)
    }

    return error;
}
