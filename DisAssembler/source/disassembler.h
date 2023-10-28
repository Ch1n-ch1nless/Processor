#ifndef ASSEMBLER_H_INCLUDED
#define ASSEMBLER_H_INCLUDED

#include "../../Onegin/source/text.h"
#include "../../Onegin/source/make_text.h"
#include "../../Onegin/source/print_text.h"
#include "../../Stack/source/struct_and_const.h"

#include "../../Common_files/commands.h"
#include "../../Common_files/registers.h"
#include "../../Common_files/labels.h"

#define PRINT_ERROR(error)                              \
    if (error != NO_ERR)                                \
    {                                                   \
        fprintf(stdout, "%s:%d\n", __FILE__, __LINE__); \
    }

ERRORS TranslateMachineCode(elem_t* cmd_array, Text* asm_code);

ERRORS OpenFile(const char* file_name, FILE** file_pointer, const char* mode);

ERRORS CountBufferSize(size_t* len, const char* file_name);

ERRORS ReadArrayOfCommands(FILE* file_pointer, elem_t* cmd_array, const size_t len);

#endif // ASSEMBLER_H_INCLUDED
