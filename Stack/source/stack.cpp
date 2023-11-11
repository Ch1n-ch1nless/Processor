#include "stack.h"

error_t StackCtor(Stack* stk, const char* stk_name, const char* file, const int   line)
{
    error_t error = NO_ERR;

    //Set values to the left canary and right canary
    #if defined WITH_CANARY
        stk->left_canary  = LEFT_CANARY_VALUE;
        stk->right_canary = RIGHT_CANARY_VALUE;
    #endif

    stk->size = 0;
    stk->capacity = 4;

    //Allocate memory for data
    #if defined WITH_CANARY
        stk->data = (char*) calloc(stk->capacity * sizeof(elem_t) + 2 * sizeof(canary_t), sizeof(char));
    #else /*WITHOUT CANARY*/
        stk->data = (char*) calloc(stk->capacity * sizeof(elem_t), sizeof(char));
    #endif

    stk->name = stk_name;
    stk->file = file;
    stk->line = line;
    stk->status = LIVE_STACK;

    //Check the correct functioning of the calloc()
    if (stk->data == nullptr)
    {
        error |= MEM_ALLOC_ERR;
    }
    else
    {
        #if defined WITH_CANARY
            //Set in left canary of data the value INTRO_CANARY_VALUE
            SetStkDataIntro(stk, INTRO_CANARY_VALUE);
            //Set in right canary of data the value OUTRO_CANARY_VALUE
            SetStkDataOutro(stk, OUTRO_CANARY_VALUE);
        #endif
    }

    //Clean the data and fill all elements with a POISON_VALUE
    for (int i = 0; i < stk->capacity; i++)
    {
        SetStkDataElemT(stk, i, POISON_VALUE);
    }

    //Calculate the hash
    #if defined WITH_HASH
        stk->hash = CalculateStkHash((const Stack*) stk);
    #endif

    //Check for errors
    error |= StackVerify(stk);
    if (error != NO_ERR)
        PRINT_STK_ERROR(stk, error)
    return error;
}

error_t StackDtor(Stack* stk)
{
    //Check for errors
    error_t error = StackVerify(stk);
    if (error)
    {
        PRINT_STK_ERROR(stk, error)
        return error;
    }

    //Set the poison value to left canary and right value
    #if defined WITH_CANARY
        stk->left_canary  = POISON_CANARY_VALUE;
        stk->right_canary = POISON_CANARY_VALUE;
    #endif

    free(stk->data);

    stk->status = KILLED_STACK;

    #if defined WITH_HASH
        stk->hash = 0;
    #endif

    return NO_ERR;
}

error_t StackPush(Stack* stk, elem_t new_value)
{
    assert(stk);

    //Check for errors
    error_t error = StackVerify(stk);
    if (error)
    {
        PRINT_STK_ERROR(stk, error);
        return error;
    }

    //Call StackRealloc()
    error |= StackRealloc(stk);
    if (error != NO_ERR)
    {
        PRINT_STK_ERROR(stk, error)
        return error;
    }

    //Push the element to data
    SetStkDataElemT(stk, stk->size, new_value);
    stk->size++;

    #if defined WITH_HASH
        stk->hash = CalculateStkHash(stk);
    #endif

    return NO_ERR;
}

error_t StackPop(Stack* stk, elem_t* ret_value)
{
    assert(stk);
    assert(ret_value);

    //Check for errors
    error_t error = StackVerify(stk);
    if (error)
    {
        PRINT_STK_ERROR(stk, error);
        return error;
    }

    //Check if the data is empty
    if (stk->size == 0)
    {
        *ret_value = POISON_VALUE;
        error |= MINUS_SIZE_ERR;
        PRINT_STK_ERROR(stk, error)
        return error;
    }

    //Pop the element from data
    *ret_value = GetStkDataElemT(stk, stk->size-1);
    stk->size--;
    SetStkDataElemT(stk, stk->size, POISON_VALUE);

    //Calculate the hash
    #if defined WITH_HASH
        stk->hash = CalculateStkHash((const Stack*) stk);
    #endif

    //Call StackRealloc()
    error |= StackRealloc(stk);
    if (error)
    {
        PRINT_STK_ERROR(stk, error);
        return error;
    }

    //Calculate the hash
    #if defined  WITH_HASH
        stk->hash = CalculateStkHash(stk);
    #endif

    return NO_ERR;
}

error_t StackRealloc(Stack* stk)
{
    //Check for errors
    error_t error = StackVerify(stk);
    if (error)
    {
        PRINT_STK_ERROR(stk, error);
        return error;
    }

    //Set to stk->capacity the new value
    if (stk->size >= stk->capacity)
    {
        stk->capacity *= STACK_SIZE_UP;
    }
    else if ((size_t) stk->size < (stk->capacity / STACK_SIZE_DOWN))
    {
        stk->capacity /= STACK_SIZE_UP; //Reduce the data size by constant = STACK_SIZE_UP
    }
    else
    {
        return NO_ERR;
    }

    //Allocate the new memory area
    char* temp_ptr = nullptr; //temporary pointer
    #if defined WITH_CANARY
        temp_ptr = (char*) realloc(stk->data, stk->capacity * sizeof(elem_t) + 2 * sizeof(canary_t) + 8);
    #else
        temp_ptr = (char*) realloc(stk->data, stk->capacity * sizeof(elem_t));
    #endif

    //Check the correct functioning of the realloc()
    if (temp_ptr == nullptr)
    {
        error |= MEM_ALLOC_ERR;
        PRINT_STK_ERROR(stk, error)
    }
    else
    {
        stk->data = temp_ptr;
    }

    //Clean the data and fill all elements with a POISON_VALUE
    for (size_t i = stk->size; i < (size_t)stk->capacity; i++)
    {
        SetStkDataElemT(stk, i, POISON_VALUE);
    }

    //Set the values to left canary and right canary
    #if defined WITH_CANARY
        SetStkDataIntro(stk, INTRO_CANARY_VALUE);
        SetStkDataOutro(stk, OUTRO_CANARY_VALUE);
    #endif

    return NO_ERR;
}

error_t PrintStack(Stack* stk, const char* file, const char* function, const int   line)
{
    error_t error = StackVerify(stk);
    if (error != NO_ERR)
        PRINT_STK_ERROR(stk, error);

    printf("Stack \"%s\": [%p] from %s(%d)\n", stk->name, stk, stk->file, stk->line);
    printf("called from file: %s(%d) in function: %s\n{\n", file, line, function);
    printf("Status of Stack: %s\n", stk->status);
    #if defined WITH_CANARY
        printf("\tLeft Canary =  %X\n", stk->left_canary);
        printf("\tRight Canary = %X\n", stk->right_canary);
    #endif
    printf("\tSize     = %d\n", stk->size);
    printf("\tCapacity = %d\n", stk->capacity);
    #if defined WITH_HASH
        printf("\tHash     = %u\n", stk->hash);
    #endif
    printf("\tData     = [%p]\n", stk->data);

    if (stk->data == nullptr)
    {
        printf("\tElements of Data: {}\n}\n");
        return NO_ERR;
    }
    printf("\tElements of Data:\n\t{\n");
    #if defined WITH_CANARY
        printf("\t Left canary(Intro) = %X\n", GetStkDataIntro(stk));
    #endif
    for (int i = 0; i < stk->capacity; i++)
    {
        PrintStkDataElemT(stk, i);
    }
    #if defined WITH_CANARY
        printf("\t Right canary(Outro) = %X\n", GetStkDataOutro(stk));
    #endif
    printf("\t}\n}\n");

    return NO_ERR;
}

