#include "cmd_line_processing.h"

int main(int argc, const char* argv[])
{
    ERRORS error = NO_ERR;
    error_t new_error = NO_ERR;

    const char* input_file  = "lol";
    const char* output_file = "lol";

    new_error = CheckArguments(&input_file, &output_file, argc, argv);

    if (new_error != NO_ERR)
    {
        HandleErrorsOfCheckArguments(new_error, argc, argv);
        return new_error;
    }

    Text asm_code = {};

    error = FillText(input_file, &asm_code);
    $CHECK_AND_RETURN_ERROR

    elem_t* cmd_array = nullptr;
    size_t  len = 2 * asm_code.n_lines;

    cmd_array = (elem_t*) calloc(len, sizeof(elem_t));
    if (cmd_array == nullptr)
    {
        error = MEM_ALLOC_ERR;
    }
    $CHECK_AND_RETURN_ERROR

    error = TranslateAssemblerCode(cmd_array, &asm_code);
    $CHECK_AND_RETURN_ERROR

    for (size_t i = 0; i < 11; i++)
    {
        printf("[%d] = %d\n", i, cmd_array[i]);
    }

    FILE* output_fp = nullptr;

    error = OpenFile(output_file, &output_fp, "wb");
    $CHECK_AND_RETURN_ERROR

    error = PrintToFile(cmd_array, output_fp, len);
    $CHECK_AND_RETURN_ERROR

    FreeText(&asm_code);

    free(cmd_array);

    fclose(output_fp);

    return 0;
}
