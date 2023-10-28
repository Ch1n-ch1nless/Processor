///@file errors.h
#ifndef ERRORS_H_INCLUDED
#define ERRORS_H_INCLUDED

#include "getter_setter.h"
#include "log.h"
#include <string.h>

#define PRINT_ERROR(stk, error) PrintError(stk, error, __FILE__, __FUNCTION__, __LINE__);

///Types of errors:
enum ERRORS : unsigned int
{
    NO_ERR                    = 0,       //!< constant which shows that no errors
    NULL_STK_ERR              = 1 << 0,  //!< constant which shows that pointer to stack is null
    NULL_ARR_ERR              = 1 << 1,  //!< constant which shows that pointer to array is null
    MINUS_CAPACITY_ERR        = 1 << 2,  //!< constant which shows that capacity of array is fewer 0
    MINUS_SIZE_ERR            = 1 << 3,  //!< constant which shows that size of array is fewer 0
    CAPACITY_FEWER_SIZE_ERR   = 1 << 4,  //!< constant which shows that capacity of array is fewer size
    OPEN_FILE_ERR             = 1 << 5,  //!< constant which shows that program can not open file
    MEM_ALLOC_ERR             = 1 << 6,  //!< constant which shows that program can not allocate memory
    NULL_NAME_ERR             = 1 << 7,  //!< constant which shows that pointer to name of stack is null
    NULL_FILE_ERR             = 1 << 8,  //!< constant which shows that pointer to file of stack is null
    MINUS_LINE_ERR            = 1 << 9,  //!< constant which shows that value of stack's line is fewer 0
    RIGHT_CANARY_DIED         = 1 << 10, //!< constant which shows that right canary of stack was changed
    LEFT_CANARY_DIED          = 1 << 11, //!< constant which shows that left canary of stack was changed
    WRONG_INTRO_ERR           = 1 << 12, //!< constant which shows that left canary of array was changed
    WRONG_OUTRO_ERR           = 1 << 13, //!< constant which shows that right canary of array was changed
    WRONG_HASH                = 1 << 14, //!< constant which shows that hash is wrong
    STK_KILL_ERR              = 1 << 15, //!< constant which shows that status of stack is KILLED_STACK
    WRONG_STK_STATUS_ERR      = 1 << 16, //!< constant which shows that status of stack was changed to strange value
    REG_ARRAY_NULLPTR_ERR     = 1 << 17,
    CMD_ARRAY_NULLPTR_ERR     = 1 << 18,
    FEW_CMD_LINE_ARGS_ERR     = 1 << 19,
    MANY_CMD_LINE_ARGS_ERR    = 1 << 20,
    INCORRECT_INPUT_FILE_ERR  = 1 << 21,
    INCORRECT_OUTPUT_FILE_ERR = 1 << 22,
    READ_FEW_ARGS_ERR         = 1 << 23,
    BAD_MEM_ACS_ERR           = 1 << 24,
    WRITE_TO_FILE_ERR         = 1 << 25,

    END_OF_ENUM
};

/**
 *@brief Checks stack for errors listed in enum
 *
 *@param [in] stk - pointer to Stack
 *
 *@return NO_ERR - if the stack has been destroyed successfully
 *@return error  - the variable which contains numbers of errors, which u can see in enum ERRRORS.
 */
error_t StackVerify(Stack* stk);

/**
 *@brief Print all elements of Stack
 *
 *@param [in] stk - pointer to Stack
 *@param [in] error - variable which contains the errors of stack
 *@param [in] file - pointer to file which was called function
 *@param [in] function - pointer to string, which contains name of function
 *@param [in] line - variable, which contains number of line that function was called
 */
void PrintError(Stack* stk, error_t error, const char* file,
                                           const char* function,
                                           const int   line);
/**
 *@brief Print the value and index of array[index]
 *
 *@param [in] stk - pointer to Stack
 *@param [in] index - index of element
 */
void PrintStkDataElemT(const Stack* stk, const size_t index);

/**
 *@brief Calculate the hash of stack by the djb2
 *
 *@param [in] stk - pointer to Stack
 *
 *@return new hash of stack
 */
hash_t CalculateStkHash(const Stack* stk);

#endif // ERRORS_H_INCLUDED
