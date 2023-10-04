#include "disassembler.h"

int main()
{
    ERRORS error = NO_ERR;

    const char* input_file  = "Txt/commands_in_byte_code.txt";
    const char* output_file = "Txt/commands_in_asm_code.txt";

    Text instruction = FillText(input_file_ptr, &error);
    $CHECK_AND_RETURN_ERROR

    error = DisAssemblerTheInstruction(output_file_ptr, &instruction);
    $CHECK_AND_RETURN_ERROR

    FreeText(&instruction);

    return 0;
}
