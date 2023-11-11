#include "spu_execute.h"
#include "cmd_line_processing.h"

int main(int argc, const char* argv[])
{
    error_t error = NO_ERR;

    FILE* file_pointer = nullptr;

    const char* filename = nullptr;

    //Check correctness of command's arguments
    error = CheckArguments(argc, argv, &filename);

    if (error != NO_ERR)
    {
        //Handle errors in command's arguments
        HandleErrorsOfCheckArguments(error, argc);
        return error;
    }

    //Create processor
    Processor proc = {
                      .stk       = {},
                      .call_stk  = {},
                      .reg_array = nullptr,
                      .cmd_array = nullptr,
                      .buf_size  = 0,
                     };

    error = ProcessorCtor(&proc);
    CHECK_PROC_ERR(error, &proc)

    //Open binary file
    error = OpenFile(&file_pointer, filename, "rb");
    CHECK_PROC_ERR(error, &proc)

    error = CountBufferSize(&proc, filename);
    CHECK_PROC_ERR(error, &proc)

    error = ReadArrayOfCommands(file_pointer, &proc);
    CHECK_PROC_ERR(error, &proc)

    error = ExecuteCommands(&proc);
    CHECK_PROC_ERR(error, &proc)

    #ifdef WITH_PROC_DUMP
        PRINT_PROCESSOR(&proc);
    #endif

    ProcessorDtor(&proc);

    fclose(file_pointer);

    return 0;
}
