#include "cmd_line_processing.h"

int main(int argc, const char* argv[])
{
    error_t error = NO_ERR;

    const char* input_file  = nullptr;
    const char* output_file = nullptr;

    //Check correctness of command's arguments
    error = CheckArguments(&input_file, &output_file, argc, argv);

    if (error != NO_ERR)
    {
        //Handle errors in command's arguments
        HandleErrorsOfCheckArguments(error, argc, argv);
        return error;
    }

    Text asm_code = {}; //Struct from Onegin

    error |= FillText(input_file, &asm_code); //Get assembler code
    CHECK_ERROR(error != NO_ERR, error)

    elem_t* cmd_array = nullptr;        //Binary Array of commands
    size_t  len = 2 * asm_code.n_lines;

    cmd_array = (elem_t*) calloc(len, sizeof(elem_t));
    CHECK_ERROR(cmd_array == nullptr, error | MEM_ALLOC_ERR);

    //Translate assembler's commands to binary array
    error |= TranslateAssemblerCode(cmd_array, &asm_code);
    CHECK_ERROR(error != NO_ERR, error)

    FILE* output_fp = nullptr;  //Binary file

    //Open binary file
    error |= OpenFile(output_file, &output_fp, "wb");
    CHECK_ERROR(error != NO_ERR, error)

    //Write array to binary file
    error |= PrintToFile(cmd_array, output_fp, len);
    CHECK_ERROR(error != NO_ERR, error)

    FreeText(&asm_code);

    free(cmd_array);

    fclose(output_fp);

    return 0;
}
