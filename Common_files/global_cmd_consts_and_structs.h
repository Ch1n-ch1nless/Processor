#ifndef CONFIG_CMD_H_INCLUDED
#define CONFIG_CMD_H_INCLUDED

#include "global_sgnt_consts_and_structs.h"

const int BIT_MASK_OF_CMD  = 31;
const int BIT_MASK_OF_ARGS = 32 + 64;

#define DEF_CMD(name, cmd, ...) CMD_##name = cmd,

enum CMD : int
{
    #include "../DSL/commands.dsl"
    END_CMD
};

#undef DEF_CMD

const size_t DICTIONARY_LEN = END_CMD;

struct Translation
{
    const char*  asm_cmd;
    size_t       cmd_len;
    unsigned int type_of_args;
    size_t       num_of_args;
    int          byte_cmd;
};

#define DEF_CMD(name, cmd, signature, num_of_args, ...)  {#name, strlen(#name), signature, num_of_args, cmd},

const Translation DICTIONARY[] = {
                                    #include "../DSL/commands.dsl"
                                 };

#undef DEF_CMD

#endif // CONFIG_CMD_H_INCLUDED
