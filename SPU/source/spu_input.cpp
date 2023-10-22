#include "spu_input.h"

error_t OpenFile(FILE** file_pointer, const char* file_name, const char* mode)
{
    assert(file_pointer != nullptr);
    assert(file_name != nullptr);
    assert(mode != nullptr);

    error_t error = NO_ERR;

    *file_pointer = fopen(file_name, mode);
    if (*file_pointer == nullptr)
    {
        error = OPEN_FILE_ERR;
    }

    return error;
}

error_t CountBufferSize(Processor* clm, const char* file_name)
{
    assert(clm);
    assert(file_name);

    error_t error = NO_ERR;

    struct stat st = {};
    if (stat(file_name, &st) == -1)
    {
        error = OPEN_FILE_ERR;
        return error;
    }

    clm->buf_size = (st.st_size) / sizeof(elem_t) + 1;

    return error;
}

error_t ReadArrayOfCommands(FILE* file_pointer, Processor* clm)
{
    assert(file_pointer);
    assert(clm);

    error_t error = NO_ERR;

    clm->cmd_array = (elem_t*) calloc(clm->buf_size, sizeof(elem_t));
    if (clm->cmd_array == nullptr)
    {
        return error | MEM_ALLOC_ERR;
    }

    if (fread(clm->cmd_array, sizeof(elem_t), clm->buf_size, file_pointer) < clm->buf_size)
    {
        return error | READ_FEW_ARGS_ERR;
    }

    return error;
}
