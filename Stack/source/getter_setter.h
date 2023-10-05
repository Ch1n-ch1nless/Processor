///@file getter_setter.h

#ifndef GETTER_SETTER_H_INCLUDED
#define GETTER_SETTER_H_INCLUDED

#include "struct_and_const.h"
/**
 *@brief Return the value of array's left canary
 *
 *@param [in] stk - pointer to stack
 *
 *@return value of array's left canary
 */
canary_t GetStkDataIntro(const Stack* stk);
/**
 *@brief Return the value of array's right canary
 *
 *@param [in] stk - pointer to stack
 *
 *@return value of array's right canary
 */
canary_t GetStkDataOutro(const Stack* stk);

/**
 *@brief Set the new value of array's left canary
 *
 *@param [in] stk - pointer to stack
 *
 *@param [in] new value of array's left canary
 */
void SetStkDataIntro(Stack* stk, const canary_t new_value);
/**
 *@brief Set the new value of array's right canary
 *
 *@param [in] stk - pointer to stack
 *
 *@param [in] new value of array's right canary
 */
void SetStkDataOutro(Stack* stk, const canary_t new_value);

/**
 *@brief Return the value of array[index]
 *
 *@param [in] stk - pointer to stack
 *
 *@param [in] index - index of element in array
 *
 *@return value of array[index]
 */
elem_t GetStkDataElemT(const Stack* stk, const size_t index);
/**
 *@brief Set the new value in array[index]
 *
 *@param [in] stk - pointer to stack
 *
 *@param [in] index - index of element in array
 *
 *@param [in] new value of array[index]
 */
void SetStkDataElemT(Stack* stk, const size_t index, elem_t new_value);

#endif // GETTER_SETTER_H_INCLUDED
