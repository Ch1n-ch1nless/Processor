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
    NO_ERR,
    OPEN_FILE_ERR,
    MEM_ALLOC_ERR
};

#endif // TEXT_H_INCLUDED
