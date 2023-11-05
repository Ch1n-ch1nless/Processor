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

    Text asm_code = {};

    error |= FillText(input_file, &asm_code);
    CHECK_ERROR(error != NO_ERR, error)

    elem_t* cmd_array = nullptr;
    size_t  len = 2 * asm_code.n_lines;

    cmd_array = (elem_t*) calloc(len, sizeof(elem_t));
    CHECK_ERROR(cmd_array == nullptr, error | MEM_ALLOC_ERR);

    error |= TranslateAssemblerCode(cmd_array, &asm_code);
    CHECK_ERROR(error != NO_ERR, error)

    FILE* output_fp = nullptr;

    error |= OpenFile(output_file, &output_fp, "wb");
    CHECK_ERROR(error != NO_ERR, error)

    error |= PrintToFile(cmd_array, output_fp, len);
    CHECK_ERROR(error != NO_ERR, error)

    FreeText(&asm_code);

    free(cmd_array);

    fclose(output_fp);

    return 0;
}
