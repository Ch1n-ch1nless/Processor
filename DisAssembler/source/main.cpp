#include "cmd_line_processing.h"

int main(int argc, const char* argv[])
{
    ERRORS error = NO_ERR;
    error_t new_error = NO_ERR;

    const char* input_file  = nullptr;
    const char* output_file = nullptr;

    new_error = CheckArguments(&input_file, &output_file, argc, argv);

    if (new_error != NO_ERR)
    {
        HandleErrorsOfCheckArguments(new_error, argc, argv);
        return new_error;
    }

    FILE* input_fp  = nullptr;
    FILE* output_fp = nullptr;

    size_t buf_size = 0;

    CountBufSize(input_file, &buf_size);

    elem_t* cmd_array = nullptr;

    cmd_array = (elem_t*) calloc(buf_size, sizeof(elem_t));

    error = OpenFile(input_file, input_fp, "rb");

    error = OpenFile(output_file, output_fp, "w");

    ReadFile(input_fp, cmd_array, buf_size);

    error = TranslateMachineCode(output_fp, cmd_array, buf_size)

    free(cmd_array);

    fclose(output_fp);

    return 0;
}
