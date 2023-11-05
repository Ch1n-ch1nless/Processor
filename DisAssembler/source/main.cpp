#include "cmd_line_processing.h"

int main(int argc, const char* argv[])
{
    error_t error = NO_ERR;

    const char* input_file  = nullptr;
    const char* output_file = nullptr;

    error = CheckArguments(&input_file, &output_file, argc, argv);

    if (error != NO_ERR)
    {
        HandleErrorsOfCheckArguments(error, argc, argv);
        return error;
    }

    FILE* input_fp  = nullptr;
    FILE* output_fp = nullptr;

    size_t buf_size = 0;

    error |= CountBufferSize(&buf_size, input_file);

    elem_t* cmd_array = nullptr;

    cmd_array = (elem_t*) calloc(buf_size, sizeof(elem_t));

    error |= OpenFile(input_file, &input_fp, "rb");

    error |= OpenFile(output_file, &output_fp, "w");

    error |= ReadArrayOfCommands(input_fp, cmd_array, buf_size);

    error |= TranslateMachineCode(output_fp, cmd_array, buf_size);

    free(cmd_array);

    fclose(output_fp);

    return 0;
}
