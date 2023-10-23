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

    Stack call_stk  = {
                        #ifdef WITH_CANARY
                            .left_canary = LEFT_CANARY_VALUE,
                        #endif
                        .data = nullptr,
                        .size = 0,
                        .capacity = 0,
                        .name = nullptr,
                        .file = nullptr,
                        .line = -1,
                        .status = KILLED_STACK,
                        #ifdef WITH_HASH
                            .hash = 0,
                        #endif
                        #ifdef WITH_CANARY
                            .right_canary = RIGHT_CANARY_VALUE,
                        #endif
                      };

    error = STACK_CTOR(&call_stk); //Make the call stack
    PRINT_ERROR(&call_stk, error);

    MAKE_PROCESSOR(clm);  //C.L.M. = Capybara Loves Maths

    error = ProcessorCtor(&clm);
    PRINT_PROC_ERR(error, &clm)

    error = OpenFile(&file_pointer, argv[1], "rb");
    PRINT_PROC_ERR(error, &clm)

    error = CountBufferSize(&clm, argv[1]);
    PRINT_PROC_ERR(error, &clm)

    error = ReadArrayOfCommands(file_pointer, &clm);
    PRINT_PROC_ERR(error, &clm)

    error = ExecuteCommands(&clm, &call_stk);
    PRINT_PROC_ERR(error, &clm)
    PRINT_ERROR(&call_stk, error);

    ProcessorDtor(&clm);

    fclose(file_pointer);

    return 0;
}
