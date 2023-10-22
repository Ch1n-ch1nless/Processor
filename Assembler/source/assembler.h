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
    CMD_POP  = 11,
    END_CMD
};

const size_t DICTIONARY_LEN = END_CMD;

enum ArgsType : int
{
    NONE = 1 << 0,
    REG  = 1 << 5,
    NUM  = 1 << 6
};

struct Translation
{
    const char*  asm_cmd;
    size_t       cmd_len;
    unsigned int arg_type;
    CMD          byte_cmd;
};

const Translation DICTIONARY[] = {
                                    {"push", 4, REG | NUM, CMD_PUSH},
                                    {"in",   2, NONE,      CMD_IN  },
                                    {"add",  3, NONE,      CMD_ADD },
                                    {"sub",  3, NONE,      CMD_SUB },
                                    {"mul",  3, NONE,      CMD_MUL },
                                    {"div",  3, NONE,      CMD_DIV },
                                    {"sqrt", 4, NONE,      CMD_SQRT},
                                    {"sin",  3, NONE,      CMD_SIN },
                                    {"cos",  3, NONE,      CMD_COS },
                                    {"out",  3, NONE,      CMD_OUT },
                                    {"hlt",  3, NONE,      CMD_HLT },
                                    {"pop",  3, REG,       CMD_POP }
                                };

ERRORS TranslateAssemblerCode(elem_t* cmd_array, Text* asm_code);

ERRORS OpenFile(const char* file_name, FILE** file_pointer, const char* mode);

ERRORS PrintToFile(elem_t* cmd_array, FILE* output_fp, const size_t len);

#endif // ASSEMBLER_H_INCLUDED
