#include "assembler.h"

error_t TranslateAssemblerCode(elem_t* cmd_array, Text* asm_code)
{
    assert((cmd_array != nullptr) && "Error! Pointer to cmd_array is NULL!!!");
    assert((asm_code  != nullptr) && "Error! Pointer to asm_code is NULL!!!");

    error_t error = NO_ERR;

    //Table of labels
    LabelTable lbl_table = {};

    //Create table of labels
    error = LabelTableCtor(&lbl_table);
    CHECK_ERROR(error != NO_ERR, error)

    for (size_t pass = 0; pass < 2; pass++)
    {
        size_t index = 0;

        for (size_t i = 0; i < asm_code->n_lines; i++)
        {
            char* cmd_begin = asm_code->line_array[i].str_ptr;

            //Skip white spaces and tabs before command
            DeleteExtraSpacesAndTabs(&cmd_begin);

            if (cmd_begin[0] == ';')
            {
                ;
            }
            else if (cmd_begin[0] == ':')
            {
                cmd_begin++;

                Label new_lbl = {};

                //Create label
                error = MakeNewLabel(cmd_begin, &new_lbl, index);
                CHECK_ERROR(error != NO_ERR, error)

                size_t lbl_num = 0;

                //Find new label
                while (lbl_num < lbl_table.size)
                {
                    if (stricmp(new_lbl.str, lbl_table.array[lbl_num].str) == 0)
                    {
                        lbl_table.array[lbl_num].line = new_lbl.line;
                        break;
                    }
                    lbl_num++;
                }

                //If label doesn't locates in array, add label to label's table
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
                    //Find command in set of commands
                    if (strnicmp(cmd_begin, COMMAND_SET[n].asm_cmd, COMMAND_SET[n].cmd_len) == 0)
                    {
                        cmd_array[index] = COMMAND_SET[n].byte_cmd;

                        char* str_arg = cmd_begin + COMMAND_SET[n].cmd_len;

                        //Check correctness of command's arguments
                        error = CheckCorrectnessOfArguments(str_arg);
                        CHECK_ERROR(error != NO_ERR, error)

                        //Skip white spaces and tabs
                        DeleteExtraSpacesAndTabs(&str_arg);

                        //Translate assembler argument to binary argument
                        TranslateCmdArg(cmd_array, &index, str_arg, COMMAND_SET[n].type_of_args,
                                        &error,    &lbl_table);
                        CHECK_ERROR(error != NO_ERR && pass % 2 == 1, error);

                        index++;
                    }
                }
            }
        }

        #ifdef WITH_LBL_DUMP
            LabelTableDump(&lbl_table);
        #endif
    }

    //Delete label's table
    LabelTableDtor(&lbl_table);

    return error;
}

void TranslateCmdArg(elem_t* cmd_array, size_t* opcode_addr, char* str_arg, unsigned int arg_type,
                      error_t* error, LabelTable* lbl_table)
{
    assert((cmd_array != nullptr)   && "Error! Pointer to array of commands is NULL!!!");
    assert((opcode_addr != nullptr) && "Error! Pointer to opcode_addr is NULL!!!");
    assert((str_arg != nullptr)     && "Error! Pointer to str_arg is NULL!!!");
    assert((error != nullptr)       && "Error! Pointer to error is NULL!!!");
    assert((lbl_table != nullptr)   && "Error! Pointer to label's table is NULL!!!");

    //Skips white spaces and tabs
    DeleteExtraSpacesAndTabs(&str_arg);

    if (arg_type == NONE)
    {
        return;
    }
    else
    {
        //Allocate a memory cell to the command's argument
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
        }

        if (type == NONE || type == RAM)
        {
            *error |= WRONG_SYNTAX_ERR;
        }

        cmd_array[*opcode_addr - 1] |= type;

        return;
    }
}

bool GetNumberArg(elem_t* cmd_array, size_t* index, char* str_arg, error_t* error)
{
    assert((cmd_array != nullptr) && "Error! Pointer to array of commands is NULL!!!");
    assert((index != nullptr)     && "Error! Pointer to index is NULL!!!");
    assert((str_arg != nullptr)   && "Error! Pointer to str_arg is NULL!!!");
    assert((error != nullptr)     && "Error! Pointer to error is NULL!!!");

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
    assert((cmd_array != nullptr) && "Error! Pointer to array of commands is NULL!!!");
    assert((index != nullptr)     && "Error! Pointer to index is NULL!!!");
    assert((str_arg != nullptr)   && "Error! Pointer to str_arg is NULL!!!");
    assert((error != nullptr)     && "Error! Pointer to error is NULL!!!");

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
    assert((cmd_array != nullptr) && "Error! Pointer to array of commands is NULL!!!");
    assert((index != nullptr)     && "Error! Pointer to index is NULL!!!");
    assert((str_arg != nullptr)   && "Error! Pointer to str_arg is NULL!!!");
    assert((error != nullptr)     && "Error! Pointer to error is NULL!!!");
    assert((lbl_table != nullptr) && "Error! Pointer to label's table is NULL!!!");

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
    assert((cmd_array != nullptr) && "Error! Pointer to array of commands is NULL!!!");
    assert((index != nullptr)     && "Error! Pointer to index is NULL!!!");
    assert((str_arg != nullptr)   && "Error! Pointer to str_arg is NULL!!!");
    assert((error != nullptr)     && "Error! Pointer to error is NULL!!!");

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
            *error |= WRONG_SYNTAX_ERR;

            return false;
        }
    }

    return false;
}
