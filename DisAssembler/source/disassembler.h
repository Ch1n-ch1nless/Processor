#ifndef ASSEMBLER_H_INCLUDED
#define ASSEMBLER_H_INCLUDED

#include "../../Onegin/source/text.h"
#include "../../Onegin/source/make_text.h"
#include "../../Onegin/source/print_text.h"
#include "../../Stack/source/struct_and_const.h"

#include "../../Common_files/commands.h"
#include "../../Common_files/registers.h"

#define CHECK_ERROR(error)                              \
    if (error != NO_ERR)                                \
    {                                                   \
        fprintf(stdout, "%s:%d\n", __FILE__, __LINE__); \
    }

error_t TranslateMachineCode(FILE* output, elem_t* cmd_array, const size_t len);

error_t OpenFile(const char* file_name, FILE** file_pointer, const char* mode);

error_t CountBufferSize(size_t* len, const char* file_name);

error_t ReadArrayOfCommands(FILE* file_pointer, elem_t* cmd_array, const size_t len);

#endif // ASSEMBLER_H_INCLUDED
