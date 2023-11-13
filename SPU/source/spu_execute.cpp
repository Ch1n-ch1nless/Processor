#include "spu_execute.h"

error_t ExecuteCommands(Processor* proc)
{
    error_t error = NO_ERR;
    CHECK_PROC_ERR(error, proc)

    for (size_t cmd_index = 0; cmd_index < proc->buf_size; cmd_index++)
    {
        int command = proc->cmd_array[cmd_index] & BITMASK_OPCODE;

        #define DEF_CMD(name, num, arg_type, num_of_args, action) \
            case(CMD_##name):                                     \
                action                                            \
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
            CHECK_PROC_ERR(error, proc)
        }
    }

    return error;
}

error_t GetArgument(Processor* proc, size_t index, int     signature,
                                                   elem_t* argument, elem_t** arg_pointer)
{
    error_t error = NO_ERR;

    if (signature == NONE || signature == LBL)
    {
        return error;
    }

    if (signature & RAM)
    {
        if (signature & NUM)
        {
            size_t ram_index = proc->cmd_array[index];
            *arg_pointer = &(proc->ram[ram_index]);
            *argument = proc->ram[ram_index];
        }
        else if (signature & REG)
        {
            size_t reg_index = proc->cmd_array[index];
            size_t ram_index = proc->reg_array[reg_index];
            *arg_pointer = &(proc->ram[ram_index]);
            *argument = proc->ram[ram_index];
        }
        else
        {
            return error | WRONG_SYNTAX_ERR;
        }
    }
    else
    {
        if (signature & NUM)
        {
            *argument = proc->cmd_array[index];
            return error;
        }
        else if (signature & REG)
        {
            size_t reg_index = proc->cmd_array[index];
            *arg_pointer = &(proc->reg_array[reg_index]);
            *argument = proc->reg_array[reg_index];
        }
        else
        {
            return error | WRONG_SYNTAX_ERR;
        }
    }

    return error;
}
