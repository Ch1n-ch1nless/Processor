///@file stack.h

#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include "errors.h"

///Constant by which we increase the stack size
const size_t STACK_SIZE_UP   = 2;

///Constant by which reduce stack size
const size_t STACK_SIZE_DOWN = 4;



/**
 *@brief Construct the Stack
 *
 *@param [in] stk - pointer to stack
 *@param [in] stk_name - name of stack
 *@param [in] file - name of file in which the stack was created
 *@param [in] line - value of line on which the stack was created
 *
 *@return NO_ERR - if the stack has been compiled successfully
 *@return error  - the variable which contains numbers of errors, which u can see in enum ERRRORS.
 *
 *The function assigns values to all stack elements and specifies the memory area of the array
 */
error_t StackCtor(Stack* stk, const char* stk_name, const char* file, const int   line);

/**
 *@brief Destruct the Stack
 *
 *@param [in] stk - pointer to stack
 *
 *@return NO_ERR - if the stack has been destroyed successfully
 *@return error  - the variable which contains numbers of errors, which u can see in enum ERRRORS.
 *
 *The function makes free the memory area of array with canaries and make the status of stack - KILLED_STACK
 */
error_t StackDtor(Stack* stk);



/**
 *@brief Add to Stack the new element
 *
 *@param [in] stk - pointer to stack
 *@param [in] new_value - value of new element
 *
 *@return NO_ERR - if the stack has been completed successfully
 *@return error  - the variable which contains numbers of errors, which u can see in enum ERRRORS.
 */
error_t StackPush(Stack* stk, elem_t new_value);

/**
 *@brief Delete last element of Stack
 *
 *@param [in] stk - pointer to stack
 *@param [in] ret_value - pointer to variable, which will contains the value of last element
 *
 *@return NO_ERR - if the stack has been completed successfully
 *@return error  - the variable which contains numbers of errors, which u can see in enum ERRRORS.
 */
error_t StackPop(Stack* stk, elem_t* ret_value);

/**
 *@brief Make the new memory area of array with canaries
 *
 *@param [in] stk - pointer to stack
 *
 *@return NO_ERR - if the stack has been destroyed successfully
 *@return error  - the variable which contains numbers of errors, which u can see in enum ERRRORS.
 *
 *If stk->capacity is too small to add the new element pr too big to delete last element. The function
 *finds new memory area, which size will be bigger or smaller.
 */
error_t StackRealloc(Stack* stk);



/**
 *@brief Print all elements of stack
 *
 *@param [in] stk - pointer to stack
 *@param [in] stk_name - name of stack
 *@param [in] file - name of file in which the function was called
 *@param [in] function - name of function that was called
 *@param [in] line - value of line on which the function was called
 *
 *@return NO_ERR - if the stack has been destroyed successfully
 *@return error  - the variable which contains numbers of errors, which u can see in enum ERRRORS.
 */
error_t PrintStack(Stack* stk, const char* stk_name, const char* file,
                               const char* function, const int   line);

#endif // STACK_H_INCLUDED
