#include "asm_check.h"

void DeleteExtraSpacesAndTabs(char** string)
{
    assert((string != nullptr)  && "Error! Pointer to string is NULL!!!");
    assert((*string != nullptr) && "Error! Pointer to char* array is NULL!!!");

    size_t count_of_extra_char = 0;  //Count of extra spaces, tabs before command
    char temp_array[] = {};          //Temporary array of symbols

    sscanf(*string, "%[ \t]%n", temp_array, &count_of_extra_char);

    *string = *string + count_of_extra_char;

    return;
}

error_t CheckCorrectnessOfArguments(char* str_arg, unsigned int arg_type)
{
    assert((str_arg  != nullptr) && "Error! Pointer to link of string is NULL!!!");

    error_t error = NO_ERR;

    char* copy_str_arg = str_arg;   //Copy of string with arguments

    size_t count_of_args = 0;       //Counter of function's arguments

    //Moves the pointer to a string so that the first element is not a white space or a tab
    DeleteExtraSpacesAndTabs(&copy_str_arg);

    //Validates the spelling of square brackets
    error |= CheckCorrectnessOfBrackets(&copy_str_arg);
    CHECK_ERROR(error != NO_ERR, error);

    while (*copy_str_arg != '\0' && *copy_str_arg != ';'
                                 && *copy_str_arg != '\n' && *copy_str_arg != '\r')
    {
        //Validates the spelling of string characters
        error |= CheckCorrectnessOfSymbols(&copy_str_arg, &count_of_args);
    }

    if (count_of_args > 1)
    {
        return error | INCORRECT_NUM_OF_ARGS_ERR;
    }

    return error;
}

error_t CheckCorrectnessOfBrackets(char** str_arg)
{
    assert((str_arg  != nullptr) && "Error! Pointer to link of string is NULL!!!");
    assert((*str_arg != nullptr) && "Error! Pointer to string is NULL!!!");

    error_t error = NO_ERR;

    char* bracket_pt = strchr(*str_arg, '[');   //Pointer to '['

    char* comment_pt = strchr(*str_arg, ';');   //Pointer to ';'

    if (bracket_pt == nullptr) //Check that string doesn't have '['
    {
        bracket_pt = strchr(*str_arg, ']');

        if (bracket_pt == nullptr) //Check that string doesn't have ']'
        {
            return error;
        }
        else if (bracket_pt > comment_pt && comment_pt != nullptr) //Check that ']' locates in comment
        {
            return error;
        }
    }
    else if (*str_arg - bracket_pt == 0) //Checks that begin of argument is '['
    {
        *str_arg = *str_arg + 1;

        bracket_pt = strchr(*str_arg, '[');     //Pointer to second '['

        if (bracket_pt == nullptr)  //String doesn't have second '['
        {
            bracket_pt = strchr(*str_arg, ']'); //Pointer to ']'

            if (bracket_pt != nullptr)
            {
                //Checks that string has next type: ([...] ; ...) or ([...])
                if (bracket_pt - *str_arg > 0 && (bracket_pt < comment_pt || comment_pt == nullptr))
                {
                    bracket_pt++;

                    bracket_pt = strchr(bracket_pt, ']');

                    //Checks that string doesn't have second ']' or second ']' locates in comment
                    if (bracket_pt == nullptr || (bracket_pt > comment_pt && comment_pt != nullptr))
                    {
                        return error;
                    }
                }
            }
        }
        //Checks that second '[' in comment
        else if (bracket_pt > comment_pt && comment_pt != nullptr)
        {
            bracket_pt = strchr(*str_arg, ']');

            if (bracket_pt != nullptr)
            {
                //Checks that string has next types: ([...] ; ...) or ([...])
                if (bracket_pt - *str_arg > 0 && (bracket_pt < comment_pt || comment_pt == nullptr))
                {
                    bracket_pt++;

                    bracket_pt = strchr(bracket_pt, ']');

                    //Checks that string doesn't have second ']' or second ']' locates in comment
                    if (bracket_pt == nullptr || (bracket_pt > comment_pt && comment_pt != nullptr))
                    {
                        return error;
                    }
                }
            }
        }
    }
    //Checks that string has next type: ... ; ...[...
    else if (bracket_pt > comment_pt && comment_pt != nullptr)
    {
        return error;
    }

    return error | WRONG_SYNTAX_ERR;
}

error_t CheckCorrectnessOfSymbols(char** str_arg, size_t* count_of_args)
{
    assert((str_arg       != nullptr) && "Error! Pointer to link of string is NULL!!!");
    assert((*str_arg      != nullptr) && "Error! Pointer to string is NULL!!!");
    assert((count_of_args != nullptr) && "Error! Pointer to count of arguments is NULL!!!");

    error_t error = NO_ERR;

    int is_argument = 0; //Variable that accepts 1 if there is an argument and 0 otherwise

    while (**str_arg != '\0' && **str_arg != ';' && **str_arg != '\n' && **str_arg != '\r')
    {
        is_argument = 0;    //No arguments

        //Moves the pointer to a string so that the first element is not a white space or a tab
        DeleteExtraSpacesAndTabs(str_arg);

        while (isalnum(**str_arg) || **str_arg == '_' || **str_arg == '-')
        {
            *str_arg = *str_arg + 1;    //Go to next symbol
            is_argument = 1;            //Find argument
        }

        *count_of_args += is_argument;  //Count number of arguments

        //Moves the pointer to a string so that the first element is not a white space or a tab
        DeleteExtraSpacesAndTabs(str_arg);

        if (isalnum(**str_arg) == false && **str_arg != '_' && **str_arg != '-')
        {
            if (**str_arg == '\0' || **str_arg == ';' || **str_arg == '\n')
            {
                break; //After these symbols string doesn't have arguments
            }
            else if (**str_arg == ']')
            {
                *str_arg = *str_arg + 1; //Skip the bracket
            }
            else
            {
                error |= WRONG_SYNTAX_ERR;  //String has incorrect symbols!
                break;
            }
        }
    }

    return error;
}
