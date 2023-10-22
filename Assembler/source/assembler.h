#ifndef ASSEMBLER_H_INCLUDED
#define ASSEMBLER_H_INCLUDED

#include "../../Onegin/source/text.h"
#include "../../Onegin/source/make_text.h"
#include "../../Onegin/source/print_text.h"
#include "../../Stack/source/struct_and_const.h"

enum CMD : int
{
    CMD_HLT  = -1,
    CMD_PUSH =  1,
    CMD_IN   =  2,
    CMD_ADD  =  3,
    CMD_SUB  =  4,
    CMD_MUL  =  5,
    CMD_DIV  =  6,
    CMD_SQRT =  7,
    CMD_SIN  =  8,
    CMD_COS  =  9,
    CMD_OUT  = 10,
    END_CMD
};

const size_t DICTIONARY_LEN = END_CMD;

struct Translation
{
    const char* asm_cmd;
    size_t      cmd_len;
    CMD         byte_cmd;
};

const Translation DICTIONARY[] = {
                                    {"push", 4, CMD_PUSH},
                                    {"in",   2, CMD_IN  },
                                    {"add",  3, CMD_ADD },
                                    {"sub",  3, CMD_SUB },
                                    {"mul",  3, CMD_MUL },
                                    {"div",  3, CMD_DIV },
                                    {"sqrt", 4, CMD_SQRT},
                                    {"sin",  3, CMD_SIN },
                                    {"cos",  3, CMD_COS },
                                    {"out",  3, CMD_OUT },
                                    {"hlt",  3, CMD_HLT }
                                };

ERRORS TranslateAssemblerCode(elem_t* cmd_array, Text* asm_code);

ERRORS OpenFile(const char* file_name, FILE** file_pointer, const char* mode);

//ERRORS MakeBinCmdArray(elem_t* cmd_array, const size_t len);

ERRORS PrintToFile(elem_t* cmd_array, FILE* output_fp, const size_t len);

#endif // ASSEMBLER_H_INCLUDED
