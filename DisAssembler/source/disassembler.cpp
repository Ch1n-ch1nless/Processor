#include "assembler.h"

ERRORS TranslateMachineCode(elem_t* cmd_array, const size_t len)
{
    ERRORS error = NO_ERR;

    for (size_t ip = 0; ip < len; ip++)
    {
        int command = cmd_array[i] & BITMASK_OPCODE;

        for (size_t j = 0; j < DICTIONARY_LEN; j++)
        {
            if (command == DICTIONARY[j].byte_cmd)
            {
                fprintf(output_fp, "%s ", DICTIONARY[j].asm_cmd);

                int arg_type = cmd_array[ip] & BITMASK_SGNT;
                i++;

                if (arg_type & RAM)
                {
                    fprintf(output_fp,"[%d]\n", cmd_array[ip]);
                    break;
                }
                if (arg_type & REG)
                {
                    fprintf(output_fp, "%s\n", REGISTERS_DICTIONARY[cmd_array[ip]].name);
                    break;
                }
                if (arg_type & NUM)
                {
                    fprintf(output_fp, "%d\n", cmd_array[ip]);
                    break;
                }
                if (arg_type & LBL)
                {
                    fprintf(output_fp, "label_%d", cmd_array[ip]);
                    break;
                }
                else
                {
                    fprintf(output_fp"\n");
                    break;
                }
            }
        }
    }

    return error;
}

ERRORS OpenFile(const char* file_name, FILE** file_pointer, const char* mode)
{
    assert(file_name != nullptr);

    *file_pointer = fopen(file_name, mode);
    if (*file_pointer == nullptr)
    {
        return OPEN_FILE_ERR;
    }

    return NO_ERR;
}

ERRORS CountBufferSize(size_t* len, const char* file_name)
{
    assert(len);
    assert(file_name);

    ERRORS error = NO_ERR;

    struct stat st = {};
    if (stat(file_name, &st) == -1)
    {
        error = OPEN_FILE_ERR;
        return error;
    }

    len = (st.st_size) / sizeof(elem_t) + 1;

    return error;
}

ERRORS ReadArrayOfCommands(FILE* file_pointer, elem_t* cmd_array, const size_t len)
{
    assert(file_pointer);
    assert(cmd_array);

    ERRORS error = NO_ERR;

    cmd_array = (elem_t*) calloc(len, sizeof(elem_t));
    if (cmd_array == nullptr)
    {
        return error | MEM_ALLOC_ERR;
    }

    if (fread(ccmd_array, sizeof(elem_t), len, file_pointer) < len)
    {
        return error | READ_FEW_ARGS_ERR;
    }

    return error;
}
