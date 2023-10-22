#ifndef ASSEMBLER_H_INCLUDED
#define ASSEMBLER_H_INCLUDED

#include "../../Onegin/source/text.h"
#include "../../Onegin/source/make_text.h"
#include "../../Onegin/source/print_text.h"
#include "../../Stack/source/struct_and_const.h"

#include "../../Common_files/global_cmd_consts_and_structs.h"
#include "../../Common_files/global_reg_consts_and_structs.h"
#include "../../Common_files/global_lbl_consts_and_structs.h"

ERRORS TranslateAssemblerCode(elem_t* cmd_array, Text* asm_code);

ERRORS OpenFile(const char* file_name, FILE** file_pointer, const char* mode);

ERRORS PrintToFile(elem_t* cmd_array, FILE* output_fp, const size_t len);

void   TranslateCmdArgs(elem_t* cmd_array, size_t* index, char* str_arg, unsigned arg_type, ERRORS* error);

#endif // ASSEMBLER_H_INCLUDED
