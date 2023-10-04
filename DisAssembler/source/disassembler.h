#ifndef DISASSEMBLER_H_INCLUDED
#define DISASSEMBLER_H_INCLUDED

#include "../../Onegin/source/onegin.h"

const size_t COUNT_OF_COMMANDS = 11;

struct translation
{
    const char* asm_cmd;
    const char* mode;
};

const translation cmd_array[] = {
                                    {"1",  "push"},
                                    {"2",  "in"},
                                    {"3",  "add"},
                                    {"4",  "sub"},
                                    {"5",  "mul"},
                                    {"6",  "div"},
                                    {"7",  "sqrt"},
                                    {"8",  "sin"},
                                    {"9",  "cos"},
                                    {"10", "out"},
                                    {"0",  "hlt"}
                                };

ERRORS DisAssemblerTheInstruction(const char* outputfile, Text* guide);


#endif // DISASSEMBLER_H_INCLUDED
