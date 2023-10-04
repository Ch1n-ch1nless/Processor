#include "print_text.h"

ERRORS PrintText(FILE* file_ptr, Text onegin)
{
    assert(onegin.line_array);

    ERRORS error = NO_ERR;

    for (size_t i = 0; i < onegin.n_lines; i++) {
        if ((onegin.line_array)->str_ptr) {
            fprintf(file_ptr, "%s\n", (onegin.line_array)->str_ptr);
            (onegin.line_array)++;
        } else {
            fprintf(file_ptr, "END OF FILE!!!");
            break;
        }
    }

    return error;
}

void FreeText(Text* onegin)
{
    free(onegin->buffer);
    onegin->buffer = nullptr;
    onegin->buf_size = 0;

    free(onegin->line_array);
    onegin->line_array = nullptr;
    onegin->n_lines = 0;

    if (onegin->file_ptr != nullptr) {
        fclose(onegin->file_ptr);
        onegin->file_ptr = nullptr;
    }
}
