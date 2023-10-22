#include "spu_execute.h"

error_t ExecuteCommands(Processor* clm)
{
    error_t error = NO_ERR;
    PRINT_PROC_ERR(error, clm)

    for (size_t i = 0; i < clm->buf_size; i++)
    {
        int command = clm->cmd_array[i] & BIT_MASK_OF_COMMAND;

        if (clm->cmd_array[i] == CMD_HLT)
        {
            return error;
        }

        switch(command)
        {
            case(CMD_PUSH):
            {
                i++;
                error = ProcessorStkPush(clm, clm->cmd_array[i]);
                break;
            }

            case(CMD_IN):
            {
                elem_t new_value = POISON_VALUE;
                scanf(elem_format, &new_value);
                error = ProcessorStkPush(clm, new_value);
                break;
            }

            case(CMD_ADD):
            {
                elem_t first  = POISON_VALUE;
                elem_t second = POISON_VALUE;
                error = ProcessorStkPop(clm, &second);
                error = ProcessorStkPop(clm, &first);
                error = ProcessorStkPush(clm, first + second);
                break;
            }

            case(CMD_SUB):
            {
                elem_t first  = POISON_VALUE;
                elem_t second = POISON_VALUE;
                error = ProcessorStkPop(clm, &second);
                error = ProcessorStkPop(clm, &first);
                error = ProcessorStkPush(clm, first - second);
                break;
            }

            case(CMD_MUL):
            {
                elem_t first  = POISON_VALUE;
                elem_t second = POISON_VALUE;
                error = ProcessorStkPop(clm, &second);
                error = ProcessorStkPop(clm, &first);
                error = ProcessorStkPush(clm, first * second);
                break;
            }

            case(CMD_DIV):
            {
                elem_t first  = POISON_VALUE;
                elem_t second = POISON_VALUE;
                error = ProcessorStkPop(clm, &second);
                error = ProcessorStkPop(clm, &first);
                error = ProcessorStkPush(clm, first / second);
                break;
            }

            case(CMD_SQRT):
            {
                elem_t x  = POISON_VALUE;
                error = ProcessorStkPop(clm, &x);
                error = ProcessorStkPush(clm, sqrt((double) x));
                break;
            }

            case(CMD_SIN):
            {
                elem_t x  = POISON_VALUE;
                error = ProcessorStkPop(clm, &x);
                error = ProcessorStkPush(clm, sin((double) x));
                break;
            }

            case(CMD_COS):
            {
                elem_t x  = POISON_VALUE;
                error = ProcessorStkPop(clm, &x);
                error = ProcessorStkPush(clm, cos((double) x));
                break;
            }

            case(CMD_OUT):
            {
                elem_t x  = POISON_VALUE;
                error = ProcessorStkPop(clm, &x);
                printf(elem_format, x);
                break;
            }

            case(CMD_HLT):
                return error;

            default:
            {
                printf("ERROR!!! Undefined command!!!\n");
                break;
            }
        }

        PRINT_PROC_ERR(error, clm)
    }

    return error;
}
