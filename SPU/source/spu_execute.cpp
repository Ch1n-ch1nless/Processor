#include "spu_execute.h"

error_t ExecuteCommands(Processor* clm, Stack* call_stk)
{
    error_t error = NO_ERR;
    PRINT_PROC_ERR(error, clm)

    for (size_t cmd_index = 0; cmd_index < clm->buf_size; cmd_index++)
    {
        int command = clm->cmd_array[cmd_index] & BITMASK_OPCODE;

        if (clm->cmd_array[cmd_index] == CMD_HLT)
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
                printf("ERROR!!! Undefined Command in [%d]\n", cmd_index);
                break;
        }

#undef DEF_CMD
        if (error != NO_ERR)
        {
            PRINT_PROC_ERR(error, clm)
        }
    }

    return error;
}
