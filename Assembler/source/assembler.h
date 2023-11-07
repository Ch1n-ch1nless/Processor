#ifndef ASSEMBLER_H_INCLUDED
#define ASSEMBLER_H_INCLUDED

#include "asm_output.h"

#include "../../Common_files/commands.h"
#include "../../Common_files/registers.h"
#include "label.h"

#define CHECK_ERROR(condition, error)                       \
    if (condition)                                          \
    {                                                       \
        fprintf(stdout, "%s:%d\n", __FILE__, __LINE__);     \
        return error;                                       \
    }

#define DEF_CMD(name, num, arg_type, num_of_args, ...)                                         \
    static_assert(num_of_args < 2, "Wrong syntax in DSL! Function can't have > 1 argumets!\n");

#include "../../DSL/commands.dsl"

#undef DEF_CMD

error_t TranslateAssemblerCode(elem_t* cmd_array, Text* asm_code);

void    TranslateCmdArg(elem_t*  cmd_array, size_t*      opcode_addr,
                        char*    str_arg,   unsigned int arg_type,
                        error_t* error,     LabelTable*  lbl_table);

void    DeleteExtraSpacesAndTabs(char** string);

bool    GetNumberArg(elem_t* cmd_array, size_t* index, char* str_arg, error_t* error);

bool    GetRegisterArg(elem_t* cmd_array, size_t* index, char* str_arg, error_t* error);

bool    GetLabelArg(elem_t*     cmd_array, size_t*  index,
                    char*       str_arg,   error_t* error,
                    LabelTable* lbl_table);

bool    GetRAMArg(elem_t* cmd_array, size_t* index, char** str_arg, error_t* error);

error_t CheckEndOfArgument(char* str_arg);

#endif // ASSEMBLER_H_INCLUDED
