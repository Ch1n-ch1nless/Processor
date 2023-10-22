#ifndef TEXT_H_INCLUDED
#define TEXT_H_INCLUDED

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <TXLib.h>

#define $CHECK_AND_RETURN_ERROR                              \
if (error != NO_ERR) {                                       \
    fprintf(stdout, "%s:%d\n", __FILE__, __LINE__);          \
    return error;                                            \
}

#define $CHECK_ERROR_AND_RETURN_ONEGIN                       \
if (*error != NO_ERR) {                                      \
    fprintf(stdout, "%s:%d\n", __FILE__, __LINE__);          \
    return onegin;                                           \
}

struct Line
{
    char* str_ptr;
    size_t str_len;
};

struct Text
{
    FILE* file_ptr;
    size_t buf_size;
    char* buffer;
    size_t n_lines;
    Line* line_array;

};

enum ERRORS
{
    NO_ERR                    = 0,
    OPEN_FILE_ERR             = 1 << 0,
    MEM_ALLOC_ERR             = 1 << 1,
    FEW_CMD_LINE_ARGS_ERR     = 1 << 2,
    MANY_CMD_LINE_ARGS_ERR    = 1 << 3,
    INCORRECT_INPUT_FILE_ERR  = 1 << 4,
    INCORRECT_OUTPUT_FILE_ERR = 1 << 5,
    WRITE_TO_FILE_ERR         = 1 << 6
};

#endif // TEXT_H_INCLUDED
