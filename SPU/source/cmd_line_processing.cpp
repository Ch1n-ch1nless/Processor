#include "cmd_line_processing.h"

error_t CheckArguments(int argc, const char** argv)
{
    if (argc < COUNT_OF_ARGS)
    {
        return FEW_CMD_LINE_ARGS_ERR;
    }
    else if (argc > COUNT_OF_ARGS)
    {
        return MANY_CMD_LINE_ARGS_ERR;
    }
    else
    {
        for (size_t i = 1; i < COUNT_OF_ARGS; i++)
        {
            if (CheckFile(argv[i], INPUT_FILE_EXTENSION))
            {
                return NO_ERR;
            }
        }
        return INCORRECT_INPUT_FILE_ERR;
    }
}

void HandleErrorsOfCheckArguments(error_t error, int argc, const char** argv)
{
    if (error & FEW_CMD_LINE_ARGS_ERR)
    {
        printf("ERROR!!! Program gets few command line arguments!!!\n %d < %d", argc, COUNT_OF_ARGS);
    }
    if (error & MANY_CMD_LINE_ARGS_ERR)
    {
        printf("ERROR!!! Program gets many command line arguments!!!\n %d > %d", argc, COUNT_OF_ARGS);
    }
    if (error & INCORRECT_INPUT_FILE_ERR)
    {
        printf("ERROR!!! The input file does NOT have extension = .%s", INPUT_FILE_EXTENSION);
    }
}

bool CheckFile(const char *str, const char* file_extension)
{
    assert(str != nullptr);

    const char* last_point_ptr = nullptr;
    char point = '.';
    const char* ptr = strchr(str, point);

    while (ptr != nullptr)
    {
        ptr++;
        last_point_ptr = ptr;
        ptr = strchr(ptr,  point);
    }

    if (last_point_ptr == nullptr)
    {
        return false;
    }
    else
    {
        return (!strcmp(last_point_ptr, file_extension));
    }
}
