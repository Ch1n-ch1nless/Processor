#include "disassembler.h"

error_t TranslateMachineCode(FILE* output_fp, elem_t* cmd_array, const size_t len)
{
    assert(output_fp);
    assert(cmd_array);

    error_t error = NO_ERR;

    for (size_t ip = 0; ip < len; ip++)
    {
        int command = cmd_array[ip] & BITMASK_OPCODE;

        for (size_t cmd_index = 0; cmd_index < NUMBER_OF_COMMANDS; cmd_index++)
        {
            if (command == COMMAND_SET[cmd_index].byte_cmd)
            {
                fprintf(output_fp, "\t\t%s ", COMMAND_SET[cmd_index].asm_cmd);

                int arg_type = cmd_array[ip] & BITMASK_SGNT;
                if (arg_type == NONE)
                {
                    break;
                }
                ip++;

                if (arg_type & RAM)
                {
                    fprintf(output_fp,"[");

                    if (arg_type & REG)
                    {
                        fprintf(output_fp, "%s", REG_DICTIONARY[cmd_array[ip]].name);
                    }
                    else
                    {
                        fprintf(output_fp, "%d", cmd_array[ip]);
                    }

                    fprintf(output_fp,"]");
                    break;
                }
                if (arg_type & REG)
                {
                    fprintf(output_fp, "%s", REG_DICTIONARY[cmd_array[ip]].name);
                    break;
                }
                if (arg_type & NUM)
                {
                    fprintf(output_fp, "%d", cmd_array[ip]);
                    break;
                }
                if (arg_type & LBL)
                {
                    fprintf(output_fp, "label_%d", cmd_array[ip]);
                    break;
                }
                else
                {
                    fprintf(output_fp, "Error!!!");
                }

                break;
            }
        }

        fprintf(output_fp, "\n");
    }

    return error;
}

error_t OpenFile(const char* file_name, FILE** file_pointer, const char* mode)
{
    assert(file_name != nullptr);

    *file_pointer = fopen(file_name, mode);
    if (*file_pointer == nullptr)
    {
        return OPEN_FILE_ERR;
    }

    return NO_ERR;
}

error_t CountBufferSize(size_t* len, const char* file_name)
{
    assert(len);
    assert(file_name);

    error_t error = NO_ERR;

    struct stat st = {};
    if (stat(file_name, &st) == -1)
    {
        error = OPEN_FILE_ERR;
        return error;
    }

    *len = (st.st_size) / sizeof(elem_t);

    return error;
}

error_t ReadArrayOfCommands(FILE* file_pointer, elem_t* cmd_array, const size_t len)
{
    assert(file_pointer);
    assert(cmd_array);

    error_t error = NO_ERR;

    if (fread(cmd_array, sizeof(elem_t), len, file_pointer) < len)
    {
        return error | READ_FEW_ARGS_ERR;
    }

    return error;
}
