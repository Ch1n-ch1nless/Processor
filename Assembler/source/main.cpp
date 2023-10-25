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

    Text asm_code = {};

    error = FillText(input_file, &asm_code);
    PRINT_ERROR(error)

    elem_t* cmd_array = nullptr;
    size_t  len = 2 * asm_code.n_lines;

    cmd_array = (elem_t*) calloc(len, sizeof(elem_t));
    if (cmd_array == nullptr)
    {
        error = MEM_ALLOC_ERR;
    }
    PRINT_ERROR(error)

    error = TranslateAssemblerCode(cmd_array, &asm_code);
    PRINT_ERROR(error)

    FILE* output_fp = nullptr;

    error = OpenFile(output_file, &output_fp, "wb");
    PRINT_ERROR(error)

    error = PrintToFile(cmd_array, output_fp, len);
    PRINT_ERROR(error)

    FreeText(&asm_code);

    free(cmd_array);

    fclose(output_fp);

    return 0;
}
