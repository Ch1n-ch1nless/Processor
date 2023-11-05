///@file errors.h
#ifndef STK_ERRORS_H_INCLUDED
#define STK_ERRORS_H_INCLUDED

#include "getter_setter.h"
#include "log.h"
#include <string.h>

#define PRINT_STK_ERROR(stk, error) PrintStkError(stk, error, __FILE__, __FUNCTION__, __LINE__);

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
void PrintStkError(Stack* stk, error_t error, const char* file,
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

#endif // STK_ERRORS_H_INCLUDED
