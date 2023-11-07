#ifndef ASM_OUTPUT_H_INCLUDED
#define ASM_OUTPUT_H_INCLUDED

#include "../../Onegin/source/text.h"
#include "../../Onegin/source/make_text.h"
#include "../../Onegin/source/print_text.h"
#include "../../Stack/source/struct_and_const.h"

error_t OpenFile(const char* file_name, FILE** file_pointer, const char* mode);

error_t PrintToFile(elem_t* cmd_array, FILE* output_fp, const size_t len);

#endif // ASM_OUTPUT_H_INCLUDED
