#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include "spu_execute.h"

#include "cmd_line_processing.h"

#define MAKE_PROCESSOR(nick)                \
    Processor nick = {                      \
                      .stk       = {},      \
                      .reg_array = nullptr, \
                      .cmd_array = nullptr, \
                      .buf_size  = 0,       \
                     }

#endif // MAIN_H_INCLUDED
