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

error_t CountBufferSize(Processor* proc, const char* file_name)
{
    assert(proc);
    assert(file_name);

    error_t error = NO_ERR;

    struct stat st = {};
    if (stat(file_name, &st) == -1)
    {
        error = OPEN_FILE_ERR;
        return error;
    }

    proc->buf_size = (st.st_size) / sizeof(elem_t) + 1;

    return error;
}

error_t ReadArrayOfCommands(FILE* file_pointer, Processor* proc)
{
    assert(file_pointer);
    assert(proc);

    error_t error = NO_ERR;

    proc->cmd_array = (elem_t*) calloc(proc->buf_size, sizeof(elem_t));
    if (proc->cmd_array == nullptr)
    {
        return error | MEM_ALLOC_ERR;
    }

    if (fread(proc->cmd_array, sizeof(elem_t), proc->buf_size, file_pointer) < proc->buf_size)
    {
        return error | READ_FEW_ARGS_ERR;
    }

    return error;
}
