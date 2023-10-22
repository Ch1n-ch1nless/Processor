#include "main.h"

int main(int argc, const char* argv[])
{
    error_t error = NO_ERR;

    FILE* file_pointer  = nullptr;

    error = CheckArguments(argc, argv);

    if (error != NO_ERR)
    {
        HandleErrorsOfCheckArguments(error, argc, argv);
        return error;
    }

    MAKE_PROCESSOR(clm);  //C.L.M. = Capybara Loves Maths

    error = ProcessorCtor(&clm);
    PRINT_PROC_ERR(error, &clm)

    error = OpenFile(&file_pointer, argv[1], "rb");
    PRINT_PROC_ERR(error, &clm)

    error = CountBufferSize(&clm, argv[1]);
    PRINT_PROC_ERR(error, &clm)

    error = ReadArrayOfCommands(file_pointer, &clm);
    PRINT_PROC_ERR(error, &clm)

    error = ExecuteCommands(&clm);
    PRINT_PROC_ERR(error, &clm)

    ProcessorDtor(&clm);

    fclose(file_pointer);

    return 0;
}