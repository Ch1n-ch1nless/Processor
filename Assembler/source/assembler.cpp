#include "assembler.h"

ERRORS TranslateAssemblerCode(elem_t* cmd_array, Text* asm_code)
{
    ERRORS error = NO_ERR;

    LabelTable lbl_table = {};

    LabelTableCtor(&lbl_table);

    for (size_t number_of_cycle = 0; number_of_cycle < 2; number_of_cycle++)
    {
        size_t index = 0;

        for (size_t i = 0; i < asm_code->n_lines; i++)
        {
            char* cmd_begin = asm_code->line_array[i].str_ptr;

            DeleteExtraSpacesAndTabs(&cmd_begin);

            if (strchr(cmd_begin, ':') != nullptr)
            {
                Label new_lbl = {};

                error = MakeNewLabel(cmd_begin, &new_lbl, index);
                PRINT_ERROR(error)

                size_t lbl_num = 0;

                while (lbl_num < lbl_table.size)
                {
                    if (new_lbl.str == lbl_table.array[lbl_num].str)
                    {
                        lbl_table.array[lbl_num].line = new_lbl.line;
                        break;
                    }
                    lbl_num++;
                }

                if (lbl_num >= lbl_table.size)
                {
                    error = LabelTablePush(&lbl_table, new_lbl);
                    PRINT_ERROR(error)
                }
            }
            else
            {
                for (size_t n = 0; n < DICTIONARY_LEN; n++)
                {
                    if (strnicmp(cmd_begin, DICTIONARY[n].asm_cmd, DICTIONARY[n].cmd_len) == 0)
                    {
                        cmd_array[index] = DICTIONARY[n].byte_cmd;

                        char* str_arg = cmd_begin + DICTIONARY[n].cmd_len;

                        DeleteExtraSpacesAndTabs(&str_arg);

                        TranslateCmdArgs(cmd_array, &index, str_arg, DICTIONARY[n].type_of_args,
                                         &error,    &lbl_table, number_of_cycle);

                        index++;
                    }
                }
            }
        }
    }

    LabelTableDump(&lbl_table);

    LabelTableDtor(&lbl_table);

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
                      ERRORS* error, LabelTable* lbl_table, size_t number_of_cycle)
{
    DeleteExtraSpacesAndTabs(&str_arg);

    if (arg_type == NONE)
    {
        return;
    }
    else
    {
        size_t ip = *index;
        ip++;
        *index = ip;
        cmd_array[ip] = POISON_VALUE;

        bool ret_value = false;

        if (arg_type & RAM)
        {
            ret_value = GetRAMArg(cmd_array, index, &str_arg, error);

            if (ret_value == true)
            {
                ip--;
                cmd_array[ip] += RAM * (number_of_cycle % 2 == 1);
                ip++;
            }
        }

        if (arg_type & NUM)
        {
            ret_value = GetNumberArg(cmd_array, index, str_arg, error);

            if (ret_value == true)
            {
                ip--;
                cmd_array[ip] += NUM * (number_of_cycle % 2 == 1);
                ip++;
            }
        }

        if (arg_type & LBL)
        {
            ret_value = GetLabelArg(cmd_array, index, str_arg, error, lbl_table);

            if (ret_value == true)
            {
                ip--;
                cmd_array[ip] += LBL * (number_of_cycle % 2 == 1);
                ip++;
            }
        }

        if (arg_type & REG)
        {
            ret_value = GetRegisterArg(cmd_array, index, str_arg, error);

            if (ret_value == true)
            {
                ip--;
                cmd_array[ip] += REG * (number_of_cycle % 2 == 1);
                ip++;
            }
        }

        return;
    }
}

void DeleteExtraSpacesAndTabs(char** string)
{
    size_t count_of_extra_char = 0;  //Count of extra spaces, tabs before command
    char temp_array[] = {};          //Temporary array of symbols

    sscanf(*string, "%[ \t]%n", temp_array, &count_of_extra_char);

    *string = *string + count_of_extra_char;

    return;
}

bool GetNumberArg(elem_t* cmd_array, size_t* index, char* str_arg, ERRORS* error)
{
    elem_t number = POISON_VALUE;

    if (sscanf(str_arg, "%d", &number) == 1)
    {
        *(cmd_array + *index) = number;

        return true;
    }
    else
    {
        return false;
    }
}

bool GetRegisterArg(elem_t* cmd_array, size_t* index, char* str_arg, ERRORS* error)
{
    for (size_t reg_index = 0; reg_index < REGISTER_COUNT; reg_index++)
    {
        if (strnicmp(str_arg, REG_DICTIONARY[reg_index].name, REG_DICTIONARY[reg_index].len) == 0)
        {
            *(cmd_array + *index) = REG_DICTIONARY[reg_index].num;

            return true;
        }
    }

    return false;
}

bool GetLabelArg(elem_t* cmd_array, size_t* index, char* str_arg, ERRORS* error, LabelTable* lbl_table)
{
    for (size_t lbl_index = 0; lbl_index < lbl_table->size; lbl_index++)
    {
        if (strnicmp(str_arg, lbl_table->array[lbl_index].str, lbl_table->array[lbl_index].len) == 0)
        {
            *(cmd_array + *index) = lbl_table->array[lbl_index].line;

            return true;
        }
    }

    return false;
}

bool GetRAMArg(elem_t* cmd_array, size_t* index, char** str_arg, ERRORS* error)
{
    char* ram_begin = nullptr;

    size_t ip = *index;

    ram_begin = strchr(*str_arg, '[');

    if (ram_begin != nullptr)
    {
        ram_begin = ram_begin + 1;            //Skip the square bracket

        if (strchr(ram_begin, ']') != nullptr)
        {
            *str_arg = ram_begin;

            return true;
        }
        else
        {
            *error = WRONG_SYNTAX_ERR;

            return false;
        }
    }

    return false;
}
