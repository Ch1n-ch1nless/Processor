#ifndef CMD_LINE_PROCESSING_H_INCLUDED
#define CMD_LINE_PROCESSING_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <TXLib.h>
#include "assembler.h"

static const char* INPUT_FILE_EXTENSION  = "asm";
static const char* OUTPUT_FILE_EXTENSION = "bin";

const size_t COUNT_OF_ARGS = 3;

error_t CheckArguments(const char** input_file, const char** output_file,
                       int argc, const char** argv);

void    HandleErrorsOfCheckArguments(error_t error, int argc, const char** argv);

bool    CheckFile(const char *str, const char* file_extension);

#endif // CMD_LINE_PROCESSING_H_INCLUDED
