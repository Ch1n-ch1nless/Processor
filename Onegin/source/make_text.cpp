#include "make_text.h"

ERRORS FillText(const char* filename, Text* onegin)
{
    ERRORS error = NO_ERR;

    error = OpenFile(onegin, filename);
    $CHECK_AND_RETURN_ERROR

    error = ReadBuffer(onegin);
    $CHECK_AND_RETURN_ERROR

    size_t count_of_lines = FillLineArray(onegin, &error);

    if (count_of_lines <= onegin->n_lines) {
        onegin->n_lines = count_of_lines;
    } else {
        printf("ERROR! count_of_lines: %d\nn_lines: %d\n", count_of_lines, onegin->n_lines);
        assert(0);
    }

    return error;
}

ERRORS OpenFile(Text* onegin, const char* filename)
{
    struct stat st = {};

    onegin->file_ptr = fopen(filename, "r");
    if (onegin->file_ptr == nullptr) {
        ERRORS error = OPEN_FILE_ERR;
        $CHECK_AND_RETURN_ERROR
    }

    stat(filename, &st);
    onegin->buf_size = st.st_size + 1;
    return NO_ERR;
}

ERRORS ReadBuffer(Text* onegin)
{
    assert(onegin);
    assert(onegin->file_ptr);

    onegin->buffer = (char*) calloc(onegin->buf_size, sizeof(char));
    if (onegin->buffer == nullptr) {
        ERRORS error = MEM_ALLOC_ERR;
        $CHECK_AND_RETURN_ERROR
    }

    const size_t symbol_number = fread(onegin->buffer, sizeof(char), onegin->buf_size, onegin->file_ptr);
    if (symbol_number != onegin->buf_size) {
        #if 1
        if (feof(onegin->file_ptr)) {
            printf("Error reading %s: unexpected end of file\n", "<STRING>");
        } else if (ferror(onegin->file_ptr)) {
            printf("Error reading %s", "<STRING>");
        }
        #endif
        if (symbol_number > onegin->buf_size) {
            printf("ERROR! Symbols in Onegin.txt  more then buf_size!");
            assert(0);
        }
    }

    fclose(onegin->file_ptr);
    onegin->file_ptr = nullptr;
    return NO_ERR;
}

size_t FillLineArray(Text* onegin, ERRORS* error)
{
    assert(onegin);
    assert(onegin->buffer);

    onegin->n_lines = onegin->buf_size / 2 + 1;
    onegin->line_array = (Line*) calloc(onegin->n_lines, sizeof(Line));
    if (onegin->line_array == nullptr) {
        fprintf(stderr, "%s:%d\n", __FILE__, __LINE__);
        *error = MEM_ALLOC_ERR;
        return 0;
    }

    size_t count_of_lines = 0;

    Line* temp_array = onegin->line_array;
    temp_array->str_ptr = onegin->buffer;

    for (size_t i = 1; i < onegin->buf_size; i++) {
        if (*(onegin->buffer + i) == '\n')
        {
            size_t length = (onegin->buffer + i) - temp_array->str_ptr;
            temp_array->str_len = length;
            do {
                *(onegin->buffer + i) = '\0';
                i++;
            } while(*(onegin->buffer + i) == '\n');

            temp_array++;
            temp_array->str_ptr =  (onegin->buffer + i);

            count_of_lines++;

        }
        else if (*(onegin->buffer+ i) == '\0')
        {
            size_t length = (onegin->buffer + i) - temp_array->str_ptr;
            temp_array->str_len = length;

            count_of_lines++;

            return count_of_lines;
        }
    }
    return count_of_lines;
}

