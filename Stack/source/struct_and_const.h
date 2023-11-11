///@file struct_and_const.h
#ifndef STRUCT_AND_CONST_H_INCLUDED
#define STRUCT_AND_CONST_H_INCLUDED

/**
 * The elem_t is data type of stack's elements
 */
typedef int elem_t;
/**
 * This define specifies how the elements will be displayed
 */
#define elem_format "%d"

#define PRINT_STACK(stk) PrintStack((stk), #stk, __FILE__, __FUNCTION__, __LINE__);
#define STACK_CTOR(stk) StackCtor((stk), #stk, __FILE__, __LINE__);

/// The canary_t is data type of canaries
typedef unsigned int canary_t;
/// The hash_t is data type of hash
typedef unsigned int hash_t;

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../Common_files/config_error.h"

const elem_t POISON_VALUE = 0;                      //!< @brief The value of element, which show that we don't have this element
const canary_t LEFT_CANARY_VALUE   = 0x602DA617;    //!< @brief The value of working stack left canary
const canary_t RIGHT_CANARY_VALUE  = 0x602DABAD;    //!< @brief The value of working stack right canary
const canary_t INTRO_CANARY_VALUE  = 0xD134CA75;    //!< @brief The value of working data left canary
const canary_t OUTRO_CANARY_VALUE  = 0x06B16A55;    //!< @brief The value of working data right canary
const canary_t POISON_CANARY_VALUE = 0xF331D3AD;    //!< @brief The value of killed canary
const char* const KILLED_STACK = "D3AD 57ACK";      //!< @brief The status, which shows that stack was destructed
const char* const LIVE_STACK   = "LIVE STACK";      //!< @brief The status, which shows that stack is correct

/**
 *The struct which contains elements of real stack and security features
 */
struct Stack
{
    #if defined WITH_CANARY
        canary_t left_canary;   //!< the element, that checks if the stack data was affected on the left
    #endif
    char* data;                 //!< the pointer to memory area where the array with canaries is located
    int size;                   //!< the number of elements
    int capacity;               //!< the size of array
    const char* name;           //!< the name of stack
    const char* file;           //!< the name of file, which has been constructed stack
    int line;                   //!< the value of line, which has been constructed the stack
    const char* status;         //!< the status of stack, which can contains LIVE_STACk or KILLED_STACK
    #if defined WITH_HASH
        hash_t hash;            //!< the hash of stack
    #endif
    #if defined WITH_CANARY
        canary_t right_canary;  //!< the element, that checks if the stack data was affected on the right
    #endif
};

#endif // STRUCT_AND_CONST_H_INCLUDED
