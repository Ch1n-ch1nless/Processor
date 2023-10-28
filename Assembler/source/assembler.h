#ifndef ASSEMBLER_H_INCLUDED
#define ASSEMBLER_H_INCLUDED

#include "../../Onegin/source/text.h"
#include "../../Onegin/source/make_text.h"
#include "../../Onegin/source/print_text.h"
#include "../../Stack/source/struct_and_const.h"

#include "../../Common_files/commands.h"
#include "../../Common_files/registers.h"
#include "label.h"

#define PRINT_ERROR(error)                              \
    if (error != NO_ERR)                                \
    {                                                   \
        fprintf(stdout, "%s:%d\n", __FILE__, __LINE__); \
    }

ERRORS TranslateAssemblerCode(elem_t* cmd_array, Text* asm_code);

ERRORS OpenFile(const char* file_name, FILE** file_pointer, const char* mode);

ERRORS PrintToFile(elem_t* cmd_array, FILE* output_fp, const size_t len);

void   TranslateCmdArgs(elem_t* cmd_array, size_t* index, char* str_arg, unsigned arg_type,
                        ERRORS* error,     LabelTable* lbl_table, size_t number_of_cycle);

void   DeleteExtraSpacesAndTabs(char** string);

bool   GetNumberArg(elem_t* cmd_array, size_t* index, char* str_arg, ERRORS* error);

bool   GetRegisterArg(elem_t* cmd_array, size_t* index, char* str_arg, ERRORS* error);

bool   GetLabelArg(elem_t* cmd_array, size_t* index, char* str_arg, ERRORS* error,
                                                                                LabelTable* lbl_table);

bool   GetRAMArg(elem_t* cmd_array, size_t* index, char** str_arg, ERRORS* error);

#endif // ASSEMBLER_H_INCLUDED
