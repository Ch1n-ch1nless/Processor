#ifndef ASSEMBLER_H_INCLUDED
#define ASSEMBLER_H_INCLUDED

#include "../../Onegin/source/text.h"
#include "../../Onegin/source/make_text.h"
#include "../../Onegin/source/print_text.h"

enum MODE : unsigned int
{
    PUSH_MODE = 1,
    IN_MODE   = 2,
    ADD_MODE  = 3,
    SUB_MODE  = 4,
    MUL_MODE  = 5,
    DIV_MODE  = 6,
    SQRT_MODE = 7,
    SIN_MODE  = 8,
    COS_MODE  = 9,
    OUT_MODE  = 10,
    HLT_MODE  = 0
};

const size_t COUNT_OF_COMMANDS = 11;

struct translation
{
    const char* asm_cmd;
    MODE mode;
};

const translation cmd_array[] = {
                                    {"push", PUSH_MODE},
                                    {"in",   IN_MODE},
                                    {"add",  ADD_MODE},
                                    {"sub",  SUB_MODE},
                                    {"mul",  MUL_MODE},
                                    {"div",  DIV_MODE},
                                    {"sqrt", SQRT_MODE},
                                    {"sin",  SIN_MODE},
                                    {"cos",  COS_MODE},
                                    {"out",  OUT_MODE},
                                    {"hlt",  HLT_MODE}
                                };

ERRORS AssemblerTheInstruction(const char* outputfile, Text* guide);

#endif // ASSEMBLER_H_INCLUDED
