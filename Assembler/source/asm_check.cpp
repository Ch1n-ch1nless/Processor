#include "asm_check.h"

void DeleteExtraSpacesAndTabs(char** string)
{
    assert((string != nullptr) && "Error! Pointer to string is NULL!!!");

    size_t count_of_extra_char = 0;  //Count of extra spaces, tabs before command
    char temp_array[] = {};          //Temporary array of symbols

    sscanf(*string, "%[ \t]%n", temp_array, &count_of_extra_char);

    *string = *string + count_of_extra_char;

    return;
}

error_t CheckCorrectnessOfArguments(char* str_arg, unsigned int arg_type)
{
    assert(str_arg);

    if (arg_type == LBL) return NO_ERR;

    error_t error = NO_ERR;

    char* copy_str_arg = str_arg;

    size_t count_of_args = 0;

    error |= CheckCorrectnessOfRamArgument(&copy_str_arg);
    CHECK_ERROR(error != NO_ERR, error);

    while (*copy_str_arg != '\0' && *copy_str_arg != ';' && *copy_str_arg != '\n')
    {
        error |= CheckCorrectnessOfRegArgument(&copy_str_arg, &count_of_args);

        error |= CheckCorrectnessOfNumArgument(&copy_str_arg, &count_of_args);
    }

    if (count_of_args > 1)
    {
        return error | INCORRECT_NUM_OF_ARGS_ERR;
    }

    return error;
}

error_t CheckCorrectnessOfRamArgument(char** str_arg)
{
    assert((str_arg  != nullptr) && "Error! Pointer to link of string is NULL!!!");
    assert((*str_arg != nullptr) && "Error! Pointer to string is NULL!!!");

    error_t error = NO_ERR;

    char* first_bracket_pt = strchr(*str_arg, '[');

    if (first_bracket_pt == nullptr)
    {
        first_bracket_pt = strchr(*str_arg, ']');

        if (first_bracket_pt == nullptr)
        {
            return error;
        }
    }
    else if (*str_arg - first_bracket_pt == 0)
    {
        *str_arg = *str_arg + 1;

        if (strchr(*str_arg, '[') == nullptr)
        {
            first_bracket_pt = strchr(*str_arg, ']');

            if (first_bracket_pt != nullptr)
            {
                if (first_bracket_pt - *str_arg > 1)
                {
                    first_bracket_pt++;

                    first_bracket_pt = strchr(first_bracket_pt, ']');

                    if (first_bracket_pt == nullptr)
                    {
                        return error;
                    }
                }
            }
        }
    }

    return error | WRONG_SYNTAX_ERR;
}

error_t CheckCorrectnessOfNumArgument(char** str_arg, size_t* count_of_args)
{
    assert((str_arg       != nullptr) && "Error! Pointer to link of string is NULL!!!");
    assert((*str_arg      != nullptr) && "Error! Pointer to string is NULL!!!");
    assert((count_of_args != nullptr) && "Error! Pointer to count of arguments is NULL!!!");

    error_t error = NO_ERR;

    int is_argument_number = 0;

    while (**str_arg != '\0' && **str_arg != ';' && **str_arg != '\n')
    {
        DeleteExtraSpacesAndTabs(str_arg);

        while (isdigit(**str_arg))
        {
            *str_arg = *str_arg + 1;
            is_argument_number = 1;
        }

        *count_of_args += is_argument_number;

        DeleteExtraSpacesAndTabs(str_arg);

        if (isdigit(**str_arg) == false)
        {
            if (isalpha(**str_arg) || **str_arg == '\0' || **str_arg == ';' || **str_arg == '\n')
            {
                break;
            }
            else if (**str_arg == ']')
            {
                *str_arg = *str_arg + 1;
            }
            else
            {
                error |= WRONG_SYNTAX_ERR;
                break;
            }
        }
    }

    return error;
}

error_t CheckCorrectnessOfRegArgument(char** str_arg, size_t* count_of_args)
{
    assert((str_arg       != nullptr) && "Error! Pointer to link of string is NULL!!!");
    assert((*str_arg      != nullptr) && "Error! Pointer to string is NULL!!!");
    assert((count_of_args != nullptr) && "Error! Pointer to count of arguments is NULL!!!");

    error_t error = NO_ERR;

    int is_argument_letter = 0;

    while (**str_arg != '\0' && **str_arg != ';' && **str_arg != '\n')
    {
        DeleteExtraSpacesAndTabs(str_arg);

        while (isalpha(**str_arg))
        {
            *str_arg = *str_arg + 1;
            is_argument_letter = 1;
        }

        *count_of_args += is_argument_letter;

        DeleteExtraSpacesAndTabs(str_arg);

        if (isalpha(**str_arg) == false)
        {
            if (isdigit(**str_arg) || **str_arg == '\0' || **str_arg == ';' || **str_arg == '\n')
            {
                break;
            }
            else if (**str_arg == ']')
            {
                *str_arg = *str_arg + 1;
            }
            else
            {
                error |= WRONG_SYNTAX_ERR;
                break;
            }
        }
    }

    return error;
}
