#include "assembler.h"

ERRORS TranslateAssemblerCode(elem_t* cmd_array, Text* asm_code)
{
    ERRORS error = NO_ERR;

    for (size_t l = 0; l < 2; l++)
    {
        size_t index = 0;

        for (size_t i = 0; i < asm_code->n_lines; i++)
        {
            char* cmd_begin = asm_code->line_array[i].str_ptr;

            if (strchr(cmd_begin, ':') != nullptr && cmd_begin[0] != '\t')
            {
                for (size_t j = 0; j < LABELS_COUNT; j++)
                {
                    if (strnicmp(cmd_begin, LABELS_ARRAY[j].name, LABELS_ARRAY[j].len) == 0)
                    {
                        LABELS_ARRAY[j].line = index;
                        break;
                    }
                }
            }
            else
            {
                cmd_begin = cmd_begin + 2;
                for (size_t j = 0; j < DICTIONARY_LEN; j++)
                {
                    if (strnicmp(cmd_begin, DICTIONARY[j].asm_cmd, DICTIONARY[j].cmd_len) == 0)
                    {
                        cmd_array[index] = DICTIONARY[j].byte_cmd;

                        char* str_arg = cmd_begin + DICTIONARY[j].cmd_len + (DICTIONARY[j].type_of_args != NONE);

                        TranslateCmdArgs(cmd_array, &index, str_arg, DICTIONARY[j].type_of_args, &error);

                        index++;
                    }
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

void TranslateCmdArgs(elem_t* cmd_array, size_t* index, char* str_arg, unsigned arg_type, ERRORS* error)
{
    #define DEF_SGNT(name, num, action)              \
        if (arg_type & name)                         \
        {                                            \
            action;                                  \
        }

    size_t i = *index;
    #include "../../DSL/signature.dsl"
    *index = i;

    #undef DEF_SGNT
}
