#ifndef ASSEMBLER_H_INCLUDED
#define ASSEMBLER_H_INCLUDED

#include "../../Onegin/source/text.h"
#include "../../Onegin/source/make_text.h"
#include "../../Onegin/source/print_text.h"
#include "../../Stack/source/struct_and_const.h"

#include "../../Common_files/commands.h"
#include "../../Common_files/registers.h"
#include "label.h"

#define CHECK_ERROR(condition, error)                       \
    if (condition)                                          \
    {                                                       \
        fprintf(stdout, "%s:%d\n", __FILE__, __LINE__);     \
        return error;                                       \
    }

error_t TranslateAssemblerCode(elem_t* cmd_array, Text* asm_code);

error_t OpenFile(const char* file_name, FILE** file_pointer, const char* mode);

error_t PrintToFile(elem_t* cmd_array, FILE* output_fp, const size_t len);

void    TranslateCmdArg(elem_t* cmd_array, size_t* opcode_addr, char* str_arg, unsigned arg_type,
                        error_t* error,    LabelTable* lbl_table, size_t number_of_cycle);

void    DeleteExtraSpacesAndTabs(char** string);

bool    GetNumberArg(elem_t* cmd_array, size_t* index, char* str_arg, error_t* error);

bool    GetRegisterArg(elem_t* cmd_array, size_t* index, char* str_arg, error_t* error);

bool    GetLabelArg(elem_t* cmd_array, size_t* index, char* str_arg, error_t* error,
                                                                     LabelTable* lbl_table);

bool    GetRAMArg(elem_t* cmd_array, size_t* index, char** str_arg, error_t* error);

#endif // ASSEMBLER_H_INCLUDED
