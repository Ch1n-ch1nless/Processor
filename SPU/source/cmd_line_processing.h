#ifndef CMD_LINE_PROCESSING_H_INCLUDED
#define CMD_LINE_PROCESSING_H_INCLUDED

#include "spu.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int COUNT_OF_ARGS = 2;

const char* const INPUT_FILE_EXTENSION = "bin";

error_t CheckArguments(int argc, const char** argv, const char** filename);

void    HandleErrorsOfCheckArguments(error_t error, int argc);

bool    CheckFile(const char *str, const char* file_extension);

#endif // CMD_LINE_PROCESSING_H_INCLUDED
