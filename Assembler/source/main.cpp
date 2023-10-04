#include "assembler.h"

int main()
{
    ERRORS error = NO_ERR;

    const char* input_file = "Txt/commands.txt";
    const char* output_file = "Txt/commands_in_byte_code.txt";

    Text instruction = FillText(input_file, &error);
    $CHECK_AND_RETURN_ERROR

    error = AssemblerTheInstruction(output_file, &instruction);
    $CHECK_AND_RETURN_ERROR

    FreeText(&instruction);

    return 0;
}
