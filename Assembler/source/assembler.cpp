#include "assembler.h"

error_t TranslateAssemblerCode(elem_t* cmd_array, Text* asm_code)
{
    error_t error = NO_ERR;

    LabelTable lbl_table = {};

    error = LabelTableCtor(&lbl_table);
    CHECK_ERROR(error != NO_ERR, error)

    for (size_t pass = 0; pass < 2; pass++)
    {
        size_t index = 0;

        for (size_t i = 0; i < asm_code->n_lines; i++)
        {
            char* cmd_begin = asm_code->line_array[i].str_ptr;

            DeleteExtraSpacesAndTabs(&cmd_begin);

            if (cmd_begin[0] == ':')
            {
                cmd_begin++;

                Label new_lbl = {};

                error = MakeNewLabel(cmd_begin, &new_lbl, index);
                CHECK_ERROR(error != NO_ERR, error)

                size_t lbl_num = 0;

                while (lbl_num < lbl_table.size)
                {
                    if (stricmp(new_lbl.str, lbl_table.array[lbl_num].str) == 0)
                    {
                        lbl_table.array[lbl_num].line = new_lbl.line;
                        break;
                    }
                    lbl_num++;
                }

                if (lbl_num >= lbl_table.size)
                {
                    error |= LabelTablePush(&lbl_table, new_lbl);
                    CHECK_ERROR(error != NO_ERR, error)
                }
            }
            else
            {
                for (size_t n = 0; n < NUMBER_OF_COMMANDS; n++)
                {
                    if (strnicmp(cmd_begin, COMMAND_SET[n].asm_cmd, COMMAND_SET[n].cmd_len) == 0)
                    {
                        cmd_array[index] = COMMAND_SET[n].byte_cmd;

                        char* str_arg = cmd_begin + COMMAND_SET[n].cmd_len;

                        DeleteExtraSpacesAndTabs(&str_arg);

                        TranslateCmdArg(cmd_array, &index, str_arg, COMMAND_SET[n].type_of_args,
                                        &error,    &lbl_table);
                        //CHECK_ERROR(error != NO_ERR, error)

                        index++;
                    }
                }
            }
        }

        LabelTableDump(&lbl_table);
    }

    LabelTableDtor(&lbl_table);

    return error;
}

void TranslateCmdArg(elem_t* cmd_array, size_t* opcode_addr, char* str_arg, unsigned int arg_type,
                      error_t* error, LabelTable* lbl_table)
{
    DeleteExtraSpacesAndTabs(&str_arg);

    if (arg_type == NONE)
    {
        return;
    }
    else
    {
        *opcode_addr += 1;
        cmd_array[*opcode_addr] = POISON_VALUE;

        int type = 0;

        if ((arg_type & RAM) && GetRAMArg(cmd_array, opcode_addr, &str_arg, error))
        {
            type |= RAM;

            if ((arg_type & NUM) && GetNumberArg(cmd_array, opcode_addr, str_arg, error))
            {
                type |= NUM;
            }
            if ((arg_type & REG) && GetRegisterArg(cmd_array, opcode_addr, str_arg, error))
            {
                type |= REG;
            }

        }
        else
        {
            if ((arg_type & NUM) && GetNumberArg(cmd_array, opcode_addr, str_arg, error))
            {
                type |= NUM;
            }

            if ((arg_type & LBL) && GetLabelArg(cmd_array, opcode_addr, str_arg, error, lbl_table))
            {
                type |= LBL;
            }

            if ((arg_type & REG) && GetRegisterArg(cmd_array, opcode_addr, str_arg, error))
            {
                type |= REG;
            }

            /*if (type == NONE)
            {
                *error |= WRONG_SYNTAX_ERR;
                return;
            }*/
        }

        cmd_array[*opcode_addr - 1] |= type;

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

bool GetNumberArg(elem_t* cmd_array, size_t* index, char* str_arg, error_t* error)
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

bool GetRegisterArg(elem_t* cmd_array, size_t* index, char* str_arg, error_t* error)
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

bool GetLabelArg(elem_t* cmd_array, size_t* index, char* str_arg, error_t* error, LabelTable* lbl_table)
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

bool GetRAMArg(elem_t* cmd_array, size_t* index, char** str_arg, error_t* error)
{
    char* ram_begin = nullptr;

    ram_begin = *str_arg;

    if (ram_begin[0] == '[')
    {
        ram_begin++;            //Skip the square bracket

        if (strchr(ram_begin, ']') != nullptr)
        {
            DeleteExtraSpacesAndTabs(&ram_begin);

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

error_t CheckEndOfArgument(char* str_arg)
{
    error_t error = NO_ERR;

    size_t index = 0;

    size_t count_of_args = 0;

    while(str_arg[index] != '\n')
    {
        if (str_arg[index] == ' ' || str_arg[index] == '\t')
        {
            count_of_args++;
            while (str_arg[index] == ' ' || str_arg[index] == '\t')
            {
                index++;
            }
        }
        else
        {
            index++;
        }
    }

    if (count_of_args > 1)
    {
        return error | WRONG_SYNTAX_ERR;
    }

    return error;
}
