#ifndef ASM_CHECK_H_INCLUDED
#define ASM_CHECK_H_INCLUDED

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

void    DeleteExtraSpacesAndTabs(char** string);

error_t CheckCorrectnessOfArguments(char* str_arg, unsigned int arg_type);

error_t CheckCorrectnessOfBrackets(char** str_arg);

error_t CheckCorrectnessOfSymbols(char** str_arg, size_t* count_of_args);

#endif // ASM_CHECK_H_INCLUDED
