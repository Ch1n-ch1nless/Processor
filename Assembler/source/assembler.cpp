#include "assembler.h"

ERRORS TranslateAssemblerCode(elem_t* cmd_array, Text* asm_code)
{
    ERRORS error = NO_ERR;

    size_t index = 0;

    for (size_t i = 0; i < asm_code->n_lines; i++)
    {
        char* cmd_begin = asm_code->line_array[i].str_ptr + 2;

        for (size_t j = 0; j < DICTIONARY_LEN; j++)
        {
            if (strnicmp(cmd_begin, DICTIONARY[j].asm_cmd, DICTIONARY[j].cmd_len) == 0)
            {
                cmd_array[index] = DICTIONARY[j].byte_cmd;
                index++;

                char* arg_begin = cmd_begin + DICTIONARY[j].cmd_len + 1;
                elem_t argument = POISON_VALUE;

                if (sscanf(arg_begin, elem_format, &argument) == 1)
                {
                    cmd_array[index] = argument;
                    index++;
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

/*ERRORS MakeBinCmdArray(elem_t* cmd_array, const size_t len)
{
    assert(cmd_array);

    cmd_array = (elem_t*) calloc(len, sizeof(elem_t));
    if (cmd_array == nullptr)
    {
        return MEM_ALLOC_ERR;
    }

    return NO_ERR;
}*/

ERRORS PrintToFile(elem_t* cmd_array, FILE* output_fp, const size_t len)
{
    assert(cmd_array);
    assert(output_fp);

    ERRORS error = NO_ERR;

    if (fwrite(cmd_array, sizeof(elem_t), len, output_fp) < len)
    {
        return WRITE_TO_FILE_ERR;
    }

    return error;
}
