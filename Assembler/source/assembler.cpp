#include "assembler.h"

ERRORS TranslateAssemblerCode(elem_t* cmd_array, Text* asm_code)
{
    ERRORS error = NO_ERR;

    Label lbl_array[MAX_SIZE_OF_CAPACITY] = {};  //Make array of labels

    size_t lbl_len = 0;

    for (size_t number_of_cycle = 0; number_of_cycle < 2; number_of_cycle++)
    {
        size_t index = 0;

        for (size_t i = 0; i < asm_code->n_lines; i++)
        {
            char* cmd_begin = asm_code->line_array[i].str_ptr;

            DeleteExtraSpacesAndTabs(&cmd_begin);

            if (strchr(cmd_begin, ':') != nullptr)
            {
                cmd_begin = cmd_begin + 1; //Skip the colon

                lbl_array[lbl_len].str = cmd_begin;

                lbl_array[lbl_len].line = index;

                size_t size_lbl = 0;

                while (isalpha(cmd_begin[size_lbl]))
                {
                    size_lbl++;
                }

                lbl_array[lbl_len].len = size_lbl;

                lbl_len++;
            }
            else
            {
                for (size_t j = 0; j < DICTIONARY_LEN; j++)
                {
                    if (strnicmp(cmd_begin, DICTIONARY[j].asm_cmd, DICTIONARY[j].cmd_len) == 0)
                    {
                        cmd_array[index] = DICTIONARY[j].byte_cmd;

                        char* str_arg = cmd_begin + DICTIONARY[j].cmd_len + (DICTIONARY[j].type_of_args != NONE);

                        TranslateCmdArgs(cmd_array, &index, str_arg, DICTIONARY[j].type_of_args,
                                         &error,    lbl_array, &lbl_len, number_of_cycle);

                        index++;
                    }
                }
            }
        }
        printf("============\n");
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

void TranslateCmdArgs(elem_t* cmd_array, size_t* index, char* str_arg, unsigned arg_type,
                      ERRORS* error, Label* lbl_array, size_t* lbl_len, size_t number_of_cycle)
{
    size_t i = *index;

    DeleteExtraSpacesAndTabs(&str_arg);

    if (arg_type & NONE)
    {
        return;
    }

    if (arg_type & NUM)
    {
        elem_t number = POISON_VALUE;

        if (sscanf(str_arg, "%d", &number) == 1)
        {
            cmd_array[i] += NUM * (number_of_cycle % 2 == 1);
            i++;
            cmd_array[i] = number;
            *index = i;

            return;
        }

        *index = i;
    }

    if (arg_type & REG)
    {
        for (size_t k = 0; k < REGISTER_COUNT; k++)
        {
            if (strnicmp(str_arg, REGISTERS_DICTIONARY[k].name, REGISTERS_DICTIONARY[k].len) == 0)
            {
                cmd_array[i] += REG * (number_of_cycle % 2 == 1);
                i++;
                cmd_array[i] = REGISTERS_DICTIONARY[k].num;
                *index = i;

                return;
            }
        }

        *index = i;
        return;
    }

    if (arg_type & LBL)
    {
        for (size_t k = 0; k < *lbl_len; k++)
        {
            if (strnicmp(str_arg, lbl_array[k].str, lbl_array[k].len) == 0)
            {
                cmd_array[i] += LBL * (number_of_cycle % 2 == 1);
                i++;
                cmd_array[i] = lbl_array[k].line + 1;
                *index = i;

                return;
            }
        }

        *index = i;
        return;
    }

    *index = i;
    return;
}

void DeleteExtraSpacesAndTabs(char** string)
{
    size_t count_of_extra_char = 0;  //Count of extra spaces, tabs before command
    char temp_array[] = {};          //Temporary array of symbols

    sscanf(*string, "%[ \t]%n", temp_array, &count_of_extra_char);

    *string = *string + count_of_extra_char;

    return;
}
