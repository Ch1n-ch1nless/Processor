#include "disassembler.h"

ERRORS DisAssemblerTheInstruction(const char* outputfile, Text* guide)
{
    ERRORS error = NO_ERR;

    FILE* output = fopen(outputfile, "w");
    if (output == nullptr)
    {
        error = OPEN_FILE_ERR;
        return error;
    }

    for (int i = 0; i < guide->n_lines; i++)
    {
        if (strncmp(guide->line_array[i].str_ptr, cmd_array[0].mode, 1) == 0)
        {
            fprintf(output, "%s%s\n", cmd_array[0].asm_cmd, guide->line_array[i].str_ptr + 1);
            continue;
        }
        for (int j = 1; j < COUNT_OF_COMMANDS; j++)
        {
            if (strncmp(guide->line_array[i].str_ptr, cmd_array[j].mode, strlen(cmd_array[j].mode)) == 0)
            {
                fprintf(output, "%s\n", cmd_array[j].asm_cmd);
            }
        }
    }

    fclose(output);

    return error;
}
